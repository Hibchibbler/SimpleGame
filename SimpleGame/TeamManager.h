/**********************************************************************************
Tank Game
TeamManager.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef TeamManager_h_
#define TeamManager_h_

#include "Team.h"
#include "Sprites.h"
#include "ArenaManager.h"

namespace sg
{
    class TeamManager
    {
    public:
        int load(ArenaManager &arenaMan, bool isServer){

            MinionImage mi;
            mi.img = new sf::Image();
            mi.img->loadFromFile("minion1.png");
            mi.img->createMaskFromColor(sf::Color::Cyan,0);
            mi.tex = new sf::Texture();
            mi.tex->loadFromImage(*mi.img);

            minionImages1.push_back(mi);
            minionImages2.push_back(mi);//both teams use same image..hack

            
                team1.garageState.health = 100;
                //set by caller: team1.garageState.position
                team1.generator1State.health = 100;
                //set by caller
                //team1.generator1State.position = arenaMan.getGenerator(0,0);
                std::cout << team1.generator1State.position.x << ", " << team1.generator1State.position.y << std::endl;
                team1.teamState.uid = 0;

                team2.garageState.health = 100;
                //set by caller
                //team2.garageState.position = arenaMan.getGarage(1);
                team2.generator1State.health = 100;
                //set by caller
                //team2.generator1State.position = arenaMan.getGenerator(1,0);
                std::cout << team2.generator1State.position.x << ", " << team2.generator1State.position.y << std::endl;
                team2.teamState.uid = 1;
            
            srand( time(NULL) );
            return 0;
        }

        int draw(sf::RenderWindow & window, sf::Vector2f pos){
            //Minion m;
            //m.minionSprite.setTexture(*minionImages1[0].tex);
            //m.minionState.position = pos;
            ////m.minionState.velocity = 
            //m.minionState.power = 1;
            //team1.minions.push_back(m);
            //std::vector<MinionImage>::iterator i;
            ////i = minionImages1[0].
        }
        
        //int addTeam(sf::Uint32 uid, sf::Vector2f garagePosition){

        //    Team team;
        //    team.teamState.uid = uid;
        //    team.garageState.health = 100;
        //    team.garageState.position = garagePosition;
        //    teams.push_back(team);
        //    return 0;
        //}

        std::vector<MinionImage> minionImages1;
        std::vector<MinionImage> minionImages2;
        Team team1;
        Team team2;
        
    };
};

#endif

