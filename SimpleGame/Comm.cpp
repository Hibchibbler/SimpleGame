/**********************************************************************************
Tank Game
Comm.cpp

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#include "Comm.h"
#include <iostream>

#define SELECTOR_TIMEOUT            0.001f
#define COMM_THREAD_LOOP_DELAY      40000 //40 ms




bool sg::Comm::StartClient(sf::Uint16 port, sf::IpAddress addr)
    
{//We are creating a connecting client
    NotDone = true;
    AddConnection(sg::Connection());
    std::cout << "StartClient" << std::endl;
    CommLooperThread.launch();
    return true;
}

//TODO: StartServer operates on the Established connections container
bool sg::Comm::StartServer(sf::Uint16 port)  
{//We are creating a listener
    NotDone = true;
    Listener.listen(8280);
    ListeningSelector.add(Listener);
    std::cout << "StartServer" << std::endl;
    CommLooperThread.launch();
    return true;
}

void sg::Comm::Stop()
{
    NotDone = false;
    std::cout << "waiting for Looper Thread to stop" << std::endl;
    CommLooperThread.wait();

    Listener.close();
    std::vector<sg::Connection>::iterator i = Connecting.begin();
    for (;i != Connecting.end();i++){
        delete i->Socket;
        delete i->SendMutex;
        delete i->RecvMutex;
    }
    Connecting.clear();

    i = Established.begin();
    for (;i != Established.end();i++){
        i->Socket->disconnect();
        delete i->Socket;
        delete i->SendMutex;
        delete i->RecvMutex;
    }
    Established.clear();
}

 //Send operates on the Established connections container
void sg::Comm::Send(sg::CommEvent &gpacket)
{
    EstablishedMutex.lock();
    std::vector<sg::Connection>::iterator i = Established.begin();
    for (;i != Established.end();i++){
        if (gpacket.connectionId == -1 || gpacket.connectionId == i->connectionId){
            i->SendMutex->lock();
            i->SendQueue.push(gpacket.packet);
            i->SendMutex->unlock();
        }
    }
    EstablishedMutex.unlock();
}

//Receive operates on the Established connections container
bool sg::Comm::Receive(sg::CommEvent &gpacket)
{
    //first check for system messages
    SystemMutex.lock();
    while (!SystemPackets.empty()){
        gpacket.connectionId = -1;
        gpacket.packet = SystemPackets.front();
        SystemPackets.pop();
        SystemMutex.unlock();
        return true;
    }
    SystemMutex.unlock();


    //now check for data
    EstablishedMutex.lock();
    std::vector<sg::Connection>::iterator i = Established.begin();
    for (;i != Established.end();i++){
        i->RecvMutex->lock();
        if (!i->RecvQueue.empty()){
            gpacket.packet = i->RecvQueue.front();
            gpacket.connectionId = i->connectionId;
            i->RecvQueue.pop();
            i->RecvMutex->unlock();
            EstablishedMutex.unlock();
            return true;
        }
        i->RecvMutex->unlock();
    }
    EstablishedMutex.unlock();
    return false;
}

//AddConnection adds to the Connecting connections container
void sg::Comm::AddConnection(sg::Connection &client)
{
    ConnectingMutex.lock();
    Connecting.push_back(client);
    ConnectingMutex.unlock();
}

void sg::Comm::CommLooper(Comm* comm)
{
    std::cout << "Looper" << std::endl;
    
    while (comm->NotDone){

        // Check for, and process, any new connection requests
        //TODO: spawn a thread for each willing listener;  the listener mutex and selector stuff is WIP.
        if (comm->ListeningSelector.wait(sf::microseconds(3))){
            sg::Connection newConnection;
            newConnection.Socket = new sf::TcpSocket();
            newConnection.SendMutex = new sf::Mutex();
            newConnection.RecvMutex = new sf::Mutex();
            
            sf::Socket::Status s= comm->Listener.accept(*newConnection.Socket);
            if (s == sf::Socket::Done){
                std::cout << "Client connected from " << newConnection.Socket->getRemoteAddress().toString() << std::endl;

                // Add the client to our internal list
                newConnection.connectionId = comm->TotalConnectCount;
                newConnection.IsConnected = true;
                comm->Established.push_back(newConnection);

                //And add the client to the selector
                comm->EstablishedSelector.add(*newConnection.Socket);
                comm->SendSystem(sg::CommEvent::Acceptance, comm->TotalConnectCount, std::string("accepted Connection Request"));
                comm->TotalConnectCount++;
            }else{
                //TODO: Handle This!!!!!!!!!
                std::cout << "Unable to accept" << std::endl;
            }
        }
    
        //Check for and process and new outgoing connections
        comm->ConnectingMutex.lock();
        {
            std::vector<sg::Connection>::iterator i;
            i = comm->Connecting.begin();
            while (i != comm->Connecting.end()){
                if (i->Socket == NULL){
                    i->Socket = new sf::TcpSocket();
                    i->SendMutex = new sf::Mutex();
                    i->RecvMutex = new sf::Mutex();
                }
                sf::Socket::Status s = i->Socket->connect(sf::IpAddress("127.0.0.1"), 8280);//"192.168.2.110"
                if (s == sf::Socket::Done){
                
                    i->connectionId = comm->TotalConnectCount;
                    i->IsConnected = true;
                    
                    comm->EstablishedSelector.add(*i->Socket);
                    comm->Established.push_back(*i);//this must run before the QueueSystemMessage
                    
                    comm->SendSystem(sg::CommEvent::Acceptance,comm->TotalConnectCount, std::string("Connected"));
                    comm->TotalConnectCount++;
                    //The last thing we do.
                    i = comm->Connecting.erase(i);
                }else {
                    if(s == sf::Socket::Disconnected)
                        comm->SendSystem(sg::CommEvent::Disconnect, comm->TotalConnectCount, std::string("Client disconnected"));
                    else
                        comm->SendSystem(sg::CommEvent::Error,  comm->TotalConnectCount, std::string("Error on receive"));
                    //we'd better remove the socket from the selector
                    delete i->Socket;
                    delete i->SendMutex;
                    delete i->RecvMutex;
                    i = comm->Connecting.erase(i);
                }

            }
            
        }comm->ConnectingMutex.unlock();
        

        comm->EstablishedMutex.lock();
        {
            //Retrieve new incoming data
            if ( comm->EstablishedSelector.wait(sf::milliseconds(3)) ) {
                //Some data is available
                std::vector<sg::Connection>::iterator i;
                i = comm->Established.begin();
                
                while(i != comm->Established.end()){
                    bool ok=true;
                    if (comm->EstablishedSelector.isReady(*i->Socket)){
                        //Client Ready to receive

                        sg::CommEvent RecvPacket;
                        RecvPacket.connectionId = i->connectionId;
                        sf::Socket::Status s;
                        s = i->Socket->receive(RecvPacket.packet);
                        if (s == sf::Socket::Done){
               
                            i->RecvMutex->lock();
                            i->RecvQueue.push(RecvPacket.packet);
                            i->RecvMutex->unlock();
                            ok=true;
                        }else{
                        
                            if(s == sf::Socket::Disconnected)
                                comm->SendSystem(sg::CommEvent::Disconnect, RecvPacket.connectionId, std::string("Client disconnected"));
                            else
                                comm->SendSystem(sg::CommEvent::Error, RecvPacket.connectionId, std::string("Error on receive"));
                            //we'd better remove the socket from the selector
                            comm->EstablishedSelector.remove(*i->Socket);
                            delete i->Socket;
                            delete i->SendMutex;
                            delete i->RecvMutex;
                            //i = comm->Established.erase(i);
                            ok=false;
                        }
                    }
                    if (ok){
                        i++;
                    }else{
                        i = comm->Established.erase(i);
                    }

                }
            }
            //Send any pending outgoing data
            

            std::vector<sg::Connection>::iterator connection =  comm->Established.begin();
            for (;connection != comm->Established.end();){
                bool ok = true;
                connection->SendMutex->lock();
                while(!connection->SendQueue.empty()){
                    sf::Packet packet = connection->SendQueue.front();
                    connection->SendQueue.pop();
                    sf::Socket::Status s = connection->Socket->send(packet);
                    if (s == sf::Socket::Done){
                        comm->SendSystem(sg::CommEvent::Sent, connection->connectionId, std::string("Sent"));
                        ok = true;
                    }else{
                        if (s == sf::Socket::Disconnected)
                            comm->SendSystem(sg::CommEvent::Disconnect, connection->connectionId, std::string("Client disconnected"));
                        else
                            comm->SendSystem(sg::CommEvent::Error, connection->connectionId, std::string("Error on Send"));

                        //we'd better remove the socket from the selector
                        comm->EstablishedSelector.remove(*connection->Socket);
                        delete connection->Socket;
                        delete connection->SendMutex;
                        delete connection->RecvMutex;
                        ok = false;
                    }
                }
                connection->SendMutex->unlock();
                if (ok)
                    connection++;
                else{
                    connection = comm->Established.erase(connection);
                }
                
            }
        }comm->EstablishedMutex.unlock();
            
      

        //Sleep little baby
        sf::sleep(sf::milliseconds(10));
    }
}


void sg::Comm::SendSystem(sg::CommEvent::CommEventType msgId, sf::Uint32 connectionId, std::string msg)
{
    sf::Packet packet;
    packet <<  msgId << connectionId << msg;
    SystemMutex.lock();
    SystemPackets.push(packet);
    SystemMutex.unlock();
}


