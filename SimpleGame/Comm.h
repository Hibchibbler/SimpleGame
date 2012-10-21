/**********************************************************************************
Tank Game
Comm.h
Daniel Ferguson, Eddie Stranberg
Copyright 2012
**********************************************************************************/

#ifndef Comm_h_
#define Comm_h_

#include <SFML/Network.hpp>
#include <queue>


namespace sg
{
    class Connection//TODO rename to Client, or Player or something..
    {
    public:
        Connection(){
            IsConnected = false;
            Socket = NULL;
        }
        bool IsConnected;
        sf::TcpSocket* Socket;
        sf::Uint32 connectionId;
        std::queue<sf::Packet> RecvQueue;
        std::queue<sf::Packet> SendQueue;
        sf::Mutex* SendMutex;
        sf::Mutex* RecvMutex;
    private:

    };


    class CommPacket
    {
    public:
        enum CommPacketType{
            Acceptance,
            Established,
            Disconnect,
            Data,
            Sent,
            Error
        };
        CommPacket(){
            connectionId = -1;
        }
        sf::Packet packet;
        sf::Uint32 connectionId;
    private:
    };


    class Comm
    {
    public:
        Comm()
            : 
        //#pragma(warning disable: 4355);
        CommLooperThread(sg::Comm::CommLooper,this)
        {
            NotDone = true;
            TotalConnectCount=0;
        }
        ~Comm(){}
        void AddConnection(sg::Connection &client);
        bool StartClient(sf::Uint16 port, sf::IpAddress addr);
        bool StartServer(sf::Uint16 port);
        void Stop();
        void Send(sg::CommPacket &p);
        bool Receive(sg::CommPacket &p);
    protected:
        sf::TcpListener Listener;

        static void CommLooper(Comm* comm);
        sf::Thread CommLooperThread;
        sf::SocketSelector ListeningSelector;
        sf::SocketSelector ConnectingSelector;
        sf::SocketSelector EstablishedSelector;
        
        sf::Mutex ListeningMutex;
        sf::Mutex ConnectingMutex;
        sf::Mutex EstablishedMutex;
        sf::Mutex SystemMutex;

        std::vector<sg::Connection> Listening;
        std::vector<sg::Connection> Connecting;
        std::vector<sg::Connection> Established;
        std::queue<sf::Packet> SystemPackets;

        bool NotDone;
        sf::Uint32 TotalConnectCount;

        //SendSystem enqueues a CommPacket into the incoming queues - where the instantiating scope will then be able to processes them as events
        void SendSystem(sg::CommPacket::CommPacketType msgId, sf::Uint32 connectionId, std::string msg);
    };
}

#endif



