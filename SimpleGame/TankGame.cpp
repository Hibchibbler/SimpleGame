#include "TankGame.h"

void sg::TankGame::sendState(sg::Comm & comm, sf::Uint32 id, sf::Vector2f velocity, float bodyAngle, float turretAngle)
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
}

 void sg::TankGame::init(){
    //Load floor
    floor.Load();

    // Load bitmaps for player 1(Local)
    player1.bodyFrames.reserve(2);

    player1.bodyFrames.push_back(Frame());
    player1.bodyFrames[0].image.loadFromFile("BlueBody_red.png");
    player1.bodyFrames[0].image.createMaskFromColor(sf::Color::Cyan,0);
    player1.bodyFrames[0].tex.loadFromImage(player1.bodyFrames[0].image);

    player1.bodyFrames.push_back(Frame());
    player1.bodyFrames[1].image.loadFromFile("BlueBody_green.png");
    player1.bodyFrames[1].image.createMaskFromColor(sf::Color::Cyan,0);
    player1.bodyFrames[1].tex.loadFromImage(player1.bodyFrames[1].image);

    player1.bodySprite.setTexture(player1.bodyFrames[0].tex);
    player1.bodySprite.setOrigin(40,61);
    player1.bodySprite.scale(0.6f,0.6f);

    player1.turretImage.loadFromFile("BlueTurret.png");
    player1.turretImage.createMaskFromColor(sf::Color::Cyan,0);
    player1.turretTex.loadFromImage(player1.turretImage);
    player1.turretSprite.setTexture(player1.turretTex);
    player1.turretSprite.setOrigin(27,90);
    player1.turretSprite.scale(0.6f,0.6f);


    //Load bitmaps for player 2(Remote
    player2.bodyFrames.reserve(2);

    player2.bodyFrames.push_back(Frame());
    player2.bodyFrames[0].image.loadFromFile("RedBody_red.png");
    player2.bodyFrames[0].image.createMaskFromColor(sf::Color::Cyan,0);
    player2.bodyFrames[0].tex.loadFromImage(player2.bodyFrames[0].image);

    player2.bodyFrames.push_back(Frame());
    player2.bodyFrames[1].image.loadFromFile("RedBody_green.png");
    player2.bodyFrames[1].image.createMaskFromColor(sf::Color::Cyan,0);
    player2.bodyFrames[1].tex.loadFromImage(player2.bodyFrames[1].image);

    player2.bodySprite.setTexture(player2.bodyFrames[0].tex);
    player2.bodySprite.setOrigin(40,61);
    player2.bodySprite.scale(0.6f,0.6f);

    player2.turretImage.loadFromFile("RedTurret.png");
    player2.turretImage.createMaskFromColor(sf::Color::Cyan,0);
    player2.turretTex.loadFromImage(player2.turretImage);
    player2.turretSprite.setTexture(player2.turretTex);
    player2.turretSprite.setOrigin(27,90);
    player2.turretSprite.scale(0.6f,0.6f);
    
}
void sg::TankGame::onRemoteEvent(sg::CommPacket & packet){
    //some GamePackets have an ID that is indicative of the socket on
    //to which the packet pertains.
    sf::Uint32 packetType;
    packet.packet >> packetType;
    switch (packetType){
    case sg::CommPacket::Acceptance:{
        sf::Uint32 id;
        std::string msg;
        packet.packet >> id;
        packet.packet >> msg;
        cout << "Acceptance: " << msg << endl;
        connectionId = packet.connectionId;
        connectionState = CONNECTED;
        break;
    }case sg::CommPacket::Disconnect:{
        sf::Uint32 id;
        std::string msg;
        packet.packet >> id;
        packet.packet >> msg;
        cout << "Disconnect: " << msg << endl;
        break;
    }case sg::CommPacket::Data:{
        //cout << "Data" << endl;
        std::string msg;
        //Get other player's tank  position metrics
        packet.packet >> player2.bodyAngle;
        packet.packet >> player2.turretAngle;
        packet.packet >> player2.velocity.x;
        packet.packet >> player2.velocity.y;
        cout << "Rx'd on " << packet.connectionId << " : " << player2.velocity.x << ", " << player2.velocity.y << endl;
        break;
    }case sg::CommPacket::Sent:{
        //cout << "Sent" << endl;
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
bool sg::TankGame::onLocalEvent(sf::Event & event){
    switch (event.type){
        case sf::Event::MouseWheelMoved:{
            //tankGame.player1.throttle += evnt.mouseWheel.delta;
            break;
        }case sf::Event::MouseMoved:{
                
            float dx,dy;
            sf::Vector2f centerOfTurretWorld;
            sf::Vector2i centerOfMouseCursorScreen(event.mouseMove.x,event.mouseMove.y);
            sf::Vector2f centerOfMouseCursorWorld;

            //Find turrent angle based on vector from tank origin to mouse.
            centerOfTurretWorld = player1.turretSprite.getPosition();

            centerOfMouseCursorWorld = window.convertCoords(centerOfMouseCursorScreen);

            dx = centerOfMouseCursorWorld.x - centerOfTurretWorld.x;
            dy = centerOfMouseCursorWorld.y - centerOfTurretWorld.y;
               
            player1.turretAngle =  (180.0f/3.14156f)*atan2(dy,dx);

            //Update other player of our changed state
            sendState(comm, connectionId,player1.velocity,player1.bodyAngle,player1.turretAngle);

            //mouseMoveSkipCur = (mouseMoveSkipCur + 1)%mouseMoveSkip;

            break;
        }case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::J)
            {//Join a games
                comm.StartClient(8280, "127.0.0.1");
            }else if (event.key.code == sf::Keyboard::H)
            {//Host a game
                comm.StartServer(8280);
            }else if (event.key.code == sf::Keyboard::W){
                player1.throttle += 1;
            }else if (event.key.code == sf::Keyboard::S){
                player1.throttle -= 1;
            }else if (event.key.code == sf::Keyboard::A)
            {//Rotating left
                player1.bodyAngle = (player1.bodyAngle - 2.0f);
                if (player1.bodyAngle >= 360.0f){
                    player1.bodyAngle = player1.bodyAngle - 360.0f;
                }
                sendState(comm, connectionId,player1.velocity,player1.bodyAngle,player1.turretAngle);
                    
            }else if (event.key.code == sf::Keyboard::D)
            {//Rotating right
                player1.bodyAngle = ((player1.bodyAngle + 2.0f));
                if (player1.bodyAngle >= 360.0f){
                    player1.bodyAngle = player1.bodyAngle - 360.0f;
                }
                sendState(comm, connectionId,player1.velocity,player1.bodyAngle,player1.turretAngle);
            }
                
            break;
        case sf::Event::Closed:
            //Stop either the server or the client
            comm.Stop();
            return false;
        }
    return true;
}
void sg::TankGame::onLoop(sf::Time & frameTime){
    //If enough time has elapsed, than go to next frame in animation
    float s = aniClock.getElapsedTime().asSeconds();
    if (s> 0.5f){
        player1.bodySprite.setTexture(player1.bodyFrames[aniIndex].tex);
        player2.bodySprite.setTexture(player2.bodyFrames[aniIndex].tex);

        aniIndex = (aniIndex + 1) % player1.bodyFrames.size();       
        aniClock.restart();
    }

    //Calculate our tank's orientation for this frame.
    player1.bodySprite.setRotation(0.0f);
    player1.bodySprite.rotate(player1.bodyAngle-90);

    player1.turretSprite.setRotation(0.0f);
    player1.turretSprite.rotate(player1.turretAngle-90);

    //calculate our tanks velocity based on throttle and orientation
    player1.velocity.x =  player1.throttle * (float)cos(player1.bodyAngle / (180/3.14156));
    player1.velocity.y =  player1.throttle * (float)sin(player1.bodyAngle / (180/3.14156));

    //position our tank based on elapsed time and current velocity.
    player1.bodySprite.move(player1.velocity.x*20*frameTime.asSeconds(),player1.velocity.y*20*frameTime.asSeconds());
    player1.turretSprite.move(player1.velocity.x*20*frameTime.asSeconds(),player1.velocity.y*20*frameTime.asSeconds());

    cout << player1.bodySprite.getPosition().x << ", " << player1.bodySprite.getPosition().y << endl;

    //Calculate other players tank orientation
    player2.bodySprite.setRotation(0.0f);
    player2.bodySprite.rotate(player2.bodyAngle-90);

    player2.turretSprite.setRotation(0.0f);
    player2.turretSprite.rotate(player2.turretAngle-90);

    //position other players tank
    player2.bodySprite.move(player2.velocity.x*20*frameTime.asSeconds(),player2.velocity.y*20*frameTime.asSeconds());
    player2.turretSprite.move(player2.velocity.x*20*frameTime.asSeconds(),player2.velocity.y*20*frameTime.asSeconds());


    sf::View newView(player1.bodySprite.getPosition(),sf::Vector2f(400.0f, 300.0f));//TODO: i'm not sure when setView is appropriate...
    window.setView(newView);
    
}
void sg::TankGame::onRender(){
    // Clear the screen (fill it with black color)
    window.clear();

    //Draw Floor
    for (int h = 0; h < floor.height;h++){
        for (int w = 0;w < floor.width;w++){
            sf::Vector2f curPos = floor.spriteTiles[h][w].getPosition();
            floor.spriteTiles[h][w].setPosition(curPos);
            window.draw(floor.spriteTiles[h][w]);
        }
    }
        
    //Draw Tanks
    window.draw(player1.bodySprite);
    window.draw(player2.bodySprite);
    window.draw(player1.turretSprite);
    window.draw(player2.turretSprite);

    // Display window contents on screen
    window.display();
}
void sg::TankGame::onCleanup(){}