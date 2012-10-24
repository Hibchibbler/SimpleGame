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


    class TankGame
    {
    public:
        TankGame(float width, float height) : 
          window(sf::VideoMode((unsigned int)width,(unsigned int)height, 32), "Tank Game - v0.1")
        {
            connected = false;
            gameDone = false;
            aniIndex=0;
            arenaView = sf::View(sf::Vector2f(0.0f,0.0f),sf::Vector2f(width, height));//400.0f, 300.0f));
            hudView = sf::View(sf::Vector2f(0.0f,0.0f),sf::Vector2f(width, height));
            
            sf::FloatRect viewPort;
            viewPort.left = -0.36f;
            viewPort.top = 0.557f;
            viewPort.width = 0.70f;
            viewPort.height = 0.6f;
            hudView.setViewport(viewPort);
            window.setView(arenaView);
            gameWindowHasFocus = true;
            dispDim = sf::Vector2f(width, height);
        }

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
        sg::HUD hud;
        sf::Vector2f dispDim;
        sg::Player player1;
        sg::Player player2;
        sg::Floor floor;

        
        sf::Uint32 connectionId;
        int aniIndex;
        sf::Clock aniClock;
        sf::Clock stateClock;
        sf::RenderWindow window;

        bool connected;
        bool gameDone;
        bool gameWindowHasFocus;
        sf::View arenaView;
        sf::View hudView;
    };
}

#endif

