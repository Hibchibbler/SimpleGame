#ifndef Tank_h_
#define Tank_h_

#include <SFML/System.hpp>

namespace sg
{


    class TankState
    {
    public:
        TankState(){
            position = sf::Vector2f(200,200);
            velocity = sf::Vector2f(0,0);
            throttle = 0.0f;
            bodyAngle = 0.0f;
            turretAngle = 0.0f;
            mass = 5.0f;
        }
        sf::Vector2f position;
        sf::Vector2f velocity;
        float throttle;
        float bodyAngle;
        float turretAngle;
        float mass;
    };

    class Tank
    {
    public:
        int setPosition(sf::Vector2f p){
            body.setPosition(p);
            turret.setPosition(p);
            return 0;
        }
        sf::Sprite body;
        sf::Sprite turret;
        TankState tankState;

    };
};

#endif

