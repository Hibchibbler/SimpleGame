/**********************************************************************************
Tank Game
Floor.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Floor_h_
#define Floor_h_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

namespace sg
{
    class Floor
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

            //And associate a texture with them.
            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[0]);//*imageTiles.back());

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[1]);

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles[2]);

            //Read map file just for width and height.
            std::ifstream fin("export.txt",std::ios::in|std::ios::binary  );
            if (fin.is_open()){
                fin.read((char*)&width, 4);
                fin.read((char*)&height, 4);

                //Populate sprite vector with default sprites which represents the entire map.
                for (int h = 0;h < height;h++){
                    for (int w = 0; w < width;w++){
                        mapSprites.push_back(sf::Sprite(*texTiles.back()));
                        float spriteWidth = mapSprites.back().getGlobalBounds().width;
                        float spriteHeight = mapSprites.back().getGlobalBounds().height;
                        mapSprites.back().setPosition((float)(w*spriteWidth-spriteWidth/2),(float)(h*spriteHeight-spriteHeight/2));
                    }
                }

                //Now read map file, and tailor the sprite vector to have the corret tile.
                int index = 0;

                while (!fin.eof()){
                    int i;
                    fin.read((char*)&i, 4);
                    if (index == mapSprites.size())
                        break;
                    mapSprites[index].setTexture(*texTiles[i]);
                    index++;
                    std::cout << index << std::endl;
                }
            }
        
           
            return true;
        }

        

        std::vector<sf::Image*> imageTiles;
        std::vector<sf::Texture*> texTiles;
        sf::Sprite spriteTiles[7][7];
        std::vector<sf::Sprite> mapSprites;
        int width,height;
    };
}

#endif

