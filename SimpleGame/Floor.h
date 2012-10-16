#ifndef Floor_h_
#define Floor_h_

namespace sg
{
    class Floor
    {
    public:
        void Load(){
            width = 4;
            height = 3;

            imageTiles.push_back(new sf::Image());
            imageTiles.back()->loadFromFile("floor1.png");

            texTiles.push_back(new sf::Texture());
            texTiles.back()->loadFromImage(*imageTiles.back());

        
        
            for (int h = 0;h < height;h++){
                for (int w = 0; w < width;w++){
                    spriteTiles[h][w].setTexture(*texTiles.back());
                    //spriteTiles[h][w].scale(0.75f,0.75f);//32
                    spriteTiles[h][w].setPosition(w*128-200,h*128-150);//TODO: i do not know why 200 and 150 need to be there for the floor to line up on the top and left edge of view
                }
            }
        }

        std::vector<sf::Image*> imageTiles;
        std::vector<sf::Texture*> texTiles;
        sf::Sprite spriteTiles[7][7];
        int width,height;
    };

}

#endif

