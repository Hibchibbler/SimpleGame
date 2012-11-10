/**********************************************************************************
Tank Game
TankGame.cpp

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#include "TankGame.h"
#include <sstream>

void sg::TankGame::doInit(){

    assetMan.load();
    //Load Font
    dash.load();
    dash.setHealth(100);
    dash.setVelocity(sf::Vector2f(0,0));
    dash.setPos(sf::Vector2f(0,0));

    //Load arenaMan
    //arenaMan.Load(assetMan, (sf::Uint32)dispDim.x, (sf::Uint32)dispDim.y);
    startPopup.doInit(*this,dispDim.x, dispDim.y);
    lobbyPopup.doInit(*this,dispDim.x, dispDim.y);
    mechanics.doInit(*this, dispDim.x, dispDim.y);
    
}

void sg::TankGame::onRemoteEvent(sg::CommEvent & event){
    //some GamePackets have an ID that is indicative of the socket on
    //to which the packet pertains.
    sf::Uint32 packetType;
    event.packet >> packetType;
    switch (packetType){
    case sg::CommEvent::Acceptance:{
        sf::Uint32 id;
        std::string msg;
        event.packet >> id;
        event.packet >> msg;
        cout << "Acceptance: " << msg << endl;
        connectionId = id;
        connected = true;
        
        /*teamMan.load(arenaMan, my_team);
        teamMan.teams[my_team].addPlayer(assetMan,0,0,arenaMan.getGarage(my_team));
        teamMan.teams[!my_team].addPlayer(assetMan,1,0,arenaMan.getGarage(!my_team));*/

        break;
    }case sg::CommEvent::Disconnect:{
        sf::Uint32 id;
        std::string msg;
        event.packet >> id;
        event.packet >> msg;
        connected = false;
        cout << "Disconnect: " << msg << endl;
        break;
    }case sg::CommEvent::Sent:{
        //cout << "Sent" << endl;
        break;
    }case sg::CommEvent::Error:{
        sf::Uint32 id;
        std::string msg;
        event.packet >> id;
        event.packet >> msg;
        connected = false;
        cout << "Error: " << msg << endl;
        break;
    }
    default:
        break;
    }

    mechanics.onRemoteEvent(*this, event, packetType);
}

void sg::TankGame::sendPlayerState()
{
    //sg::CommEvent packet;

    ////This id indicates to Comm, which connection 
    ////that this GamePacket will be sent on.
    ////It isn't really used in a two player, one connection scenario.    
    //packet.connectionId = connectionId;
    //
    //packet.packet << (sf::Uint32)sg::CommEvent::Data;
    //packet.packet << (sf::Uint32)sg::TankGame::State;
    //packet.packet << teamMan.teams[my_team].players[0].tank.tankState.bodyAngle;
    //packet.packet << teamMan.teams[my_team].players[0].tank.tankState.turretAngle;
    //packet.packet << teamMan.teams[my_team].players[0].playerState.health;
    //packet.packet << teamMan.teams[my_team].players[0].tank.tankState.position.x;
    //packet.packet << teamMan.teams[my_team].players[0].tank.tankState.position.y;
    //packet.packet << teamMan.teams[my_team].players[0].projectiles.size();
    //std::vector<Projectile>::iterator proj = teamMan.teams[my_team].players[0].projectiles.begin();
    //while (proj != teamMan.teams[my_team].players[0].projectiles.end()){
    //    packet.packet << proj->projectileState.position.x;
    //    packet.packet << proj->projectileState.position.y;
    //    packet.packet << proj->projectileState.velocity.x;
    //    packet.packet << proj->projectileState.velocity.y;
    //    proj++;
    //}

    //packet.packet << teamMan.teams[my_team].minions.size();
    //std::list<Minion>::iterator minion = teamMan.teams[my_team].minions.begin();
    //while (minion != teamMan.teams[my_team].minions.end()){
    //    packet.packet << minion->minionState.position.x;
    //    packet.packet << minion->minionState.position.y;
    //    minion++;
    //}


    //if (connected){
    //    comm.Send(packet);
    //    //cout << "Tx'd, player1, " << packet.connectionId << ", " << player1.bodyAngle << ", " << player1.turretAngle << ", " << player1.velocity.x << ", " << player1.velocity.y << endl;
    //}
}

