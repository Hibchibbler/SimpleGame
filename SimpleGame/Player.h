/**********************************************************************************
Tank Game
Player.h
Daniel Ferguson, Eddie Stranberg
Copyright 2012
**********************************************************************************/

#ifndef Player_h_
#define Player_h_

#include <SFML/Graphics.hpp>

namespace sg
{
    class Frame
    {
    public:
        sf::Image image;
        sf::Texture tex;
    };

    class Projectile
    {
    public:
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Sprite sprite;
    };

    class Player
    {
    public:
        Player(){
            velocity.x = 0;
            velocity.y = 0;
            bodyAngle = 0.0f;
            throttle = 0.0f;
            bodyAngle = 0.0f;
            turretAngle = 0.0f;
            health = 100.0f;
            mass = 5.0f;
            frictionCoefficient = 0.5f;
            turnVelocity = 0.0f;
        }
        std::string name;

        std::vector<Frame> bodyFrames;
        Frame turretFrame;
        Frame projectileFrame;

        sf::Sprite bodySprite;
        sf::Sprite turretSprite;
        std::vector<Projectile> projectiles;

        sf::Vector2f position;
        sf::Vector2f velocity;

        float throttle;
        float bodyAngle;
        float turretAngle;
        float turnVelocity;
        float mass;
        float frictionCoefficient;
        float health;
    };
};

#endif

