/**********************************************************************************
Tank Game
TankGame.cpp
Daniel Ferguson, Eddie Stranberg
Copyright 2012
**********************************************************************************/

#include "TankGame.h"
#include <sstream>

 void sg::TankGame::onInit(){

     //Load Font
     //find some ttf somewhere on your system, and set the path
     //*don't forget to double up the '\'
     gameFont.loadFromFile("C:\\Xilinx\\13.2\\ISE_DS\\PlanAhead\\tps\\win64\\jre\\lib\\fonts\\LucidaBrightDemiBold.ttf");

     std::stringstream ss;
     ss << "Health: " << player1.health;
     player1Health.setString(ss.str());

     player1Health.setFont(gameFont);
     player1Health.scale(0.25,0.25);

    //Load floor
    floor.Load();

    //Load the one projectile we have..
    player1.projectileFrame.image.loadFromFile("projectile.png");
    player1.projectileFrame.image.createMaskFromColor(sf::Color::Cyan,0);
    player1.projectileFrame.tex.loadFromImage(player1.projectileFrame.image);
    
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

    player1.turretFrame.image.loadFromFile("BlueTurret.png");
    player1.turretFrame.image.createMaskFromColor(sf::Color::Cyan,0);
    player1.turretFrame.tex.loadFromImage(player1.turretFrame.image);

    player1.turretSprite.setTexture(player1.turretFrame.tex);
    player1.turretSprite.setOrigin(27,90);
    player1.turretSprite.scale(0.6f,0.6f);



    player2.projectileFrame.image.loadFromFile("projectile.png");
    player2.projectileFrame.image.createMaskFromColor(sf::Color::Cyan,0);
    player2.projectileFrame.tex.loadFromImage(player2.projectileFrame.image);

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

    player2.turretFrame.image.loadFromFile("RedTurret.png");
    player2.turretFrame.image.createMaskFromColor(sf::Color::Cyan,0);
    player2.turretFrame.tex.loadFromImage(player2.turretFrame.image);

    player2.turretSprite.setTexture(player2.turretFrame.tex);
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
        connectionId = id;
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
        //Get other player's tank  position metrics
        // We call the other player, player2
        int numProjectiles = 0;
        packet.packet >> player2.bodyAngle;
        packet.packet >> player2.turretAngle;
        packet.packet >> player2.position.x;
        packet.packet >> player2.position.y;
        packet.packet >> numProjectiles;
        player2.projectiles.clear();
        for (int y = 0;y < numProjectiles;y++){
            Projectile p;
            packet.packet >> p.position.x;
            packet.packet >> p.position.y;
            packet.packet >> p.velocity.x;
            packet.packet >> p.velocity.y;

            p.sprite.setTexture(player2.projectileFrame.tex);
            p.sprite.scale(0.5,0.5);
            p.sprite.setOrigin(8,8);

            //p.position.x += p.velocity.x;
            //p.position.y += p.velocity.y;
            p.sprite.setPosition(p.position);

            player2.projectiles.push_back(p);
        }
        //cout << "Rx'd, player2, " << packet.connectionId << ", " << player2.bodyAngle << ", " << player2.turretAngle << ", " << player2.velocity.x << ", " << player2.velocity.y << endl;
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

void sg::TankGame::sendState()
{
    sg::CommPacket packet;
    packet.connectionId = connectionId;//This id is indicative of the socket 
                                //which this GamePacket will be sent on
    packet.packet << (sf::Uint32)sg::CommPacket::Data;
    packet.packet << player1.bodyAngle;
    packet.packet << player1.turretAngle;
    packet.packet << player1.position.x;
    packet.packet << player1.position.y;
    packet.packet << player1.projectiles.size();
    std::vector<Projectile>::iterator proj = player1.projectiles.begin();
    while (proj != player1.projectiles.end()){
        packet.packet << proj->position.x;
        packet.packet << proj->position.y;
        packet.packet << proj->velocity.x;
        packet.packet << proj->velocity.y;
        proj++;
    }
    if (connectionState){
        comm.Send(packet);
        //cout << "Tx'd, player1, " << packet.connectionId << ", " << player1.bodyAngle << ", " << player1.turretAngle << ", " << player1.velocity.x << ", " << player1.velocity.y << endl;
    }
}

bool sg::TankGame::onLocalInput(){

    //If game window does not have focus, don't poll keyboard...
    //this is only useful when debugging two windowed instances of this game on one computer.
    if (gameWindowHasFocus != true)
        return false;

    //We poll keyboard instead of relying on bios keyboard rate
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        player1.throttle += 1;
        if (player1.throttle > 8)
            player1.throttle = 8;
    }
    

    //max speed lower in reverse
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        player1.throttle -= 1;
        if (player1.throttle < -6)
            player1.throttle = -6;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        //Rotating left
        player1.turnVelocity += 0.2;
        if (player1.turnVelocity  > 3.0)
            player1.turnVelocity  = 3.0;
        float magnitude = sqrt((player1.velocity.x*player1.velocity.x) + (player1.velocity.y*player1.velocity.y));
        player1.bodyAngle = player1.bodyAngle -  (player1.turnVelocity-magnitude);
        if (player1.bodyAngle >= 360.0f){
            player1.bodyAngle = 0;//player1.bodyAngle - 360.0f;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        //Rotating right
       player1.turnVelocity -= 0.2;
        if (player1.turnVelocity  < -3.0)
            player1.turnVelocity  = -3.0;
        float magnitude = sqrt((player1.velocity.x*player1.velocity.x) + (player1.velocity.y*player1.velocity.y));
        player1.bodyAngle = player1.bodyAngle +  (player1.turnVelocity-magnitude);
        if (player1.bodyAngle >= 360.0f){
            player1.bodyAngle = 0;//player1.bodyAngle - 360.0f;
        }
    }

    //update player 1 velocity based on updated throttle and body angle.
    player1.velocity.x =  player1.throttle * (float)cos(player1.bodyAngle / (180/3.14156));
    player1.velocity.y =  player1.throttle * (float)sin(player1.bodyAngle / (180/3.14156));
    
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        Projectile p;
        p.sprite.setTexture(player1.projectileFrame.tex);
        p.sprite.scale(0.5,0.5);
        p.sprite.setOrigin(16,16);
        p.position = player1.turretSprite.getPosition();
        //correct to find tip of cannon
        p.velocity.x =  25 * (float)cos(player1.turretAngle / (180/3.14156));
        p.velocity.y =  25 * (float)sin(player1.turretAngle / (180/3.14156));
        p.position.x += p.velocity.x;
        p.position.y += p.velocity.y;
        p.sprite.setPosition(p.position);
        
        player1.projectiles.push_back(p);
        cout << "Bang!" << endl;
    }
    return true;
}


