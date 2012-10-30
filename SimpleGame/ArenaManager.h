/**********************************************************************************
Tank Game
ArenaManager.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef ArenaManager_h_
#define ArenaManager_h_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Sprites.h"

namespace sg
{
    class ArenaManager
    {
    public:
        //TODO: finish error handling
        //Load assets
        int Load(int screenWidth, int screenHeight){
            bool ret = false;
            sf::Image* img = NULL;
            //Load floor tiles
            
            if ((img = new sf::Image()) == NULL){
                //Memory allocation failure
                return false;
            }
            floorImages.push_back(img);
            ret = floorImages.back()->loadFromFile("floor1.png");
            if (ret == false){
                //Image load failure
                return false;
            }
            floorTextures.push_back(new sf::Texture());
            floorTextures.back()->loadFromImage(*floorImages.back());// 0

            floorImages.push_back(new sf::Image());
            floorImages.back()->loadFromFile("floor2.png");
            floorTextures.push_back(new sf::Texture());
            floorTextures.back()->loadFromImage(*floorImages.back());// 1
            
            floorImages.push_back(new sf::Image());
            floorImages.back()->loadFromFile("floor3.png");
            floorTextures.push_back(new sf::Texture());
            floorTextures.back()->loadFromImage(*floorImages.back());// 2

            floorImages.push_back(new sf::Image());
            floorImages.back()->loadFromFile("team1Garage.png");
            floorTextures.push_back(new sf::Texture());
            floorTextures.back()->loadFromImage(*floorImages.back());// 3

            floorImages.push_back(new sf::Image());
            floorImages.back()->loadFromFile("team2Garage.png");
            floorTextures.push_back(new sf::Texture());
            floorTextures.back()->loadFromImage(*floorImages.back());// 4

            floorImages.push_back(new sf::Image());
            floorImages.back()->loadFromFile("team1Generator.png");
            floorTextures.push_back(new sf::Texture());
            floorTextures.back()->loadFromImage(*floorImages.back());// 5

            floorImages.push_back(new sf::Image());
            floorImages.back()->loadFromFile("team2Generator.png");
            floorTextures.push_back(new sf::Texture());
            floorTextures.back()->loadFromImage(*floorImages.back());// 6


            //Read map file just for width and height.
            //Every 4 bytes represents a distinct datum. 
            //First datum is width
            //Second datum is height
            //Remaining data is tile type. There are width*height 4 byte tile type id following width and height
            // each tile type can be:
            //  0 - Wall
            //  1 - Floor 1
            //  2 - Floor 2
            //  3 - Team 1 Garage
            //  4 - Team 2 Garage
            //  5 - Team 1 Minion Generator
            //  6 - Team 2 Minion Generator

            std::ifstream fin("map_garage_mgenerator.txt",std::ios::in|std::ios::binary  );
            if (fin.is_open()){
                fin.read((char*)&width, 4);
                fin.read((char*)&height, 4);
                //Populate sprite vector with default sprites which represents the entire map.
                //we set any ol texture here, just so we can get it's size.
                //TODO: if all tiles are same size, we can optimize and only do spriteWidth\Height once.
                for (int h = 0;h < height;h++){
                    for (int w = 0; w < width;w++){
                        FloorSprite ft;
                        ft.sprite.setTexture(*floorTextures.back());
                        floorSprites.push_back(ft);
                        float spriteWidth = floorSprites.back().sprite.getGlobalBounds().width;
                        float spriteHeight = floorSprites.back().sprite.getGlobalBounds().height;
                        floorSprites.back().sprite.setPosition((float)(w*spriteWidth-spriteWidth/2),(float)(h*spriteHeight-spriteHeight/2));
                    }
                }

                //Now read map file, and tailor the sprite vector to have the corret tile.
                int index = 0;

                while (!fin.eof()){
                    int i;
                    fin.read((char*)&i, 4);
                    if (index == floorSprites.size())
                        break;
                    floorSprites[index].id = i;
                    floorSprites[index].sprite.setTexture(*floorTextures[i]);
                    index++;
                    std::cout << index << std::endl;
                }
            }
        
           
            return true;
        }

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

