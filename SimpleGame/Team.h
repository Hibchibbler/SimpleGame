/**********************************************************************************
Tank Game
Team.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Team_h_
#define Team_h_

#include "AssetManager.h"
#include "Minion.h"
#include "Player.h"
#include "LogFile.h"
#include <list>
#include <vector>

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
        int addPlayer(AssetManager & am, sf::Uint32 uid, sf::Uint32 playerId, sf::Vector2f initialPosition){
            players.push_back(Player());
            players.back().tank.body.setTexture(*am.tankImages[uid].bodyTexture);//(*tankImages[uid].bodyTexture);
            players.back().tank.body.setOrigin(40,61);
            players.back().tank.body.scale(0.6f, 0.6f);
            
            players.back().tank.turret.setTexture(*am.tankImages[uid].turretTexture);
            players.back().tank.turret.setOrigin(27,90);
            players.back().tank.turret.scale(0.6f, 0.6f);

            players.back().tank.setPosition(initialPosition);
            //
            LogFile::get()->log(0,0,"PlayerManager::addPlayer");
            return 0;
        }
        std::vector<Player> players;
        std::list<Minion> minions;
        TeamState teamState;
        GarageState garageState;
        GeneratorState generator1State;
    };

};

#endif