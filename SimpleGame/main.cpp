#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>

#include "Comm.h"
#include "Floor.h"
#include "TankGame.h"
#include "Player.h"
//#include "Client.h"
//#include "Server.h"

#include <iostream>
#include <string>
#include <math.h>
using std::cout;
using std::endl;


int main(int argc, char **argv)
{
    //House keeping variables
    sf::Clock clock;
    sf::Clock animationClock;
    sf::Time fps;
    sf::Time previousTime;
    sf::Time currentTime;
    sf::Time deltaTime;
    bool done = false;
    int animationFrame = 0;
    sg::Floor floor;
    floor.Load();
    //Instantiate the game state module
    sg::TankGame tankGame;
    tankGame.init();
    //Instantiate the communication module
    

    // Create the main rendering window
    //sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Tank Game - v0.1");
    /*sf::View newView(sf::Vector2f(0.0f,0.0f),sf::Vector2f(400.0f, 300.0f));
    window.setView(newView);*/

    const int mouseMoveSkip = 3;
    int mouseMoveSkipCur = 0;
    // Start game loop
    while (tankGame.window.isOpen()){
        // Handle Local Input
        sf::Event evnt;
        while (tankGame.window.pollEvent(evnt)){
            if (!tankGame.onLocalEvent(evnt)){
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
        fps += deltaTime;

        tankGame.onLoop(fps);
        
        tankGame.onRender();
        //keep it from hogging cpu
        sf::sleep(sf::milliseconds(40));

    }
    return EXIT_SUCCESS;
}



