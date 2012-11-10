#ifndef LobbyPopup_h_
#define LobbyPopup_h_

#include "GameStage.h"
#include "Images.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <algorithm>

namespace sg
{
    /*
    once all functions in the life cycle of a LobbyPopup have run,
    the client will call getSummary() to obtain the results.
    
    Here are the possible values returned by getSummary(), and their meaning:
        0x00000000 - Start Game
        0x00000001 - Cancel Game
    */
    class TextBox : public sf::Drawable
    {
    public:
        TextBox(){

        }
        sf::Uint32 load(){
            hasFocus = false;
            font.loadFromFile("Assets\\digital-7mono.ttf");
            aString.setFont(font);
            aString.setColor(sf::Color::Green);
            aString.scale(0.96,0.80);
            backgroundAsset.load("Assets\\textbox_background2.png");
            backgroundSp.setTexture(backgroundAsset.getTexture());

            //backgroundSp.
            setPosition(sf::Vector2f(57,59));
            //aString.setPosition(sf::Vector2f(63,58));
            return 0;
        }
        sf::Uint32 processMouseButtonPressed(sf::RenderWindow & w, sf::Event &e, sf::View & v)
        {
            sf::Vector2f wc;
            wc = w.convertCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y), v);

            //Hit test text box. using background png as boundary.
            if (backgroundSp.getGlobalBounds().contains(wc)){
                std::string s = aString.getString();
                if (hasFocus == false)
                    s.append("_");
                hasFocus = true;
                aString.setString(s);
            }else{
                std::string s = aString.getString();
                if (hasFocus == true)
                    s.pop_back();
                aString.setString(s);
                hasFocus = false;
            }
            return 0;
        }
        sf::Uint32 processKeypress(sf::Event &e)
        {
            if (e.key.code >= sf::Keyboard::A &&
                e.key.code <= sf::Keyboard::Z){
                if (hasFocus){
                    std::string s = aString.getString();
                    if (s.size() < 13){
                        s.pop_back();//.erase(s.end()-1);
                        s.append(getASCII(e.key.code));
                        s.append("_");
                        aString.setString(s);
                    }
                }
            }else if (e.key.code == sf::Keyboard::BackSpace){
                if (hasFocus){
                    std::string s = aString.getString();
                    if (s.size() > 1){
                        s.pop_back();
                        s.pop_back();
                        s.append("_");
                        aString.setString(s);
                    }
                }
            }
            return 0;
        }
        void scale(sf::Vector2f &m){
            backgroundSp.scale(m);
        }
        void setPosition(sf::Vector2f position){
            backgroundSp.setPosition(position);
            position.x += 6;
            position.y += -1;
            aString.setPosition(position);
        }
        void setString(std::string &s){
            aString.setString(s);
        }   
    private:
        bool hasFocus;
        sf::Font font;
        sf::Text aString;
        ImageAsset backgroundAsset;
        sf::Sprite backgroundSp;
        void draw(sf::RenderTarget & target, sf::RenderStates states) const
        {
            //First draw the textbox background
            target.draw(backgroundSp, states);
            //then the string
            target.draw(aString, states);
        }    
        std::string getASCII(sf::Keyboard::Key k){
            sf::Uint32 mk = k;
            mk += 65;
            std::string s;
            s.push_back(mk);
            return s;
        }
    };

    class TankGame;
    class CommEvent;

    class LobbyPopup : public GameStage
    {
    public:
        sf::Uint32 onRemoteEvent(sg::TankGame & game, sg::CommEvent & e, sf::Uint32 packetType);
        sf::Uint32 onWindowEvent(sg::TankGame & game, sf::RenderWindow & w, sf::Event & event);
        sf::Uint32 doInit(sg::TankGame & game, int w, int h);
        sf::Uint32 doLocalInput(sg::TankGame & game);
        sf::Uint32 doLoop(sg::TankGame & game);
        sf::Uint32 doCleanup(sg::TankGame & game);
        sf::Uint32 doDraw(sf::RenderWindow & target);
    private:
        sf::View popupView;
        std::vector<TextBox*> team1;
        std::vector<TextBox*> team2;
        ImageAsset lobbyBackground;
        ImageAsset startBtn;
        sf::Sprite lobbyBackgroundSprite;
        sf::Sprite startBtnSprite;
        int w,h;
    private:
        int setPopupView(sf::View &v);
    };

};

#endif


