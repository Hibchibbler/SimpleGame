/**********************************************************************************
Tank Game
Images.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Images_h_
#define Images_h_

#include <SFML/Graphics.hpp>

namespace sg
{
    class TankImage
    {
    public:
        int load(std::string bodyFn, std::string turretFn){
            bodyImage = new sf::Image();
            bodyImage->loadFromFile(bodyFn);//"BlueBody_green.png");
            bodyImage->createMaskFromColor(sf::Color::Cyan,0);
            bodyTexture = new sf::Texture();
            bodyTexture->loadFromImage(*bodyImage);
            turretImage = new sf::Image();
            turretImage->loadFromFile(turretFn);//"BlueTurret.png");
            turretImage->createMaskFromColor(sf::Color::Cyan,0);
            turretTexture = new sf::Texture();
            turretTexture->loadFromImage(*turretImage);
            return 0;
        }

        int unload(){
            delete bodyTexture;
            delete bodyImage;

            delete turretTexture;
            delete turretImage;
            return 0;
        }
        sf::Image* bodyImage;
        sf::Texture* bodyTexture;

        sf::Image* turretImage;
        sf::Texture* turretTexture;
    };

    class FloorImage
    {
    public:
        int load(std::string fn){
            img = new sf::Image();
            img->loadFromFile(fn);
            img->createMaskFromColor(sf::Color::Cyan,0);
            tex = new sf::Texture();
            tex->loadFromImage(*img);
            return 0;
        }
        sf::Image* img;
        sf::Texture* tex;
    };

    class ProjectileImage
    {
    public:
        int load(std::string fn){
            img = new sf::Image();
            img->loadFromFile(fn);
            img->createMaskFromColor(sf::Color::Cyan,0);
            tex = new sf::Texture();
            tex->loadFromImage(*img);
            return 0;
        }
        int unload(){
            delete tex;
            delete img;
        }
        sf::Image* img;
        sf::Texture* tex;
    };

    class MinionImage
    {
    public:
        int load(std::string fn){
            img = new sf::Image();
            img->loadFromFile(fn);
            img->createMaskFromColor(sf::Color::Cyan,0);
            tex = new sf::Texture();
            tex->loadFromImage(*img);
            return 0;
        }
        sf::Image* img;
        sf::Texture* tex;
    };

    class MinionSprite
    {
    public:
        sf::Sprite sprite;
    };

    class TankSprite
    {
    public:
        sf::Sprite sprite;
    };

    class ProjectileSprite
    {
    public:
        sf::Sprite sprite;
    };

    class FloorSprite
    {
    public:
        FloorSprite(){
            id = 0;
        }
        sf::Uint32 id;
        sf::Sprite sprite;
    };

    class ImageAsset
    {
    public:
        void load(std::string fn){
            i.loadFromFile(fn);
            i.createMaskFromColor(sf::Color::Cyan,0);
            t.loadFromImage(i);
        }

        sf::Texture & getTexture(){
            return t;
        }
        sf::Image & getImage(){return i;}
    private:
        sf::Image i;
        sf::Texture t;

    };
};

#endif