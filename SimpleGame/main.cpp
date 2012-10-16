#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>

#include "Comm.h"

//#include "Client.h"
//#include "Server.h"

#include <iostream>
#include <string>
#include <math.h>
using std::cout;
using std::endl;

enum ConnectionState{
    NOT_CONNECTED,
    CONNECTED
};
class Frame
{
public:
    sf::Image image;
    sf::Texture tex;
};
class Player
{
public:
    Player(){
        velocity.x = 0;
        velocity.y = 0;
        bodyAngle = 0.0f;
        throttle = 0.0f;
        bodyAngle = 0.0f;
        turretAngle = 0.0f;
    }
    std::string name;
    std::vector<Frame> bodyFrames;
    sf::Image bodyImage;
    sf::Image turretImage;
    sf::Texture bodyTex;
    sf::Texture turretTex;
    sf::Sprite bodySprite;
    sf::Sprite turretSprite;
    sf::Vector2f velocity;
    float throttle;
    float bodyAngle;
    float turretAngle;
};



class Floor
{
public:
    void Load(){
        width = 4;
        height = 3;

        imageTiles.push_back(new sf::Image());
        imageTiles.back()->loadFromFile("floor1.png");

        texTiles.push_back(new sf::Texture());
        texTiles.back()->loadFromImage(*imageTiles.back());

        
        
        for (int h = 0;h < height;h++){
            for (int w = 0; w < width;w++){
                spriteTiles[h][w].setTexture(*texTiles.back());
                //spriteTiles[h][w].scale(0.75f,0.75f);//32
                spriteTiles[h][w].setPosition(w*128-200,h*128-150);//TODO: i do not know why 200 and 150 need to be there for the floor to line up on the top and left edge of view
            }
        }
    }

    std::vector<sf::Image*> imageTiles;
    std::vector<sf::Texture*> texTiles;
    sf::Sprite spriteTiles[7][7];
    int width,height;
};

class TankGame
{
public:
    TankGame(){
        connectionState = NOT_CONNECTED;
    }

    ConnectionState connectionState;
    sf::Uint32 connectionId;

    Player player1;
    Player player2;
};

//std::queue<EventArg> NetworkEvents;


void SendLocation(sg::Comm & comm, sf::Uint32 id, sf::Vector2f velocity, float bodyAngle, float turretAngle)
{
    sg::CommPacket packet;
    packet.connectionId = id;//This id is indicative of the socket 
                             //which this GamePacket will be sent on
    packet.packet << (sf::Uint32)sg::CommPacket::Data;
    packet.packet << bodyAngle;
    packet.packet << turretAngle;
    packet.packet << velocity.x;
    packet.packet << velocity.y;
    comm.Send(packet);
    cout << "Sent(" << id << "): (" << velocity.x << ", " << velocity.y << ")" << endl;
}

