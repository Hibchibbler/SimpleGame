/**********************************************************************************
Tank Game
Player.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Player_h_
#define Player_h_

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Tank.h"
namespace sg
{
    

    class PlayerState
    {
    public:
        PlayerState(){
            health = 100.0f;
            projectileCount = 0;
            teamUid = -1;
        }
        sf::Uint32 playerId;
        std::string playerName;
        sf::Uint32 projectileCount;
        float health;
        sf::Uint32 teamUid;
    private:
    };

    class Player
    {
    public:
        Player(){
        }
        Tank tank;
        std::vector<Projectile> projectiles;
        PlayerState playerState;
        
        
    };
};

#endif

