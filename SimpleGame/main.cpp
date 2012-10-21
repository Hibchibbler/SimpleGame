/**********************************************************************************
Tank Game
main.cpp
Daniel Ferguson, Eddie Stranberg
Copyright 2012
**********************************************************************************/

#include "TankGame.h"

int main(int argc, char **argv)
{

    //Instantiate the game state
    sg::TankGame tankGame;
    tankGame.onInit();
    
    //House keeping variables
    sf::Clock clock;
    sf::Clock localInputTimer;
    sf::Time frameTime;
    sf::Time previousTime;
    sf::Time currentTime;
    sf::Time deltaTime;

    // Start game loop
    while (tankGame.window.isOpen()){

        // Handle Local Events
        sf::Event windowEvent;
        while (tankGame.window.pollEvent(windowEvent)){
            if (!tankGame.onLocalEvent(windowEvent)){
                tankGame.window.close();
            }
        }

        //Handle  Comm Events
        sg::CommPacket packet;
        while (tankGame.comm.Receive(packet)){
            tankGame.onRemoteEvent(packet);
        }
 
        //Handle fast local input
        tankGame.onLocalInput();

        //Get our master timer stuff
        previousTime = currentTime;
        currentTime = clock.restart();
        deltaTime = currentTime - previousTime;
        frameTime += deltaTime;

        //Calculate position, and orientation of all things in the game.
        //and toggle through sprites for animation effect.
        tankGame.onLoop(frameTime);
        
        //Draw all thhings in the game
        tankGame.onRender();

        //keep this thread from hogging cpu
        //don't feel like heating up my cpu while testing..
        sf::sleep(sf::milliseconds(30));
    }

    tankGame.onCleanup();


    return EXIT_SUCCESS;
}



