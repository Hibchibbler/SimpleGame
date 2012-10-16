#include "TankGame.h"

int main(int argc, char **argv)
{

    //Instantiate the game state
    sg::TankGame tankGame;
    tankGame.init();
    
    //House keeping variables
    sf::Clock clock;

    sf::Time frameTime;
    sf::Time previousTime;
    sf::Time currentTime;
    sf::Time deltaTime;

    // Start game loop
    while (tankGame.window.isOpen()){

        // Handle Local Input
        sf::Event windowEvent;
        while (tankGame.window.pollEvent(windowEvent)){
            if (!tankGame.onLocalEvent(windowEvent)){
                tankGame.window.close();
            }
        }
        //Handle  Comm Input
        sg::CommPacket packet;
        while (tankGame.comm.Receive(packet)){
            tankGame.onRemoteEvent(packet);
        }

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
        sf::sleep(sf::milliseconds(50));

    }
    return EXIT_SUCCESS;
}



