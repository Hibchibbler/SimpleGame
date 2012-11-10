#ifndef Mechanics_h_
#define Mechanics_h_

#include <SFML/Graphics.hpp>
#include "TankGame.h"
#include "GameStage.h"

namespace sg
{
    class Mechanics : public sg::GameStage
    {
    public:
        Mechanics(){
        }
        sf::Uint32 onRemoteEvent(sg::TankGame & game, sg::CommEvent & e, sf::Uint32 packetType){
            //switch (packetType){
            //    case sg::CommEvent::Data:{
            //        //Get other player's tank  position metrics
            //        // We call the other player, player2
            //        int numProjectiles = 0;
            //        int numMinions = 0;
            //        int gameDataType;

            //        event.packet >> gameDataType;
        
            //        if (gameDataType == sg::TankGame::State){
            //            //Recieved a packet containing other players' state
            //            event.packet >> teamMan.teams[!my_team].players[0].tank.tankState.bodyAngle;
            //            event.packet >> teamMan.teams[!my_team].players[0].tank.tankState.turretAngle;
            //            event.packet >> teamMan.teams[!my_team].players[0].playerState.health;
            //            event.packet >> teamMan.teams[!my_team].players[0].tank.tankState.position.x;
            //            event.packet >> teamMan.teams[!my_team].players[0].tank.tankState.position.y;
            //            event.packet >> numProjectiles;
            //            teamMan.teams[!my_team].players[0].projectiles.clear();
            //            //Create projectile sprites for each projectile the other player reports.
            //            //Player 2 projectiles
            //            for (int y = 0;y < numProjectiles;y++){
            //                Projectile p;
            //                event.packet >> p.projectileState.position.x;
            //                event.packet >> p.projectileState.position.y;
            //                event.packet >> p.projectileState.velocity.x;
            //                event.packet >> p.projectileState.velocity.y;

            //                p.sprite.setTexture(*assetMan.projectileImages[0].tex);
            //                p.sprite.scale(0.5,0.5);
            //                p.sprite.setOrigin(8,8);
            //                p.sprite.setPosition(p.projectileState.position);
            //                teamMan.teams[!my_team].players[0].projectiles.push_back(p);
            //            }
            //            //Team 2 minions
            //            teamMan.teams[!my_team].minions.clear();
            //            event.packet >> numMinions;
            //            for (int y = 0;y < numMinions;y++){
            //                Minion m;
            //                event.packet >> m.minionState.position.x;
            //                event.packet >> m.minionState.position.y;
            //                //std::cout << m.minionState.position.x << ", " << m.minionState.position.y << std::endl;
            //                m.minionState.power = 1;//hack
            //                m.minionSprite.setPosition(m.minionState.position);
            //                m.minionSprite.setTexture(*assetMan.minionImages[!my_team].tex);
            //                teamMan.teams[!my_team].minions.push_back(m);
            //            }
            //        }else{
            //            //This is where you'd add input handling for additional game data types
            //        }
            //        //cout << "Rx'd, player2, " << packet.connectionId << ", " << player2.bodyAngle << ", " << player2.turretAngle << ", " << player2.velocity.x << ", " << player2.velocity.y << endl;
            //        break;
            //    }
            //}
            return 0;
        }
        sf::Uint32 onWindowEvent(sg::TankGame & game, sf::RenderWindow & w, sf::Event & event){
            //if (event.type == sf::Event::MouseMoved){
            //    if (!connected)
            //        return 0;
            //    float dx,dy;
            //    sf::Vector2f centerOfTurretWorld;
            //    sf::Vector2i mouseCursorScreen(event.mouseMove.x,event.mouseMove.y);
            //    sf::Vector2f mouseCursorWorld;

            //    //Find turrent angle based on vector from tank origin to mouse.
            //    centerOfTurretWorld = teamMan.teams[my_team].players[0].tank.turret.getPosition();
            //    mouseCursorWorld = window.convertCoords(mouseCursorScreen);
            //    dx = mouseCursorWorld.x - centerOfTurretWorld.x;
            //    dy = mouseCursorWorld.y - centerOfTurretWorld.y;
            //    teamMan.teams[my_team].players[0].tank.tankState.turretAngle =  (180.0f/3.14156f)*atan2(dy,dx);
            //}
            return 0;
        }
        sf::Uint32 doInit(sg::TankGame & game, int w, int h){
           
            return 0;
        }
        sf::Uint32 doCleanup(sg::TankGame & game){
            return 0;
        }
        sf::Uint32 doLocalInput(sg::TankGame & game){
            //if (!connected)
            //return false;
            ////We poll keyboard instead of relying on bios keyboard rate
            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            //    teamMan.teams[my_team].players[0].tank.tankState.throttle += 1;
            //    if (teamMan.teams[my_team].players[0].tank.tankState.throttle > 25)
            //        teamMan.teams[my_team].players[0].tank.tankState.throttle = 25;
            //}
    

            ////max speed lower in reverse
            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            //    teamMan.teams[my_team].players[0].tank.tankState.throttle -= 1;
            //    if (teamMan.teams[my_team].players[0].tank.tankState.throttle < -6)
            //        teamMan.teams[my_team].players[0].tank.tankState.throttle = -6;
            //}
    
            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            //    //Rotating left
            //    teamMan.teams[my_team].players[0].tank.tankState.bodyAngle = teamMan.teams[my_team].players[0].tank.tankState.bodyAngle -  5;
            //    if (teamMan.teams[my_team].players[0].tank.tankState.bodyAngle >= 360.0f || teamMan.teams[my_team].players[0].tank.tankState.bodyAngle <= -360.0f ){
            //        teamMan.teams[my_team].players[0].tank.tankState.bodyAngle = 0;
            //    }
            //}
    
            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            //    //Rotating right
            //    teamMan.teams[my_team].players[0].tank.tankState.bodyAngle = teamMan.teams[my_team].players[0].tank.tankState.bodyAngle +  5;
            //    if (teamMan.teams[my_team].players[0].tank.tankState.bodyAngle >= 360.0f || teamMan.teams[my_team].players[0].tank.tankState.bodyAngle <= -360.0f ){
            //        teamMan.teams[my_team].players[0].tank.tankState.bodyAngle = 0;
            //    }
            //}

            ////update player 1 velocity based on updated throttle and body angle.
            //teamMan.teams[my_team].players[0].tank.tankState.velocity.x =  teamMan.teams[my_team].players[0].tank.tankState.throttle * (float)cos(teamMan.teams[my_team].players[0].tank.tankState.bodyAngle / (180/3.14156));
            //teamMan.teams[my_team].players[0].tank.tankState.velocity.y =  teamMan.teams[my_team].players[0].tank.tankState.throttle * (float)sin(teamMan.teams[my_team].players[0].tank.tankState.bodyAngle / (180/3.14156));
    
            //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            //    //Create a new projectile
            //    Projectile p;
            //    p.projectileState.id = teamMan.teams[my_team].players[0].playerState.projectileCount;
            //    teamMan.teams[my_team].players[0].playerState.projectileCount++;


            //    p.sprite.setTexture(*assetMan.projectileImages[0].tex);
            //    p.sprite.scale(0.5,0.5);
            //    p.sprite.setOrigin(8,8);
            //    p.sprite.setPosition(teamMan.teams[!my_team].players[0].tank.tankState.position);
            //    teamMan.teams[!my_team].players[0].projectiles.push_back(p);


        
            //    //position projectile on the turret
            //    p.projectileState.position = teamMan.teams[my_team].players[0].tank.turret.getPosition();
            //    //set the projectile's velocity, based on the turret angle
            //    p.projectileState.velocity.x = teamMan.teams[my_team].players[0].tank.tankState.velocity.x + 25 * (float)cos(teamMan.teams[my_team].players[0].tank.tankState.turretAngle / (180/3.14156));
            //    p.projectileState.velocity.y = teamMan.teams[my_team].players[0].tank.tankState.velocity.y + 25 * (float)sin(teamMan.teams[my_team].players[0].tank.tankState.turretAngle / (180/3.14156));
            //    //translate projectile to appear to come from turret tip
            //    p.projectileState.position.x += p.projectileState.velocity.x;
            //    p.projectileState.position.y += p.projectileState.velocity.y;

            //    p.sprite.setPosition(p.projectileState.position);

            //    //Add projectile to in-flight list
            //    teamMan.teams[my_team].players[0].projectiles.push_back(p);
            //    cout << "Bang!" << endl;
            //}
            return 0;
        }
        sf::Uint32 doLoop(sg::TankGame & game){
            //if (!game.connected)
            //    return;
            //if (game.minionClock.getElapsedTime().asMilliseconds() > 700){
            //    Minion m;
            //    m.minionSprite.setTexture(*game.assetMan.minionImages[game.my_team].tex);
            //    m.minionState.position = game.teamMan.teams[game.my_team].generator1State.position;
            //    m.minionSprite.setPosition(m.minionState.position);
            //    //std::cout <<my_team << ",   " << m.minionState.position.x << ", " << m.minionState.position.y << std::endl;
            //    int g = rand()%4;
            //    if (!my_team){
            //        switch(g){
            //        case 0:
            //            m.minionState.velocity.x = 3;
            //            m.minionState.velocity.y = 4;
            //            break;
            //        case 1:
            //            m.minionState.velocity.x = 2;
            //            m.minionState.velocity.y = 5;
            //            break;
            //        case 2:
            //            m.minionState.velocity.x = 5;
            //            m.minionState.velocity.y = 2;
            //            break;
            //        case 3:
            //            m.minionState.velocity.x = 4;
            //            m.minionState.velocity.y = 3;
            //            break;
            //        }
            //
            //    }else{
            //        switch(g){
            //        case 0:
            //            m.minionState.velocity.x = -3;
            //            m.minionState.velocity.y = -4;
            //            break;
            //        case 1:
            //            m.minionState.velocity.x = -2;
            //            m.minionState.velocity.y = -5;
            //            break;
            //        case 2:
            //            m.minionState.velocity.x = -5;
            //            m.minionState.velocity.y = -2;
            //            break;
            //        case 3:
            //            m.minionState.velocity.x = -4;
            //            m.minionState.velocity.y = -3;
            //            break;
            //        }
            //    }
            //    game.teamMan.teams[my_team].minions.push_back(m);
        
            //    //teamMan.team1.minions.push_back(m);

            //    game.minionClock.restart();
            //}
    
    

            ////Calculate our tank's orientation for this frame.
            //game.teamMan.teams[game.my_team].players[0].tank.body.setRotation(0.0f);
            //game.teamMan.teams[game.my_team].players[0].tank.body.rotate(game.teamMan.teams[game.my_team].players[0].tank.tankState.bodyAngle-90);

            //game.teamMan.teams[game.my_team].players[0].tank.turret.setRotation(0.0f);
            //game.teamMan.teams[game.my_team].players[0].tank.turret.rotate(teamMan.teams[my_team].players[0].tank.tankState.turretAngle-90);

            ////calculate our tanks velocity based on throttle and orientation
            //game.teamMan.teams[game.my_team].players[0].tank.body.move   (game.teamMan.teams[game.my_team].players[0].tank.tankState.velocity.x*20*game.frameTime.asSeconds(),
            //                                             game.teamMan.teams[game.my_team].players[0].tank.tankState.velocity.y*20*game.frameTime.asSeconds());
    
            //game.teamMan.teams[game.my_team].players[0].tank.turret.move (game.teamMan.teams[game.my_team].players[0].tank.tankState.velocity.x*20*game.frameTime.asSeconds(),
            //                                             game.teamMan.teams[game.my_team].players[0].tank.tankState.velocity.y*20*game.frameTime.asSeconds());

            //game.teamMan.teams[game.my_team].players[0].tank.tankState.position = game.teamMan.teams[game.my_team].players[0].tank.body.getPosition();

            ////Calculate other players tank orientation
            //game.teamMan.teams[!game.my_team].players[0].tank.body.setRotation(0.0f);
            //game.teamMan.teams[!game.my_team].players[0].tank.body.rotate(game.teamMan.teams[!game.my_team].players[0].tank.tankState.bodyAngle-90);

            //game.teamMan.teams[!game.my_team].players[0].tank.turret.setRotation(0.0f);
            //game.teamMan.teams[!game.my_team].players[0].tank.turret.rotate(game.teamMan.teams[!game.my_team].players[0].tank.tankState.turretAngle-90);

            ////position other players tank
            //game.teamMan.teams[!game.my_team].players[0].tank.body.setPosition(game.teamMan.teams[!game.my_team].players[0].tank.tankState.position);
            //game.teamMan.teams[!game.my_team].players[0].tank.turret.setPosition(game.teamMan.teams[!game.my_team].players[0].tank.tankState.position);

            ////Projectiles - position and orient player 1 projectiles
            //std::vector<Projectile>::iterator proj = game.teamMan.teams[game.my_team].players[0].projectiles.begin();
            //while (proj != game.teamMan.teams[game.my_team].players[0].projectiles.end()){
            //    proj->sprite.move(proj->projectileState.velocity.x*20*game.frameTime.asSeconds(),proj->projectileState.velocity.y*20*game.frameTime.asSeconds());
            //    proj->projectileState.position = proj->sprite.getPosition();

            //    //remove projectiles whose position is beyond these extremes
            //    //this will automatically propagate to player 2, so, player2 doesn't need this treatment locally.
            //    if (proj->projectileState.position.x > 4000 || proj->projectileState.position.y > 4000  ||
            //        proj->projectileState.position.x < -300 || proj->projectileState.position.y < -300  ){
            //        proj = game.teamMan.teams[game.my_team].players[0].projectiles.erase(proj);
            //        //cout << "Smlap" << endl;
            //    }else if (proj->sprite.getGlobalBounds().intersects(teamMan.teams[!my_team].players[0].tank.body.getGlobalBounds())){
            //        //remove projectiles that hit other player
            //        proj = teamMan.teams[my_team].players[0].projectiles.erase(proj);
            //        //cout << "Smash" << endl;
            //    }else
            //        proj++;
            //}

            ////Projectiles - position and orient player 2 projectiles.
            //proj = teamMan.teams[!my_team].players[0].projectiles.begin();
            //while (proj != teamMan.teams[!my_team].players[0].projectiles.end()){
            //    //Check if player 2 projectiles are hitting player1
            //    if (proj->sprite.getGlobalBounds().intersects(teamMan.teams[my_team].players[0].tank.body.getGlobalBounds())){
            //        teamMan.teams[my_team].players[0].playerState.health--;
            //        cout << "Ouch" << endl;
            //        //restate the dash Health 
            //        dash.setHealth(teamMan.teams[my_team].players[0].playerState.health);
            //        proj = teamMan.teams[!my_team].players[0].projectiles.erase(proj);
            //    }else{
            //        proj->sprite.move(proj->projectileState.velocity.x*20*frameTime.asSeconds(),proj->projectileState.velocity.y*20*frameTime.asSeconds());
            //        proj->projectileState.position = proj->sprite.getPosition();
            //        proj++;
            //    }
            //}
    
            ////Local minions
            //std::list<Minion>::iterator minion = teamMan.teams[my_team].minions.begin();
            //for (;minion != teamMan.teams[my_team].minions.end();){
            //    minion->minionSprite.move(minion->minionState.velocity.x*20*frameTime.asSeconds(),
            //                              minion->minionState.velocity.y*20*frameTime.asSeconds());
            //    minion->minionState.position = minion->minionSprite.getPosition();
            //    if (minion->minionState.position.x > 4000 || minion->minionState.position.y > 4000  ||
            //        minion->minionState.position.x < -300 || minion->minionState.position.y < -300  ){
            //        minion = teamMan.teams[my_team].minions.erase(minion);
            //        //cout << "Smlap" << endl;
            //    }else if (minion->minionSprite.getGlobalBounds().intersects(teamMan.teams[!my_team].players[0].tank.body.getGlobalBounds())){
            //        //remove projectiles that hit other player
            //        minion = teamMan.teams[my_team].minions.erase(minion);
            //        //cout << "Smash" << endl;
            //    }else{
            //        minion++;
            //    }
            //}
            ////Other player minions
            //minion = teamMan.teams[!my_team].minions.begin();
            //for (;minion != teamMan.teams[!my_team].minions.end();){
            //    //minion->minionSprite.setPosition(minion->minionState.position);
            //    minion->minionState.position = minion->minionSprite.getPosition();
            //    //if (minion->minionState.position.x > 4000 || minion->minionState.position.y > 4000  ||
            //    //    minion->minionState.position.x < -4000 || minion->minionState.position.y < -4000  ){
            //    //    minion = teamMan.team1.minions.erase(minion);
            //    //    //cout << "Smlap" << endl;
            //    //}else
            //    if (minion->minionSprite.getGlobalBounds().intersects( teamMan.teams[my_team].players[0].tank.body.getGlobalBounds())){
            //    //    
            //        teamMan.teams[my_team].players[0].playerState.health--;
            //        cout << "Owy" << endl;
            //        //restate the dash Health 
            //        dash.setHealth(teamMan.teams[my_team].players[0].playerState.health);
            //
            //        //remove projectiles that hit other player
            //        minion = teamMan.teams[!my_team].minions.erase(minion);
            //        cout << "Smash" << endl;
            //    }else
            //        minion++;
            //}
    

            ////Update the Dashboard
            //dash.setHealth(teamMan.teams[my_team].players[0].playerState.health);
            //dash.setAngles(teamMan.teams[my_team].players[0].tank.tankState.bodyAngle,teamMan.teams[my_team].players[0].tank.tankState.turretAngle);
            //dash.setPos(teamMan.teams[my_team].players[0].tank.tankState.position);
            //dash.setVelocity(teamMan.teams[my_team].players[0].tank.tankState.velocity);
            //dash.setHealth2(teamMan.teams[!my_team].players[0].playerState.health);
            return 0;
        }
        sf::Uint32 doDraw(sf::RenderWindow &window){
            //if (!connected)
            //     return;
            ////Center arenaView on current position of player 1
            //arenaView.setCenter(teamMan.teams[my_team].players[0].tank.body.getPosition());
            //window.setView(arenaView);

            ////Draw Floor
            //arenaMan.draw(window);

        
            ////Draw Tanks
            //window.draw(teamMan.teams[my_team].players[0].tank.body);
            //window.draw(teamMan.teams[!my_team].players[0].tank.body);
            //window.draw(teamMan.teams[my_team].players[0].tank.turret);
            //window.draw(teamMan.teams[!my_team].players[0].tank.turret);

            ////Draw Player 1 projectiles
            //std::vector<Projectile>::iterator proj = teamMan.teams[my_team].players[0].projectiles.begin();
            //for(;proj != teamMan.teams[my_team].players[0].projectiles.end();proj++){
            //    window.draw(proj->sprite);
            //}

            ////Draw player 2 projectiles
            //proj = teamMan.teams[!my_team].players[0].projectiles.begin();
            //for(;proj != teamMan.teams[!my_team].players[0].projectiles.end();proj++){
            //    window.draw(proj->sprite);
            //}

            //std::list<Minion>::iterator minion = teamMan.teams[my_team].minions.begin();
            //for (;minion != teamMan.teams[my_team].minions.end();minion++){
            //    window.draw(minion->minionSprite);//.setPosition(minion->minionState.position);
            //}

            //minion = teamMan.teams[!my_team].minions.begin();
            //for (;minion != teamMan.teams[!my_team].minions.end();minion++){
            //    //cout << minion->minionSprite.getPosition().x << ", " << minion->minionSprite.getPosition().y <<  std::endl;
            //    //cout << minion->minionState.position.x << ", " << minion->minionState.position.y <<  std::endl;
            //    window.draw(minion->minionSprite);//.setPosition(minion->minionState.position);
            //}
    
            ////Set View for drawing the HUD.
            ////we use a different view because we don't want the dashboard to scale when zooming in and out.    
        
            ////Draw all the HUD stuff
            //window.setView(dashView);    
            //window.draw(dash.dashSprite);
            //window.draw(dash.health);
            //window.draw(dash.velocity);
            //window.draw(dash.position);
            //window.draw(dash.angles);
            //window.draw(dash.health2);

            ////Reset view to the state before we drew the dashboard
            //window.setView(arenaView);
            return 0;
        }

    private:

    private:
    };
};

#endif

