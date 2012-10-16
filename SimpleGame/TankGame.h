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
        

        }

        void sendState(sg::Comm & comm, sf::Uint32 id, sf::Vector2f velocity, float bodyAngle, float turretAngle);
        
        //void execute(){
        //    onInit();
        //    while (!gameDone){
        //        onEvent();
        //        onLoop();
        //        onRender();
        //    }
        //    onCleanup();
        //}

        
        void init();
        void onRemoteEvent(sg::CommPacket & packet);
        bool onLocalEvent(sf::Event & event);
        void onLoop(sf::Time & frameTime);
        void onRender();
        void onCleanup();



        ConnectionState connectionState;
        sf::Uint32 connectionId;
        int aniIndex;
        sf::Clock aniClock;
        sf::RenderWindow window;
        sg::Comm comm;
        Player player1;
        Player player2;
        sg::Floor floor;
        bool gameDone;
    };
}

#endif

