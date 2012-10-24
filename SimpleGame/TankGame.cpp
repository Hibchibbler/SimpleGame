/**********************************************************************************
Tank Game
TankGame.cpp

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#include "TankGame.h"
#include <sstream>

 void sg::TankGame::onInit(){

    //Load Font
    hud.load();
    hud.setHealth(100);
    hud.setVelocity(sf::Vector2f(0,0));
    hud.setPos(sf::Vector2f(0,0));

    //Load floor
    floor.Load(dispDim.x, dispDim.y);


    
    //Load bitmaps for player 1(Local)
    //Load the projectile imagery
    player1.projectileFrame.image.loadFromFile("projectile.png");
    player1.projectileFrame.image.createMaskFromColor(sf::Color::Cyan,0);
    player1.projectileFrame.tex.loadFromImage(player1.projectileFrame.image);
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


    //Load bitmaps for player 2(Remote
    player2.projectileFrame.image.loadFromFile("projectile2.png");
    player2.projectileFrame.image.createMaskFromColor(sf::Color::Cyan,0);
    player2.projectileFrame.tex.loadFromImage(player2.projectileFrame.image);

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
void sg::TankGame::onRemoteEvent(sg::CommEvent & packet){
    //some GamePackets have an ID that is indicative of the socket on
    //to which the packet pertains.
    sf::Uint32 packetType;
    packet.packet >> packetType;
    switch (packetType){
    case sg::CommEvent::Acceptance:{
        sf::Uint32 id;
        std::string msg;
        packet.packet >> id;
        packet.packet >> msg;
        cout << "Acceptance: " << msg << endl;
        connectionId = id;
        connected = true;
        break;
    }case sg::CommEvent::Disconnect:{
        sf::Uint32 id;
        std::string msg;
        packet.packet >> id;
        packet.packet >> msg;
        connected = false;
        cout << "Disconnect: " << msg << endl;
        break;
    }case sg::CommEvent::Data:{
        //Get other player's tank  position metrics
        // We call the other player, player2
        int numProjectiles = 0;
        int gameDataType;

        packet.packet >> gameDataType;
        
        if (gameDataType == sg::TankGame::State){
            //Recieved a packet containing other players' state
            packet.packet >> player2.bodyAngle;
            packet.packet >> player2.turretAngle;
            packet.packet >> player2.health;
            packet.packet >> player2.position.x;
            packet.packet >> player2.position.y;
            packet.packet >> numProjectiles;
            player2.projectiles.clear();
            //Create projectile sprites for each projectile the other player reports.
            for (int y = 0;y < numProjectiles;y++){
                Projectile p;
                packet.packet >> p.position.x;
                packet.packet >> p.position.y;
                packet.packet >> p.velocity.x;
                packet.packet >> p.velocity.y;

                p.sprite.setTexture(player2.projectileFrame.tex);
                p.sprite.scale(0.5,0.5);
                p.sprite.setOrigin(8,8);
                p.sprite.setPosition(p.position);
                player2.projectiles.push_back(p);
            }
        }else{
            //This is where you'd add input handling for additional game data types
        }
        //cout << "Rx'd, player2, " << packet.connectionId << ", " << player2.bodyAngle << ", " << player2.turretAngle << ", " << player2.velocity.x << ", " << player2.velocity.y << endl;
        break;
    }case sg::CommEvent::Sent:{
        //cout << "Sent" << endl;
        break;
    }case sg::CommEvent::Error:{
        sf::Uint32 id;
        std::string msg;
        packet.packet >> id;
        packet.packet >> msg;
        connected = false;
        cout << "Error: " << msg << endl;
        break;
    }
    default:
        break;
    }
}


void sg::TankGame::sendState()
{
    sg::CommEvent packet;
    packet.connectionId = connectionId;//This id is indicative of the socket 
                                //which this GamePacket will be sent on
    packet.packet << (sf::Uint32)sg::CommEvent::Data;
    packet.packet << (sf::Uint32)sg::TankGame::State;
    packet.packet << player1.bodyAngle;
    packet.packet << player1.turretAngle;
    packet.packet << player1.health;
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
    if (connected){
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
        if (player1.throttle > 35)
            player1.throttle = 35;
    }
    

    //max speed lower in reverse
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        player1.throttle -= 1;
        if (player1.throttle < -6)
            player1.throttle = -6;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        //Rotating left
        player1.bodyAngle = player1.bodyAngle -  5;
        if (player1.bodyAngle >= 360.0f || player1.bodyAngle <= -360.0f ){
            player1.bodyAngle = 0;//player1.bodyAngle - 360.0f;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        //Rotating right
        player1.bodyAngle = player1.bodyAngle +  5;
        if (player1.bodyAngle >= 360.0f || player1.bodyAngle <= -360.0f ){
            player1.bodyAngle = 0;//player1.bodyAngle - 360.0f;
        }
    }

    //update player 1 velocity based on updated throttle and body angle.
    player1.velocity.x =  player1.throttle * (float)cos(player1.bodyAngle / (180/3.14156));
    player1.velocity.y =  player1.throttle * (float)sin(player1.bodyAngle / (180/3.14156));
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        //Create a new projectiles
        Projectile p;        
        p.id = player1.projectileCount;
        player1.projectileCount++;

        p.sprite.setTexture(player1.projectileFrame.tex);
        p.sprite.scale(0.5,0.5);
        p.sprite.setOrigin(16,16);
        
        //position projectile on the turret
        p.position = player1.turretSprite.getPosition();
        //set the projectile's velocity, based on the turret angle
        p.velocity.x =  25 * (float)cos(player1.turretAngle / (180/3.14156));
        p.velocity.y =  25 * (float)sin(player1.turretAngle / (180/3.14156));
        //translate projectile to appear to come from turret tip
        p.position.x += p.velocity.x;
        p.position.y += p.velocity.y;

        p.sprite.setPosition(p.position);

        //Add projectile to in-flight list
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
            //Increase the size of the arenaView.
            //This causes everything drawn to be scaled either bigger or smaller.
            float addend = event.mouseWheel.delta/15.0f;
            sf::Vector2f newSize = arenaView.getSize();
            newSize.x += 20.0f*event.mouseWheel.delta*(dispDim.x/dispDim.y);
            newSize.y += 20.0f*event.mouseWheel.delta;
            arenaView.setSize(newSize);
            break;
        }case sf::Event::Resized:{
            dispDim.x  = (float)event.size.width;
            dispDim.y  = (float)event.size.height;
            break;
        }case sf::Event::MouseMoved:{
            float dx,dy;
            sf::Vector2f centerOfTurretWorld;
            sf::Vector2i mouseCursorScreen(event.mouseMove.x,event.mouseMove.y);
            sf::Vector2f mouseCursorWorld;

            //Find turrent angle based on vector from tank origin to mouse.
            centerOfTurretWorld = player1.turretSprite.getPosition();
            mouseCursorWorld = window.convertCoords(mouseCursorScreen);
            dx = mouseCursorWorld.x - centerOfTurretWorld.x;
            dy = mouseCursorWorld.y - centerOfTurretWorld.y;
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
        if (proj->position.x > 4000 || proj->position.y > 4000  ||
            proj->position.x < -4000 || proj->position.y < -4000  ){
            proj = player1.projectiles.erase(proj);
            //cout << "Smlap" << endl;
        }
        //remove projectiles that hit other player
        else if (proj->position.x < player2.position.x+15 &&
                 proj->position.x > player2.position.x-15 &&
                 proj->position.y < player2.position.y+15 &&
                 proj->position.y > player2.position.y-15 ){
            proj = player1.projectiles.erase(proj);
            //cout << "Smash" << endl;
        }else
            proj++;
    }

    //Projectiles - position and orient player 2 projectiles.
    proj = player2.projectiles.begin();
    while (proj != player2.projectiles.end()){
        //Check if player 2 projectiles are hitting player1
        if (proj->position.x < player1.position.x+25 &&
            proj->position.x > player1.position.x-25 &&
            proj->position.y < player1.position.y+25 &&
            proj->position.y > player1.position.y-25 ){
            player1.health--;
            cout << "Ouch" << endl;
            //restate the hud Health 
            hud.setHealth(player1.health);
            proj = player2.projectiles.erase(proj);
        }else{
            proj->sprite.move(proj->velocity.x*20*frameTime.asSeconds(),proj->velocity.y*20*frameTime.asSeconds());
            proj->position = proj->sprite.getPosition();
            proj++;
        }
    }
    

    //Position all the HUD stuff.
    //Everything is relative to the upper left corner
    // of the dashSprite (currently, a brushed metal thing)
    hud.dashSprite.setPosition(0,0);
    sf::Vector2f dashPos = hud.dashSprite.getPosition();

    hud.setHealth(player1.health);
    hud.health.setPosition(0,0);

    hud.setAngles(player1.bodyAngle,player1.turretAngle);
    hud.angles.setPosition(0,20);

    hud.setPos(player1.position);
    hud.position.setPosition(0,60);

    hud.setVelocity(player1.velocity);
    hud.velocity.setPosition(0,100);

    hud.setHealth2(player2.health);
    hud.health2.setPosition(300,120);
    

    //Send player 1 state to remote client
    //at 50Hz
    if (stateClock.getElapsedTime().asMilliseconds() >= 20){
        sendState();
        stateClock.restart();
    }


}
void sg::TankGame::onRender(){
    // Clear the screen (fill it with black color)
    window.clear();
    
    //Center arenaView on current position of player 1
    arenaView.setCenter(player1.bodySprite.getPosition());
    window.setView(arenaView);

    //Draw Floor
    std::vector<sf::Sprite>::iterator sprite = floor.mapSprites.begin();
    for (; sprite != floor.mapSprites.end(); sprite++){
        window.draw(*sprite);
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
    
    //Set View for drawing the HUD.
    //we use a different view because we don't want the hud to scale when zooming in and out.    

    window.setView(hudView);

    

    //Draw all the HUD stuff
    window.draw(hud.dashSprite);
    window.draw(hud.health);
    window.draw(hud.velocity);
    window.draw(hud.position);
    window.draw(hud.angles);
    window.draw(hud.health2);

    //Reset view to the state before we drew the hud
    //window.setView(sf::View(player1.bodySprite.getPosition(),sf::Vector2f(displayDimensions.x, displayDimensions.y)));
    window.setView(arenaView);

    //Finally, Display window contents on screen
    window.display();


}
void sg::TankGame::onCleanup(){

}