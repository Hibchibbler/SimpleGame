/**********************************************************************************
Tank Game
ArenaManager.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef ArenaManager_h_
#define ArenaManager_h_

#include <SFML/Graphics.hpp>



#include "Images.h"

namespace sg
{
    class AssetManager;
    class ArenaManager
    {
    public:
        //TODO: finish error handling
        //Load assets
        
        int Load(AssetManager & am, int screenWidth, int screenHeight);
        int draw(sf::RenderWindow & window){
            std::vector<FloorSprite>::iterator tile = floorSprites.begin();
            for (; tile != floorSprites.end(); tile++){
                window.draw(tile->sprite);
            }
            return 0;
        }
        

        sf::Vector2f getGarage(sf::Uint32 teamUid){
            std::vector<FloorSprite>::iterator iter = floorSprites.begin();
            for(;iter != floorSprites.end();iter++){
                if (teamUid == 0){
                    if (iter->id == 3){
                        return iter->sprite.getPosition();
                    }
                }else if (teamUid == 1){
                    if (iter->id == 4){
                        return iter->sprite.getPosition();
                    }
                }

            }
            return sf::Vector2f(0,0);
        }

        sf::Vector2f getGenerator(sf::Uint32 teamUid, sf::Uint32 generatorUid){
            std::vector<FloorSprite>::iterator iter = floorSprites.begin();
            for(;iter != floorSprites.end();iter++){
                if (teamUid == 0){
                    if (iter->id == 5){
                        return iter->sprite.getPosition();
                    }
                }else if (teamUid == 1){
                    if (iter->id == 6){
                        return iter->sprite.getPosition();
                    }
                }

            }
            return sf::Vector2f(0,0);
        }


        //Each floor tile png, gets 1 image, and 1 texture in memory.
        //The mapTiles sprite vector will have many sprite referencing the same texture.
        std::vector<sf::Image*> floorImages;
        std::vector<sf::Texture*> floorTextures;
        //std::vector<FloorImage> floorImages;
        std::vector<FloorSprite> floorSprites;
        int width,height;
        
        sf::Uint32 pixW, pixH;
    };
}

#endif

