/**********************************************************************************
Tank Game
TankGame.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef TankGame_h_
#define TankGame_h_

#include "Comm.h"
#include "TeamManager.h"
#include "PlayerManager.h"
#include "ArenaManager.h"
#include "Dashboard.h"


#include <list>
#include <iostream>
using std::cout;
using std::endl;

namespace sg
{
    class TankGame
    {
    public:
        TankGame(float width, float height) : 
          window(sf::VideoMode((unsigned int)width,(unsigned int)height, 32), "Tank Game - v0.1")
        {
            connected = false;
            gameDone = false;
            gameWindowHasFocus = true;
            isServer = false;
            dispDim = sf::Vector2f(width, height);
            arenaView = sf::View(sf::Vector2f(0.0f,0.0f),sf::Vector2f(width, height));//400.0f, 300.0f));
            dashView = sf::View(sf::Vector2f(0.0f,0.0f),sf::Vector2f(width, height));
            window.setView(arenaView);
            sf::FloatRect viewPort;
            viewPort.left = -0.36f;
            viewPort.top = 0.557f;
            viewPort.width = 0.70f;
            viewPort.height = 0.6f;
            dashView.setViewport(viewPort);
        }

        enum GameState{
            WaitOnStartType,
            WaitOnStart,
            Started,
            Victory,
            Loss,
        };

        enum GameDataType{
            State
        };



        void sendState();
        void onInit();
        void onRemoteEvent(sg::CommEvent & packet);
        bool onLocalEvent(sf::Event & event);
        bool onLocalInput();
        void onLoop(sf::Time & frameTime);
        void onRender();
        void onCleanup();

        sg::Comm comm;
        sg::Dashboard dash;
        sg::ArenaManager arenaMan;
        sg::PlayerManager playerMan;
        sg::TeamManager teamMan;
        sf::RenderWindow window;
        sf::View arenaView;
        sf::View dashView;
        
        sf::Vector2f dispDim;
        sf::Uint32 connectionId;
        sf::Clock stateClock;
        sf::Clock minionClock;
        bool connected;
        bool gameDone;
        bool gameWindowHasFocus;
        bool isServer;

    };
}

#endif

