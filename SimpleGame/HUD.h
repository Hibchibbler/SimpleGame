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
        hudPosition.x = 0;
        hudPosition.y = 0;
        
        //find some ttf somewhere on your system, and modify the loadFromFile line accordingly.
        //Side Note: fpgas are so rad. have to come up with a project for those.
        gameFont.loadFromFile("C:\\Xilinx\\13.2\\ISE_DS\\PlanAhead\\tps\\win64\\jre\\lib\\fonts\\LucidaBrightDemiBold.ttf");

        dashImage.loadFromFile("DashBoard.png");
        dashImage.createMaskFromColor(sf::Color::Cyan,0);
        dashTexture.loadFromImage(dashImage);

        dashSprite.setTexture(dashTexture);
        dashSprite.scale(0.5,00.5);
        
        health.setFont(gameFont);
        health.scale(0.25,0.25);

        position.setFont(gameFont);
        position.scale(0.25,0.25);

        velocity.setFont(gameFont);
        velocity.scale(0.25,0.25);

        angles.setFont(gameFont);
        angles.scale(0.25,0.25);

        health2.setFont(gameFont);
        health2.scale(0.25,0.25);

        


        //std::stringstream ss;
        //ss << "Health: " << player1.health;
        //health.setString(ss.str());
    }

    void setHealth(int h){ 
        std::stringstream ss;
        ss << "Your Health: " << h;
        health.setString(ss.str());
    }

    void setHealth2(int h){ 
        std::stringstream ss;
        ss << "Their Health: " << h;
        health2.setString(ss.str());
    }

    void setVelocity(sf::Vector2f v){
        std::stringstream ss;
        ss << "vx: " << v.x << ", vy:" << v.y;
        velocity.setString(ss.str());
    }

    void setPos(sf::Vector2f p){
        std::stringstream ss;
        ss << "px: " << p.x << ", py: " << p.y;
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

    sf::Image dashImage;
    sf::Texture dashTexture;
    sf::Sprite dashSprite;
};

#endif