bool sg::TankGame::onLocalEvent(sf::Event & event){
    switch (event.type){
        case sf::Event::LostFocus:
            gameWindowHasFocus = false;
            break;
        case sf::Event::GainedFocus:
            gameWindowHasFocus = true;
            break;
        case sf::Event::MouseWheelMoved:{
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

            break;
        }case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::J)
            {//Join a games
                comm.StartClient(8280, "127.0.0.1");
            }else if (event.key.code == sf::Keyboard::H)
            {//Host a game
                comm.StartServer(8280);
            }
            break;
        case sf::Event::Closed:
            //Stop either the server or the client
            window.close();
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

    //position our tank based on elapsed time and current velocity.
    player1.bodySprite.move(player1.velocity.x*20*frameTime.asSeconds(),player1.velocity.y*20*frameTime.asSeconds());
    player1.turretSprite.move(player1.velocity.x*20*frameTime.asSeconds(),player1.velocity.y*20*frameTime.asSeconds());
    player1.position = player1.bodySprite.getPosition();

    //Calculate other players tank orientation
    player2.bodySprite.setRotation(0.0f);
    player2.bodySprite.rotate(player2.bodyAngle-90);

    player2.turretSprite.setRotation(0.0f);
    player2.turretSprite.rotate(player2.turretAngle-90);

    //position other players tank
    player2.bodySprite.setPosition(player2.position);
    player2.turretSprite.setPosition(player2.position);


    //Projectiles - position and orient player 1 projectiles
    std::vector<Projectile>::iterator proj = player1.projectiles.begin();
    while (proj != player1.projectiles.end()){
        proj->sprite.move(proj->velocity.x*20*frameTime.asSeconds(),proj->velocity.y*20*frameTime.asSeconds());
        proj->position = proj->sprite.getPosition();

        //remove projectiles whose position is beyond these extremes
        //this will automatically propagate to player 2, so, player2 doesn't need this treatment locally.
        if (proj->position.x > 500 || proj->position.y > 500  ||
            proj->position.x < -500 || proj->position.y < -500  ){
            proj = player1.projectiles.erase(proj);
            cout << "Smlap" << endl;
        }else
            proj++;
    }

    //Projectiles - position and orient player 2 projectiles.
    proj = player2.projectiles.begin();
    while (proj != player2.projectiles.end()){
        proj->sprite.move(proj->velocity.x*20*frameTime.asSeconds(),proj->velocity.y*20*frameTime.asSeconds());
        proj->position = proj->sprite.getPosition();
        
        //Check if player 2 projectiles are hitting player1
        if (proj->position.x < player2.position.x+10 &&
            proj->position.x > player2.position.x-10 &&
            proj->position.y < player2.position.y+10 &&
            proj->position.y > player2.position.y-10 ){
            std::stringstream ss;
            player1.health--;
            ss << "Health: " << player2.health;
            player1Health.setString(ss.str());

            proj = player2.projectiles.erase(proj);
        }else{
            proj++;
        }
    }

    //Position Player 1 health status
    player1Health.setPosition(player1.bodySprite.getPosition());
    player1Health.move(-200,-150);

    //Send player 1 state to remote client
    //only every 100Hz
    if (stateClock.getElapsedTime().asMilliseconds() >= 10){
        sendState();
        stateClock.restart();
    }

    //View follows player 1
    sf::View newView(player1.bodySprite.getPosition(),sf::Vector2f(400.0f, 300.0f));
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

    //Draw Player 1 projectiles
    std::vector<Projectile>::iterator proj = player1.projectiles.begin();
    for(;proj != player1.projectiles.end();proj++){
        window.draw(proj->sprite);
    }

    //Draw player 2 projectiles
    proj = player2.projectiles.begin();
    for(;proj != player2.projectiles.end();proj++){
        window.draw(proj->sprite);
    }

    window.draw(player1Health);
    // Display window contents on screen
    window.display();
}
void sg::TankGame::onCleanup(){

}