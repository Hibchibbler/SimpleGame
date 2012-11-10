/**********************************************************************************
Tank Game
TeamManager.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef TeamManager_h_
#define TeamManager_h_

#include "Team.h"
#include "Images.h"
#include "ArenaManager.h"
#include <vector>

namespace sg
{
    class TeamManager
    {
    public:
        int load(ArenaManager &arenaMan, int my_team){
            teams.push_back(Team());
            teams.push_back(Team());
            teams[my_team].garageState.position = arenaMan.getGarage(my_team);
            teams[my_team].generator1State.position = arenaMan.getGenerator(my_team,0);
            teams[!my_team].garageState.position = arenaMan.getGarage(!my_team);
            teams[!my_team].generator1State.position = arenaMan.getGenerator(!my_team,0);

            srand( time(NULL) );
            return 0;
        }

        int draw(sf::RenderWindow & window, sf::Vector2f pos){ }
        std::vector<Team> teams;
    };
};

#endif

