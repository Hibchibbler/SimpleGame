/**********************************************************************************
Tank Game
TankGame.h
Daniel Ferguson, Eddie Stranberg
Copyright 2012
**********************************************************************************/

#ifndef TankGame_h_
#define TankGame_h_

#include "Comm.h"
#include "Player.h"
#include "Floor.h"

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
        TankGame() : window(sf::VideoMode(800, 600, 32), "Tank Game - v0.1") {
            connectionState = NOT_CONNECTED;
            gameDone = false;
            aniIndex=0;
            sf::View newView(sf::Vector2f(0.0f,0.0f),sf::Vector2f(400.0f, 300.0f));
            window.setView(newView);
            gameWindowHasFocus = true;

        }

        void sendState();

        void onInit();
        void onRemoteEvent(sg::CommPacket & packet);
        bool onLocalEvent(sf::Event & event);
        bool onLocalInput();
        void onLoop(sf::Time & frameTime);
        void onRender();
        void onCleanup();

        //These are to be drawn to the screen as stats
        sf::Font gameFont;
        sf::Text player1Health;
        sf::Text player1Position;
        sf::Text player1Velocity;
        sf::Text player2Health;


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

