#ifndef PlayerManager_h_
#define PlayerManager_h_

#include "Player.h"
#include "Sprites.h"
#include <list>

#include "LogFile.h"

namespace sg
{

    class PlayerManager
    {
    public:
        PlayerManager(){}
        ~PlayerManager(){}

        int Load(){

            //Load Tanks
            TankImage ti;
            ti.load("BlueBody_red.png", "BlueTurret.png");
            tankImages.push_back(ti);
            LogFile::get()->log(0,0,"Loaded blue tank");

            ti.load("RedBody_red.png", "RedTurret.png");
            tankImages.push_back(ti);
            LogFile::get()->log(0,0,"Loaded red tank");
            

            ProjectileImage pi;
            pi.load("projectile.png");
            projectileImages.push_back(pi);
            LogFile::get()->log(0,0,"Loaded projectile");

            return 0;
        }
        
        int addPlayer(sf::Uint32 uid, sf::Vector2f initialPosition){
            players.push_back(Player());
            players.back().tank.body.setTexture(*tankImages[uid].bodyTexture);
            players.back().tank.body.setOrigin(40,61);
            players.back().tank.body.scale(0.6f, 0.6f);
            
            players.back().tank.turret.setTexture(*tankImages[uid].turretTexture);
            players.back().tank.turret.setOrigin(27,90);
            players.back().tank.turret.scale(0.6f, 0.6f);

            players.back().tank.setPosition(initialPosition);
            
            LogFile::get()->log(0,0,"PlayerManager::addPlayer");
            return 0;
        }

        int removePlayer(){

        }

        int unload(){
            //unload tankImages

            //unload projectiles
        }

        std::vector<Player> players;
        std::vector<TankImage> tankImages;
        std::vector<ProjectileImage> projectileImages;

    };
};

#endif

