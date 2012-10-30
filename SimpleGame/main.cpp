/**********************************************************************************
Tank Game
main.cpp

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#include "TankGame.h"
#include "LogFile.h"

int main(int argc, char **argv)
{

    LogFile::get()->log(1, 0, "hello");

    //Instantiate the game state
    sg::TankGame tankGame(1024, 600);
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
        //LogFile::get()->log(1, 0, "Pwap");
        // Handle Local Events
        //go through all currently pending events from the window subsystem.
        //close, resize, mousemove(which we use to orient the turret)
        sf::Event windowEvent;
        while (tankGame.window.pollEvent(windowEvent)){
            if (!tankGame.onLocalEvent(windowEvent)){
                tankGame.window.close();
            }
        }

        //Handle Comm Events
        sg::CommEvent packet;
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
        sf::sleep(sf::milliseconds(20));
    }

    tankGame.onCleanup();

    LogFile::get()->log(1, 0, "Goodbye");
    return EXIT_SUCCESS;
}



