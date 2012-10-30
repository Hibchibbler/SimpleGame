/**********************************************************************************
Tank Game
Projectile.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Projectile_h_
#define Projectile_h_

#include <SFML/Graphics.hpp>

namespace sg
{
    class ProjectileState
    {
    public:
        ProjectileState(){
        }
        sf::Uint32 id;
        sf::Vector2f position;
        sf::Vector2f velocity;
    };

    class Projectile
    {
    public:
        sf::Sprite sprite;
        ProjectileState projectileState;
    };
};

#endif
