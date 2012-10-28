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

namespace sg
{
    class FloorTile
    {
    public:
        FloorTile(){
            id = 0;
        }
        sf::Uint32 id;
        sf::Sprite sprite;
    };

    class ArenaManager
    {
    public:
        bool Load(int screenWidth, int screenHeight){
            bool ret = false;
            sf::Image* img = NULL;
            //Load floor tiles

            img = new sf::Image();
            if (img == NULL){
                //Memory allocation failure
                return false;
            }
            imageTiles.push_back(img);
            ret = imageTiles.back()->loadFromFile("floor1.png");
            if (ret == false){
                //Image load failure
                return false;
            }

            imageTiles.push_back(new sf::Image());
            imageTiles.back()->loadFromFile("floor2.png");

            imageTiles.push_back(new sf::Image());
            imageTiles.back()->loadFromFile("floor3.png");

            imageTiles.push_back(new sf::Image());
            imageTiles.back()->loadFromFile("team1Garage.png");

            imageTiles.push_back(new sf::Image());
            imageTiles.back()->loadFromFile("team2Garage.png");

            imageTiles.push_back(new sf::Image());
            imageTiles.back()->loadFromFile("team1Generator.png");

            imageTiles.push_back(new sf::Image());
            imageTiles.back()->loadFromFile("team2Generator.png");

            //And associate a texture with them.
            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[0]);

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[1]);

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[2]);

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[3]);

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[4]);

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[5]);

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[6]);

            //Read map file just for width and height.
            std::ifstream fin("map_garage_mgenerator.txt",std::ios::in|std::ios::binary  );
            if (fin.is_open()){
                fin.read((char*)&width, 4);
                fin.read((char*)&height, 4);

                //Populate sprite vector with default sprites which represents the entire map.
                for (int h = 0;h < height;h++){
                    for (int w = 0; w < width;w++){
                        FloorTile ft;
                        ft.sprite.setTexture(*texTiles.back());
                        mapTiles.push_back(ft);
                        float spriteWidth = mapTiles.back().sprite.getGlobalBounds().width;
                        float spriteHeight = mapTiles.back().sprite.getGlobalBounds().height;
                        mapTiles.back().sprite.setPosition((float)(w*spriteWidth-spriteWidth/2),(float)(h*spriteHeight-spriteHeight/2));
                    }
                }

                //Now read map file, and tailor the sprite vector to have the corret tile.
                int index = 0;

                while (!fin.eof()){
                    int i;
                    fin.read((char*)&i, 4);
                    if (index == mapTiles.size())
                        break;
                    mapTiles[index].id = i;
                    mapTiles[index].sprite.setTexture(*texTiles[i]);
                    index++;
                    std::cout << index << std::endl;
                }
            }
        
           
            return true;
        }

        

        std::vector<sf::Image*> imageTiles;
        std::vector<sf::Texture*> texTiles;
        std::vector<FloorTile> mapTiles;
        int width,height;
    };
}

#endif

