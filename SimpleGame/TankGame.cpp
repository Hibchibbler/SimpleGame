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
    dash.load();
    dash.setHealth(100);
    dash.setVelocity(sf::Vector2f(0,0));
    dash.setPos(sf::Vector2f(0,0));

    //Load arenaMan
    arenaMan.Load((sf::Uint32)dispDim.x, (sf::Uint32)dispDim.y);
    
    
    
    playerMan.Load();

    //playerMan.addPlayer(0,arenaMan.getGarage(0));//Local - always
    //playerMan.addPlayer(1,arenaMan.getGarage(1));

    

    
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
        if (isServer)
        {
            playerMan.addPlayer(0,arenaMan.getGarage(0));
            playerMan.addPlayer(1,arenaMan.getGarage(1));
            //teamMan.team1.associate(
            teamMan.team1.garageState.position = arenaMan.getGarage(0);
            teamMan.team1.generator1State.position = arenaMan.getGenerator(0,0);

            //teamMan.team2.garageState.position = arenaMan.getGarage(1);
            //teamMan.team2.generator1State.position = arenaMan.getGenerator(1,0);
        }else{
            playerMan.addPlayer(0,arenaMan.getGarage(1));
            playerMan.addPlayer(1,arenaMan.getGarage(0));
            teamMan.team1.garageState.position = arenaMan.getGarage(1);
            teamMan.team1.generator1State.position = arenaMan.getGenerator(1,0);
            //teamMan.team2.garageState.position = arenaMan.getGarage(0);
            //teamMan.team2.generator1State.position = arenaMan.getGenerator(0,0);
        }
        teamMan.load(arenaMan, isServer);
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
        int numMinions = 0;
        int gameDataType;

        packet.packet >> gameDataType;
        
        if (gameDataType == sg::TankGame::State){
            //Recieved a packet containing other players' state
            packet.packet >> playerMan.players[1].tank.tankState.bodyAngle;
            packet.packet >> playerMan.players[1].tank.tankState.turretAngle;
            packet.packet >> playerMan.players[1].playerState.health;
            packet.packet >> playerMan.players[1].tank.tankState.position.x;
            packet.packet >> playerMan.players[1].tank.tankState.position.y;
            packet.packet >> numProjectiles;
            playerMan.players[1].projectiles.clear();
            //Create projectile sprites for each projectile the other player reports.
            //Player 2 projectiles
            for (int y = 0;y < numProjectiles;y++){
                Projectile p;
                packet.packet >> p.projectileState.position.x;
                packet.packet >> p.projectileState.position.y;
                packet.packet >> p.projectileState.velocity.x;
                packet.packet >> p.projectileState.velocity.y;

                p.sprite.setTexture(*playerMan.projectileImages[0].tex);
                p.sprite.scale(0.5,0.5);
                p.sprite.setOrigin(8,8);
                p.sprite.setPosition(p.projectileState.position);
                playerMan.players[1].projectiles.push_back(p);
            }
            //Team 2 minions
            teamMan.team2.minions.clear();
            packet.packet >> numMinions;
            for (int y = 0;y < numMinions;y++){
                Minion m;
                packet.packet >> m.minionState.position.x;
                packet.packet >> m.minionState.position.y;
                //std::cout << m.minionState.position.x << ", " << m.minionState.position.y << std::endl;
                m.minionState.power = 1;//hack
                m.minionSprite.setPosition(m.minionState.position);
                m.minionSprite.setTexture(*teamMan.minionImages1[0].tex);
                teamMan.team2.minions.push_back(m);
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

    //This id indicates to Comm, which connection 
    //that this GamePacket will be sent on.
    //It isn't really used in a two player, one connection scenario.    
    packet.connectionId = connectionId;
    
    packet.packet << (sf::Uint32)sg::CommEvent::Data;
    packet.packet << (sf::Uint32)sg::TankGame::State;
    packet.packet << playerMan.players[0].tank.tankState.bodyAngle;
    packet.packet << playerMan.players[0].tank.tankState.turretAngle;
    packet.packet << playerMan.players[0].playerState.health;
    packet.packet << playerMan.players[0].tank.tankState.position.x;
    packet.packet << playerMan.players[0].tank.tankState.position.y;
    packet.packet << playerMan.players[0].projectiles.size();
    std::vector<Projectile>::iterator proj = playerMan.players[0].projectiles.begin();
    while (proj != playerMan.players[0].projectiles.end()){
        packet.packet << proj->projectileState.position.x;
        packet.packet << proj->projectileState.position.y;
        packet.packet << proj->projectileState.velocity.x;
        packet.packet << proj->projectileState.velocity.y;
        proj++;
    }

    packet.packet << teamMan.team1.minions.size();
    std::list<Minion>::iterator minion = teamMan.team1.minions.begin();
    while (minion != teamMan.team1.minions.end()){
        packet.packet << minion->minionState.position.x;
        packet.packet << minion->minionState.position.y;
        minion++;
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
    if (!connected)
        return false;
    //We poll keyboard instead of relying on bios keyboard rate
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        playerMan.players[0].tank.tankState.throttle += 1;
        if (playerMan.players[0].tank.tankState.throttle > 25)
            playerMan.players[0].tank.tankState.throttle = 25;
    }
    

    //max speed lower in reverse
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        playerMan.players[0].tank.tankState.throttle -= 1;
        if (playerMan.players[0].tank.tankState.throttle < -6)
            playerMan.players[0].tank.tankState.throttle = -6;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        //Rotating left
        playerMan.players[0].tank.tankState.bodyAngle = playerMan.players[0].tank.tankState.bodyAngle -  5;
        if (playerMan.players[0].tank.tankState.bodyAngle >= 360.0f || playerMan.players[0].tank.tankState.bodyAngle <= -360.0f ){
            playerMan.players[0].tank.tankState.bodyAngle = 0;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        //Rotating right
        playerMan.players[0].tank.tankState.bodyAngle = playerMan.players[0].tank.tankState.bodyAngle +  5;
        if (playerMan.players[0].tank.tankState.bodyAngle >= 360.0f || playerMan.players[0].tank.tankState.bodyAngle <= -360.0f ){
            playerMan.players[0].tank.tankState.bodyAngle = 0;
        }
    }

    //update player 1 velocity based on updated throttle and body angle.
    playerMan.players[0].tank.tankState.velocity.x =  playerMan.players[0].tank.tankState.throttle * (float)cos(playerMan.players[0].tank.tankState.bodyAngle / (180/3.14156));
    playerMan.players[0].tank.tankState.velocity.y =  playerMan.players[0].tank.tankState.throttle * (float)sin(playerMan.players[0].tank.tankState.bodyAngle / (180/3.14156));
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        //Create a new projectile
        Projectile p;
        p.projectileState.id = playerMan.players[0].playerState.projectileCount;
        playerMan.players[0].playerState.projectileCount++;


        p.sprite.setTexture(*playerMan.projectileImages[0].tex);
        p.sprite.scale(0.5,0.5);
        p.sprite.setOrigin(8,8);
        p.sprite.setPosition(playerMan.players[1].tank.tankState.position);
        playerMan.players[1].projectiles.push_back(p);


        
        //position projectile on the turret
        p.projectileState.position = playerMan.players[0].tank.turret.getPosition();
        //set the projectile's velocity, based on the turret angle
        p.projectileState.velocity.x = playerMan.players[0].tank.tankState.velocity.x + 25 * (float)cos(playerMan.players[0].tank.tankState.turretAngle / (180/3.14156));
        p.projectileState.velocity.y = playerMan.players[0].tank.tankState.velocity.y + 25 * (float)sin(playerMan.players[0].tank.tankState.turretAngle / (180/3.14156));
        //translate projectile to appear to come from turret tip
        p.projectileState.position.x += p.projectileState.velocity.x;
        p.projectileState.position.y += p.projectileState.velocity.y;

        p.sprite.setPosition(p.projectileState.position);

        //Add projectile to in-flight list
        playerMan.players[0].projectiles.push_back(p);
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
            //store the new
            dispDim.x  = (float)event.size.width;
            dispDim.y  = (float)event.size.height;
            break;
        }case sf::Event::MouseMoved:{
            if (!connected)
                break;
            float dx,dy;
            sf::Vector2f centerOfTurretWorld;
            sf::Vector2i mouseCursorScreen(event.mouseMove.x,event.mouseMove.y);
            sf::Vector2f mouseCursorWorld;

            //Find turrent angle based on vector from tank origin to mouse.
            centerOfTurretWorld = playerMan.players[0].tank.turret.getPosition();
            mouseCursorWorld = window.convertCoords(mouseCursorScreen);
            dx = mouseCursorWorld.x - centerOfTurretWorld.x;
            dy = mouseCursorWorld.y - centerOfTurretWorld.y;
            playerMan.players[0].tank.tankState.turretAngle =  (180.0f/3.14156f)*atan2(dy,dx);
         
            break;
        }case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::J)
            {//Join a games
                comm.StartClient(8280, "127.0.0.1");
                isServer = false;
            }else if (event.key.code == sf::Keyboard::H)
            {//Host a game
                comm.StartServer(8280);
                isServer = true;
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

    if (!connected)
        return;

    if (minionClock.getElapsedTime().asMilliseconds() > 700){
        Minion m;
        m.minionSprite.setTexture(*teamMan.minionImages1[0].tex);
        m.minionState.position = teamMan.team1.generator1State.position;
        std::cout << m.minionState.position.x << ", " << m.minionState.position.y << std::endl;
        int g = rand()%4;
        if (isServer){
            switch(g){
            case 0:
                m.minionState.velocity.x = 3;
                m.minionState.velocity.y = 4;
                break;
            case 1:
                m.minionState.velocity.x = 2;
                m.minionState.velocity.y = 5;
                break;
            case 2:
                m.minionState.velocity.x = 5;
                m.minionState.velocity.y = 2;
                break;
            case 3:
                m.minionState.velocity.x = 4;
                m.minionState.velocity.y = 3;
                break;
            }
            teamMan.team1.minions.push_back(m);
        }else{
            switch(g){
            case 0:
                m.minionState.velocity.x = -3;
                m.minionState.velocity.y = -4;
                break;
            case 1:
                m.minionState.velocity.x = -2;
                m.minionState.velocity.y = -5;
                break;
            case 2:
                m.minionState.velocity.x = -5;
                m.minionState.velocity.y = 2;
                break;
            case 3:
                m.minionState.velocity.x = -4;
                m.minionState.velocity.y = -3;
                break;
            }
            teamMan.team2.minions.push_back(m);
        }

        
        //teamMan.team1.minions.push_back(m);

        minionClock.restart();
    }
    
    

    //Calculate our tank's orientation for this frame.
    playerMan.players[0].tank.body.setRotation(0.0f);
    playerMan.players[0].tank.body.rotate(playerMan.players[0].tank.tankState.bodyAngle-90);

    playerMan.players[0].tank.turret.setRotation(0.0f);
    playerMan.players[0].tank.turret.rotate(playerMan.players[0].tank.tankState.turretAngle-90);

    //calculate our tanks velocity based on throttle and orientation
    playerMan.players[0].tank.body.move   (playerMan.players[0].tank.tankState.velocity.x*20*frameTime.asSeconds(),
                                                 playerMan.players[0].tank.tankState.velocity.y*20*frameTime.asSeconds());
    
    playerMan.players[0].tank.turret.move (playerMan.players[0].tank.tankState.velocity.x*20*frameTime.asSeconds(),
                                                 playerMan.players[0].tank.tankState.velocity.y*20*frameTime.asSeconds());

    playerMan.players[0].tank.tankState.position = playerMan.players[0].tank.body.getPosition();

    //Calculate other players tank orientation
    playerMan.players[1].tank.body.setRotation(0.0f);
    playerMan.players[1].tank.body.rotate(playerMan.players[1].tank.tankState.bodyAngle-90);

    playerMan.players[1].tank.turret.setRotation(0.0f);
    playerMan.players[1].tank.turret.rotate(playerMan.players[1].tank.tankState.turretAngle-90);

    //position other players tank
    playerMan.players[1].tank.body.setPosition(playerMan.players[1].tank.tankState.position);
    playerMan.players[1].tank.turret.setPosition(playerMan.players[1].tank.tankState.position);

    //Projectiles - position and orient player 1 projectiles
    std::vector<Projectile>::iterator proj = playerMan.players[0].projectiles.begin();
    while (proj != playerMan.players[0].projectiles.end()){
        proj->sprite.move(proj->projectileState.velocity.x*20*frameTime.asSeconds(),proj->projectileState.velocity.y*20*frameTime.asSeconds());
        proj->projectileState.position = proj->sprite.getPosition();

        //remove projectiles whose position is beyond these extremes
        //this will automatically propagate to player 2, so, player2 doesn't need this treatment locally.
        if (proj->projectileState.position.x > 4000 || proj->projectileState.position.y > 4000  ||
            proj->projectileState.position.x < -4000 || proj->projectileState.position.y < -4000  ){
            proj = playerMan.players[0].projectiles.erase(proj);
            //cout << "Smlap" << endl;
        }else if (proj->sprite.getGlobalBounds().intersects(playerMan.players[1].tank.body.getGlobalBounds())){
            //remove projectiles that hit other player
            proj = playerMan.players[0].projectiles.erase(proj);
            //cout << "Smash" << endl;
        }else
            proj++;
    }

    //Projectiles - position and orient player 2 projectiles.
    proj = playerMan.players[1].projectiles.begin();
    while (proj != playerMan.players[1].projectiles.end()){
        //Check if player 2 projectiles are hitting player1
        if (proj->sprite.getGlobalBounds().intersects(playerMan.players[0].tank.body.getGlobalBounds())){
            playerMan.players[0].playerState.health--;
            cout << "Ouch" << endl;
            //restate the dash Health 
            dash.setHealth(playerMan.players[0].playerState.health);
            proj = playerMan.players[1].projectiles.erase(proj);
        }else{
            proj->sprite.move(proj->projectileState.velocity.x*20*frameTime.asSeconds(),proj->projectileState.velocity.y*20*frameTime.asSeconds());
            proj->projectileState.position = proj->sprite.getPosition();
            proj++;
        }
    }
    
    //Local minions
    std::list<Minion>::iterator minion = teamMan.team1.minions.begin();
    for (;minion != teamMan.team1.minions.end();){
        minion->minionSprite.move(minion->minionState.velocity.x*20*frameTime.asSeconds(),
                                  minion->minionState.velocity.y*20*frameTime.asSeconds());
        minion->minionState.position = minion->minionSprite.getPosition();
        if (minion->minionState.position.x > 4000 || minion->minionState.position.y > 4000  ||
            minion->minionState.position.x < -4000 || minion->minionState.position.y < -4000  ){
            minion = teamMan.team1.minions.erase(minion);
            //cout << "Smlap" << endl;
        }else if (minion->minionSprite.getGlobalBounds().intersects(playerMan.players[1].tank.body.getGlobalBounds())){
            //remove projectiles that hit other player
            minion = teamMan.team1.minions.erase(minion);
            //cout << "Smash" << endl;
        }else
            minion++;
    }
    //Other player minions
    minion = teamMan.team2.minions.begin();
    for (;minion != teamMan.team2.minions.end();){
        minion->minionSprite.setPosition(minion->minionState.position);
        minion->minionState.position = minion->minionSprite.getPosition();
        //if (minion->minionState.position.x > 4000 || minion->minionState.position.y > 4000  ||
        //    minion->minionState.position.x < -4000 || minion->minionState.position.y < -4000  ){
        //    minion = teamMan.team1.minions.erase(minion);
        //    //cout << "Smlap" << endl;
        //}else if (minion->minionSprite.getGlobalBounds().intersects(playerMan.players[0].tank.body.getGlobalBounds())){
        //    
        //    playerMan.players[0].playerState.health--;
        //    cout << "Owy" << endl;
        //    //restate the dash Health 
        //    dash.setHealth(playerMan.players[0].playerState.health);
        //    
        //    //remove projectiles that hit other player
        //    minion = teamMan.team2.minions.erase(minion);
        //    //cout << "Smash" << endl;
        //}else
            minion++;
    }
    

    //Update the Dashboard
    dash.setHealth(playerMan.players[0].playerState.health);
    dash.setAngles(playerMan.players[0].tank.tankState.bodyAngle,playerMan.players[0].tank.tankState.turretAngle);
    dash.setPos(playerMan.players[0].tank.tankState.position);
    dash.setVelocity(playerMan.players[0].tank.tankState.velocity);
    dash.setHealth2(playerMan.players[1].playerState.health);

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
    if (connected){
        //Center arenaView on current position of player 1
        arenaView.setCenter(playerMan.players[0].tank.body.getPosition());
        window.setView(arenaView);

        //Draw Floor
        arenaMan.draw(window);

        
        //Draw Tanks
        window.draw(playerMan.players[0].tank.body);
        window.draw(playerMan.players[1].tank.body);
        window.draw(playerMan.players[0].tank.turret);
        window.draw(playerMan.players[1].tank.turret);

        //Draw Player 1 projectiles
        std::vector<Projectile>::iterator proj = playerMan.players[0].projectiles.begin();
        for(;proj != playerMan.players[0].projectiles.end();proj++){
            window.draw(proj->sprite);
        }

        //Draw player 2 projectiles
        proj = playerMan.players[1].projectiles.begin();
        for(;proj != playerMan.players[1].projectiles.end();proj++){
            window.draw(proj->sprite);
        }

        std::list<Minion>::iterator minion = teamMan.team1.minions.begin();
        for (;minion != teamMan.team1.minions.end();minion++){
            window.draw(minion->minionSprite);//.setPosition(minion->minionState.position);
        }

        minion = teamMan.team2.minions.begin();
        for (;minion != teamMan.team2.minions.end();minion++){
            window.draw(minion->minionSprite);//.setPosition(minion->minionState.position);
        }
    
        //Set View for drawing the HUD.
        //we use a different view because we don't want the dashboard to scale when zooming in and out.    
    }
    //Draw all the HUD stuff
    window.setView(dashView);    
    window.draw(dash.dashSprite);
    window.draw(dash.health);
    window.draw(dash.velocity);
    window.draw(dash.position);
    window.draw(dash.angles);
    window.draw(dash.health2);

    //Reset view to the state before we drew the dashboard
    window.setView(arenaView);

    //Finally, Display window contents on screen
    window.display();


}
void sg::TankGame::onCleanup(){

}