/**********************************************************************************
Tank Game
Player.h

Copyright 2012
Daniel Ferguson, Eddie Stranberg
**********************************************************************************/

#ifndef Dashboard_h_
#define Dashboard_h_

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
namespace sg
{
    class Dashboard
    {
    public:
        Dashboard(){
        
        }
        ~Dashboard(){}

        void load(){
            hudPosition.x = 0;
            hudPosition.y = 0;

            hudFont.loadFromFile("digital-7mono.ttf");
            dashImage.loadFromFile("DashBoard.png");
            dashImage.createMaskFromColor(sf::Color::Cyan,0);
            dashTexture.loadFromImage(dashImage);

            dashSprite.setTexture(dashTexture);
            dashSprite.setPosition(0,0);
        
            health.setFont(hudFont);
            health.setColor(sf::Color::Green);
            health.scale(0.7f,0.7f);
            health.setPosition(0,0);

            position.setFont(hudFont);
            position.setColor(sf::Color::Green);
            position.scale(0.7f,0.7f);
            position.setPosition(0,60);

            velocity.setFont(hudFont);
            velocity.setColor(sf::Color::Green);
            velocity.scale(0.7f,0.7f);
            velocity.setPosition(0,100);

            angles.setFont(hudFont);
            angles.setColor(sf::Color::Green);
            angles.scale(0.7f,0.7f);
            angles.setPosition(0,20);

            health2.setFont(hudFont);
            health2.setColor(sf::Color::Green);
            health2.scale(0.7f,0.7f);
            health2.setPosition(300,120);
        }

        void setHealth(int h){ 
            if (h <= 0)
                health.setColor(sf::Color::Red);
            else
                health.setColor(sf::Color::Green);

            std::stringstream ss;
            ss << "   Health: " << std::setfill(' ') << std::setw(3)  << h;
            health.setString(ss.str());
        }

        void setHealth2(int h){ 
            if (h <= 0)
                health2.setColor(sf::Color::Red);
            else
                health2.setColor(sf::Color::Green);

            std::stringstream ss;
            ss << "Opponent Health: " << std::setfill(' ') << std::setw(3) << h;
            health2.setString(ss.str());
        }
    
        void setAngles(float bodyAngle, float turretAngle){
            std::stringstream ss;
            ss << "     Body: " << std::fixed << std::setprecision(1) << bodyAngle << std::endl << std::endl;
            ss << "   Turret: " << std::fixed << std::setprecision(1) << turretAngle;
            angles.setString(ss.str());
        }
    
        void setVelocity(sf::Vector2f v){
            std::stringstream ss;
            //ss << "vx: " << std::setfill(' ') << std::setw(4) << std::setprecision(2) << v.x << " vy: " << std::setfill(' ') << std::setw(4) << std::setprecision(2) << v.y;
            ss << "       vx: " << std::fixed <<std::setprecision(1) << v.x << std::endl << std::endl;
            ss << "       vy: " << std::fixed<< std::setprecision(1) << v.y;
            velocity.setString(ss.str());
        }

        void setPos(sf::Vector2f p){
            std::stringstream ss;
            //ss << "px: "<< std::setfill(' ') << std::setw(4)  << p.x << " py: " << std::setfill(' ') << std::setw(4) <<  p.y;
            ss << "       px: " << std::fixed << std::setprecision(1) << p.x << std::endl << std::endl;
            ss << "       py: " << std::fixed << std::setprecision(1) << p.y;
            position.setString(ss.str());
        }

        sf::Vector2f hudPosition;

        sf::Font hudFont;
        sf::Text health;
        sf::Text health2;
        sf::Text position;
        sf::Text velocity;
        sf::Text angles;

        sf::Image dashImage;
        sf::Texture dashTexture;
        sf::Sprite dashSprite;
    };
};
#endif

