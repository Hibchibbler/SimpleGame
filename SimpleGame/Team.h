/**********************************************************************************
Tank Game
Team.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Team_h_
#define Team_h_

#include "Minion.h"
#include <list>

namespace sg
{
    class GeneratorState
    {
    public:
        sf::Vector2f position;
        sf::Uint32 health;
    };
    class GarageState
    {
    public:
        sf::Vector2f position;
        sf::Uint32 health;
    };

    class TeamState
    {
    public:
        
        sf::Uint32 health;
        sf::Uint32 uid;
    };

    class Team
    {
    public:
        std::list<Minion> minions;
        TeamState teamState;
        GarageState garageState;
        GeneratorState generator1State;
    };

};

#endif