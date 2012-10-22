/**********************************************************************************
Tank Game
TankGame.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef TankGame_h_
#define TankGame_h_

#include "Comm.h"
#include "Player.h"
#include "Floor.h"
#include "HUD.h"

#include <iostream>
using std::cout;
using std::endl;

namespace sg
{
    enum ConnectionState{
        NOT_CONNECTED,
        CONNECTED
    };



    class TankGame
    {
    public:
        

        TankGame(int width, int height) : window(sf::VideoMode(width, height, 32), "Tank Game - v0.1")
        {
            connectionState = NOT_CONNECTED;
            gameDone = false;
            aniIndex=0;
            sf::View newView(sf::Vector2f(0.0f,0.0f),sf::Vector2f(400.0f, 300.0f));
            window.setView(newView);
            gameWindowHasFocus = true;
            displayDimensions = sf::Vector2f(width, height);
        }

        enum GameDataType{
            State,
            HitConfirm
        };

        void sendHitConfirm(sf::Uint32 pid);
        void sendState();

        void onInit();
        void onRemoteEvent(sg::CommPacket & packet);
        bool onLocalEvent(sf::Event & event);
        bool onLocalInput();
        void onLoop(sf::Time & frameTime);
        void onRender();
        void onCleanup();

        sf::Vector2f displayDimensions;
        HUD hud;
        


        ConnectionState connectionState;
        sf::Uint32 connectionId;
        int aniIndex;
        sf::Clock aniClock;
        sf::Clock stateClock;
        sf::RenderWindow window;
        sg::Comm comm;
        Player player1;
        Player player2;
        sg::Floor floor;
        bool gameDone;
        bool gameWindowHasFocus;
        long bytesTransmitted;
        long bytesReceoved;
    };
}

#endif