bool sg::TankGame::onLocalEvent(sf::Event & event){
    switch (gameState){
        case START:
            startPopup.onWindowEvent(*this, window,event);
            break;
        case LOBBY:
            lobbyPopup.onWindowEvent(*this, window,event);
            break;
        case DONE:
            //Stop either the server or the client
            window.close();
            comm.Stop();
            break;
        case RUN:
            mechanics.onWindowEvent(*this, window,event);
            break;
    }

    //General EVent handling
    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code){
        //case  sf::Keyboard::J:
        //    //Join a games
        //    comm.StartClient(8280, "127.0.0.1");
        //    isServer = false;
        //    my_team = 1;
        //    break;
        //case sf::Keyboard::H:
        //    //Host a game
        //    comm.StartServer(8280);
        //    isServer = true;
        //    my_team = 0;
        //    break;
        case sf::Event::LostFocus:
            gameWindowHasFocus = false;
            break;
        case sf::Event::GainedFocus:
            gameWindowHasFocus = true;
            break;
        }
    }else if (event.type == sf::Event::MouseWheelMoved){
        //Increase the size of the arenaView.
        //This causes everything drawn to be scaled either bigger or smaller.
        zoom(event.mouseWheel.delta, arenaView, dispDim);
    }else if (event.type == sf::Event::Resized){
        //store the new
        dispDim.x  = (float)event.size.width;
        dispDim.y  = (float)event.size.height;
    }else if (event.type == sf::Event::Closed){
        window.close();
        comm.Stop();
    }
    return true;
}

bool sg::TankGame::doLocalInput(){
    if (gameWindowHasFocus != true)
        return false;
    if (gameState == GameState::START){
        startPopup.doLocalInput(*this);//(&window,event);
    }else if (gameState == GameState::LOBBY){
        lobbyPopup.doLocalInput(*this);
    }else if (gameState == GameState::RUN){

        mechanics.doLocalInput(*this);
    }
    return true;
}

bool sg::TankGame::zoom(int delta, sf::View & v, sf::Vector2f screenSize){
    float addend = delta/15.0f;
    sf::Vector2f newSize = v.getSize();

    //if the screen is wider than tall;(this is assumed default)
    /*
         wider than tall => x + mx + x/y -> x
         taller than wide =>y + mx + y/x -> y
    */
    newSize.x += 20.0f*delta*(screenSize.x/screenSize.y);
    newSize.y += 20.0f*delta;
    
    
    v.setSize(newSize);
    return true;
}

void sg::TankGame::doLoop(sf::Time & frameTime){
    if (transitionClock.getElapsedTime().asMilliseconds() > 200){
         GameState state = gameState;
         if (state == RUN){
            sf::Uint32 s = mechanics.doLoop(*this);
            switch (s){

            }
        }else if (state == GameState::START){
            sf::Uint32 s = startPopup.doLoop(*this);
            switch (s){
                case 0x00000000://Quit
                    break;
                case 0x00000001://Join
                    gameState = GameState::LOBBY;
                    break;
                case 0x00000002://Host
                    gameState = GameState::LOBBY;
                    break;
            }
        }else if (state == GameState::LOBBY){
            sf::Uint32 s = lobbyPopup.doLoop(*this);
            switch (s){
                case 0x00000000://Nothing to say
                    break;
                case 0x00000001://Start
                    gameState = GameState::RUN;
                    break;
            }
        }else if (state == GameState::DONE){

        }
        transitionClock.restart();
    }


}

void sg::TankGame::doRender(){
    // Clear the screen (fill it with black color)
    window.clear();

    if (gameState == GameState::START){
        //window.draw(startPopup);
        startPopup.doDraw(window);
    }else if (gameState == GameState::LOBBY){
        //window.draw(lobbyPopup);
        lobbyPopup.doDraw(window);
    }else if (gameState == GameState::RUN){
       //window.draw(mechanics);
        mechanics.doDraw(window);
    }else if (gameState == GameState::DONE){
        
    }

    //Finally, Display window contents on screen
    window.display();
}

void sg::TankGame::doCleanup(){
    startPopup.doCleanup(*this);
}