int main(int argc, char **argv)
{
    //House keeping variables
    sf::Clock clock;
    sf::Clock animationClock;
    sf::Time totalTime;
    sf::Time previousTime;
    sf::Time currentTime;
    sf::Time deltaTime;
    bool done = false;
    int animationFrame = 0;
    Floor floor;
    floor.Load();
    //Instantiate the game state module
    TankGame tankGame;
    
    //Instantiate the communication module
    sg::Comm comm;

    // Create the main rendering window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Tank Game - v0.1");
    
    sf::View newView(sf::Vector2f(0.0f,0.0f),sf::Vector2f(400.0f, 300.0f));
    App.setView(newView);

    // Load bitmaps for each player.
    tankGame.player1.bodyFrames.reserve(2);

    tankGame.player1.bodyFrames.push_back(Frame());
    tankGame.player1.bodyFrames[0].image.loadFromFile("BlueBody_red.png");
    tankGame.player1.bodyFrames[0].image.createMaskFromColor(sf::Color::Cyan,0);
    tankGame.player1.bodyFrames[0].tex.loadFromImage(tankGame.player1.bodyFrames[0].image);

    tankGame.player1.bodyFrames.push_back(Frame());
    tankGame.player1.bodyFrames[1].image.loadFromFile("BlueBody_green.png");
    tankGame.player1.bodyFrames[1].image.createMaskFromColor(sf::Color::Cyan,0);
    tankGame.player1.bodyFrames[1].tex.loadFromImage(tankGame.player1.bodyFrames[1].image);

    tankGame.player1.bodySprite.setTexture(tankGame.player1.bodyFrames[0].tex);
    tankGame.player1.bodySprite.setOrigin(40,61);
    tankGame.player1.bodySprite.scale(0.6f,0.6f);

    tankGame.player1.turretImage.loadFromFile("BlueTurret.png");
    tankGame.player1.turretImage.createMaskFromColor(sf::Color::Cyan,0);
    tankGame.player1.turretTex.loadFromImage(tankGame.player1.turretImage);
    tankGame.player1.turretSprite.setTexture(tankGame.player1.turretTex);
    tankGame.player1.turretSprite.setOrigin(27,90);
    tankGame.player1.turretSprite.scale(0.6f,0.6f);

    tankGame.player2.bodyFrames.reserve(2);

    tankGame.player2.bodyFrames.push_back(Frame());
    tankGame.player2.bodyFrames[0].image.loadFromFile("RedBody_red.png");
    tankGame.player2.bodyFrames[0].image.createMaskFromColor(sf::Color::Cyan,0);
    tankGame.player2.bodyFrames[0].tex.loadFromImage(tankGame.player2.bodyFrames[0].image);

    tankGame.player2.bodyFrames.push_back(Frame());
    tankGame.player2.bodyFrames[1].image.loadFromFile("RedBody_green.png");
    tankGame.player2.bodyFrames[1].image.createMaskFromColor(sf::Color::Cyan,0);
    tankGame.player2.bodyFrames[1].tex.loadFromImage(tankGame.player2.bodyFrames[1].image);

    tankGame.player2.bodySprite.setTexture(tankGame.player2.bodyFrames[0].tex);
    tankGame.player2.bodySprite.setOrigin(40,61);
    tankGame.player2.bodySprite.scale(0.6f,0.6f);

    tankGame.player2.turretImage.loadFromFile("RedTurret.png");
    tankGame.player2.turretImage.createMaskFromColor(sf::Color::Cyan,0);
    tankGame.player2.turretTex.loadFromImage(tankGame.player2.turretImage);
    tankGame.player2.turretSprite.setTexture(tankGame.player2.turretTex);
    tankGame.player2.turretSprite.setOrigin(27,90);
    tankGame.player2.turretSprite.scale(0.6f,0.6f);
    
    const int mouseMoveSkip = 3;
    int mouseMoveSkipCur = 0;
    // Start game loop
    while (App.isOpen())
    {
        // Handle Local Input
        sf::Event evnt;
        
        
        while (App.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::MouseWheelMoved:{
                //tankGame.player1.throttle += evnt.mouseWheel.delta;
                break;
            }case sf::Event::MouseMoved:{
                
                float dx,dy;
                sf::Vector2f centerOfTurretWorld;
                sf::Vector2i centerOfMouseCursorScreen(evnt.mouseMove.x,evnt.mouseMove.y);
                sf::Vector2f centerOfMouseCursorWorld;

                //Find turrent angle based on vector from tank origin to mouse.
                centerOfTurretWorld = tankGame.player1.turretSprite.getPosition();

                centerOfMouseCursorWorld = App.convertCoords(centerOfMouseCursorScreen);

                dx = centerOfMouseCursorWorld.x - centerOfTurretWorld.x;
                dy = centerOfMouseCursorWorld.y - centerOfTurretWorld.y;
               
                tankGame.player1.turretAngle =  (180.0f/3.14156f)*atan2(dy,dx);

                //Update other player of our changed state
                if (mouseMoveSkipCur == 0)
                    SendLocation(comm, tankGame.connectionId,tankGame.player1.velocity,tankGame.player1.bodyAngle,tankGame.player1.turretAngle);

                mouseMoveSkipCur = (mouseMoveSkipCur + 1)%mouseMoveSkip;

                break;
            }case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::J)
                {//Join a games
                    comm.StartClient(8280, "127.0.0.1");
                }else if (evnt.key.code == sf::Keyboard::H)
                {//Host a game
                    comm.StartServer(8280);
                }else if (evnt.key.code == sf::Keyboard::W){
                    tankGame.player1.throttle += 1;
                }else if (evnt.key.code == sf::Keyboard::S){
                    tankGame.player1.throttle -= 1;
                }else if (evnt.key.code == sf::Keyboard::A)
                {//Rotating left
                    tankGame.player1.bodyAngle = (tankGame.player1.bodyAngle - 2.0f);
                    if (tankGame.player1.bodyAngle >= 360.0f){
                        tankGame.player1.bodyAngle = tankGame.player1.bodyAngle - 360.0f;
                    }
                    SendLocation(comm, tankGame.connectionId,tankGame.player1.velocity,tankGame.player1.bodyAngle,tankGame.player1.turretAngle);
                    
                }else if (evnt.key.code == sf::Keyboard::D)
                {//Rotating right
                    tankGame.player1.bodyAngle = ((tankGame.player1.bodyAngle + 2.0f));
                    if (tankGame.player1.bodyAngle >= 360.0f){
                        tankGame.player1.bodyAngle = tankGame.player1.bodyAngle - 360.0f;
                    }
                    SendLocation(comm, tankGame.connectionId,tankGame.player1.velocity,tankGame.player1.bodyAngle,tankGame.player1.turretAngle);
                }
                
                break;
            case sf::Event::Closed:
                //Stop either the server or the client
                comm.Stop();
                // Close window : exit
                App.close();
                break;
            }
        }
        //Handle  Comm Input
        sg::CommPacket packet;
        while (comm.Receive(packet)){
            //some GamePackets have an ID that is indicative of the socket on
            //to which the packet pertains.
            sf::Uint32 packetType;
            packet.packet >> packetType;
            switch (packetType)
            {
            case sg::CommPacket::Acceptance:{
                sf::Uint32 id;
                std::string msg;
                packet.packet >> id;
                packet.packet >> msg;
                cout << "Acceptance: " << msg << endl;
                
                tankGame.connectionId = packet.connectionId;
                tankGame.connectionState = CONNECTED;
                break;
            }case sg::CommPacket::Disconnect:{
                sf::Uint32 id;
                std::string msg;
                packet.packet >> id;
                packet.packet >> msg;
                cout << "Disconnect: " << msg << endl;
                
                break;
            }case sg::CommPacket::Data:{
                cout << "Data" << endl;
                std::string msg;

                //Get other player's tank  position metrics
                packet.packet >> tankGame.player2.bodyAngle;
                packet.packet >> tankGame.player2.turretAngle;
                packet.packet >> tankGame.player2.velocity.x;
                packet.packet >> tankGame.player2.velocity.y;
                cout << "Data(" << packet.connectionId << "): " << tankGame.player2.velocity.x << ", " << tankGame.player2.velocity.y << endl;
                  
                break;
            }case sg::CommPacket::Sent:{
                cout << "Sent" << endl;
                break;
            }case sg::CommPacket::Error:{
                sf::Uint32 id;
                std::string msg;
                packet.packet >> id;
                packet.packet >> msg;
                cout << "Error: " << msg << endl;
                break;
            }
            default:
                break;
            }
        }

        //Get our master timer stuff
        previousTime = currentTime;
        currentTime = clock.restart();
        deltaTime = currentTime - previousTime;
        totalTime += deltaTime;

        //If enough time has elapsed, than go to next frame in animation
        float s = animationClock.getElapsedTime().asSeconds();
        if (s> 0.5f){
            tankGame.player1.bodySprite.setTexture(tankGame.player1.bodyFrames[animationFrame].tex);
            tankGame.player2.bodySprite.setTexture(tankGame.player2.bodyFrames[animationFrame].tex);

            animationFrame = (animationFrame + 1) % tankGame.player1.bodyFrames.size();       
            animationClock.restart();
        }

        //Calculate our tank's orientation for this frame.
        tankGame.player1.bodySprite.setRotation(0.0f);
        tankGame.player1.bodySprite.rotate(tankGame.player1.bodyAngle-90);

        tankGame.player1.turretSprite.setRotation(0.0f);
        tankGame.player1.turretSprite.rotate(tankGame.player1.turretAngle-90);

        //calculate our tanks velocity based on throttle and orientation
        tankGame.player1.velocity.x =  tankGame.player1.throttle * (float)cos(tankGame.player1.bodyAngle / (180/3.14156));
        tankGame.player1.velocity.y =  tankGame.player1.throttle * (float)sin(tankGame.player1.bodyAngle / (180/3.14156));

        //position our tank based on elapsed time and current velocity.
        tankGame.player1.bodySprite.move(tankGame.player1.velocity.x*20*totalTime.asSeconds(),tankGame.player1.velocity.y*20*totalTime.asSeconds());
        tankGame.player1.turretSprite.move(tankGame.player1.velocity.x*20*totalTime.asSeconds(),tankGame.player1.velocity.y*20*totalTime.asSeconds());

        cout << tankGame.player1.bodySprite.getPosition().x << ", " << tankGame.player1.bodySprite.getPosition().y << endl;

        //Calculate other players tank orientation
        tankGame.player2.bodySprite.setRotation(0.0f);
        tankGame.player2.bodySprite.rotate(tankGame.player2.bodyAngle-90);

        tankGame.player2.turretSprite.setRotation(0.0f);
        tankGame.player2.turretSprite.rotate(tankGame.player2.turretAngle-90);

        //position other players tank
        tankGame.player2.bodySprite.move(tankGame.player2.velocity.x*20*totalTime.asSeconds(),tankGame.player2.velocity.y*20*totalTime.asSeconds());
        tankGame.player2.turretSprite.move(tankGame.player2.velocity.x*20*totalTime.asSeconds(),tankGame.player2.velocity.y*20*totalTime.asSeconds());


        sf::View newView(tankGame.player1.bodySprite.getPosition(),sf::Vector2f(400.0f, 300.0f));//TODO: i'm not sure when setView is appropriate...
        App.setView(newView);
        // Clear the screen (fill it with black color)
        App.clear();

        //Draw everything
        for (int h = 0; h < floor.height;h++){
            for (int w = 0;w < floor.width;w++){
                sf::Vector2f curPos = floor.spriteTiles[h][w].getPosition();
                floor.spriteTiles[h][w].setPosition(curPos);
                App.draw(floor.spriteTiles[h][w]);
            }
        }
        
        App.draw((sf::Sprite)tankGame.player1.bodySprite);
        App.draw((sf::Sprite)tankGame.player2.bodySprite);
        App.draw((sf::Sprite)tankGame.player1.turretSprite);
        App.draw((sf::Sprite)tankGame.player2.turretSprite);

        // Display window contents on screen
        App.display();

        //keep it from hogging cpu
        sf::sleep(sf::milliseconds(40));

    }
    App.close();

    return EXIT_SUCCESS;
}



