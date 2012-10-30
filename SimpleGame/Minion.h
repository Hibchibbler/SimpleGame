/**********************************************************************************
Tank Game
Minion.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Minion_h_
#define Minion_h_

#include <SFML/Graphics.hpp>

namespace sg
{
    class MinionState
    {
    public:
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Uint32 power;
    };

    class Minion
    {
    public:
        sf::Sprite minionSprite;
        MinionState minionState;
    };

};


#endif

