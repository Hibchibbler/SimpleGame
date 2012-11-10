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
    //Load Assets
    //sg::AssetManager am;
    //am.load();

    //Instantiate the game state
    sg::TankGame tankGame(800, 600);
    tankGame.doInit();
    
    //House keeping variables
    sf::Clock clock;
    sf::Clock localInputTimer;
    sf::Time frameTime;
    sf::Time previousTime;
    sf::Time currentTime;
    sf::Time deltaTime;
    bool firstIteration = true;
    // Start game loop
    while (tankGame.window.isOpen()){

        if (firstIteration){
            
            firstIteration=false;
        }
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
        tankGame.doLocalInput();

        //Get our master timer stuff
        previousTime = currentTime;
        currentTime = clock.restart();
        deltaTime = currentTime - previousTime;
        frameTime += deltaTime;

        //Calculate position, and orientation of all things in the game.
        //and toggle through sprites for animation effect.
        tankGame.doLoop(frameTime);
        
        //Draw all thhings in the game
        tankGame.doRender();

        //keep this thread from hogging cpu
        sf::sleep(sf::milliseconds(20));
    }

    tankGame.doCleanup();

    LogFile::get()->log(1, 0, "Goodbye");
    return EXIT_SUCCESS;
}



