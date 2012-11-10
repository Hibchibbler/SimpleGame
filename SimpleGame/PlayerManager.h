#ifndef PlayerManager_h_
#define PlayerManager_h_

#include "Player.h"
#include "Images.h"
#include <list>

#include "LogFile.h"
#include "AssetManager.h"

namespace sg
{

    class PlayerManager
    {
    public:
        PlayerManager(){}
        ~PlayerManager(){}

        int Load(){

            ////Load Tanks
            //TankImage ti;
            //ti.load("BlueBody_red.png", "BlueTurret.png");
            //tankImages.push_back(ti);
            //LogFile::get()->log(0,0,"Loaded blue tank");

            //ti.load("RedBody_red.png", "RedTurret.png");
            //tankImages.push_back(ti);
            //LogFile::get()->log(0,0,"Loaded red tank");
            //

            //ProjectileImage pi;
            //pi.load("projectile.png");
            //projectileImages.push_back(pi);
            //LogFile::get()->log(0,0,"Loaded projectile");

            return 0;
        }
        
        

        int removePlayer(){

        }

        int unload(){
            //unload tankImages

            //unload projectiles
        }

        

    };
};

#endif

