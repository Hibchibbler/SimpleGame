/**********************************************************************************
Tank Game
Player.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef HUD_h_
#define HUD_h_

#include <SFML/Graphics.hpp>
#include <sstream>

class HUD
{
public:
    HUD(){
        
    }
    ~HUD(){}

    void load(){
        //find some ttf somewhere on your system, and modify the loadFromFile line accordingly.
        //Side Note: fpgas are so rad. have to come up with a project for those.
        gameFont.loadFromFile("C:\\Xilinx\\13.2\\ISE_DS\\PlanAhead\\tps\\win64\\jre\\lib\\fonts\\LucidaBrightDemiBold.ttf");

        health.setPosition(5,5);
        health.setFont(gameFont);
        health.scale(0.25,0.25);

        position.setPosition(5,20);
        position.setFont(gameFont);
        position.scale(0.25,0.25);

        velocity.setPosition(5,35);
        velocity.setFont(gameFont);
        velocity.scale(0.25,0.25);

        angles.setPosition(5, 50);
        angles.setFont(gameFont);
        angles.scale(0.25,0.25);

        health2.setPosition(5,65);
        health2.setFont(gameFont);
        health2.scale(0.25,0.25);

        hudPosition.x = 0;
        hudPosition.y = 0;

        //std::stringstream ss;
        //ss << "Health: " << player1.health;
        //health.setString(ss.str());
    }

    void setHealth(int h){ 
        std::stringstream ss;
        ss << "Health: " << h;
        health.setString(ss.str());
    }

    void setHealth2(int h){ 
        std::stringstream ss;
        ss << "Health2: " << h;
        health2.setString(ss.str());
    }

    void setVelocity(sf::Vector2f v){
        std::stringstream ss;
        ss << "Velocity: " << v.x << ", " << v.y;
        velocity.setString(ss.str());
    }

    void setPos(sf::Vector2f p){
        std::stringstream ss;
        ss << "Position: " << p.x << ", " << p.y;
        position.setString(ss.str());
    }

    void setAngles(float bodyAngle, float turretAngle){
        std::stringstream ss;
        ss << "Body: " << bodyAngle << std::endl;
        ss << "Turret: " << turretAngle;
        angles.setString(ss.str());
    }

    sf::Vector2f hudPosition;

    sf::Font gameFont;
    sf::Text health;
    sf::Text health2;
    sf::Text position;
    sf::Text velocity;
    sf::Text angles;
};

#endif

