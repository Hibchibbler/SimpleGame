#ifndef StartPopup_h_
#define StartPopup_h_

#include "GameStage.h"
#include "Images.h"

#include <SFML/Window.hpp>
#include <iostream>

namespace sg
{
    /*
    once all functions in the life cycle of a StartPopup have run,
    the client will call getSummary() to obtain the results.
    
    Here are the possible values returned by getSummary(), and their meaning:
        0x00000000 - Quit Application
        0x00000001 - Join a game
        0x00000002 - Host a game
    */
    class StartPopup : public sg::GameStage
    {
    public:
        StartPopup();
        sf::Uint32 onRemoteEvent(sg::TankGame & game, sg::CommEvent & e, sf::Uint32 packetType);
        //called from TankGame::onLocalEvent
        sf::Uint32 onWindowEvent(sg::TankGame & game, sf::RenderWindow & w, sf::Event & event);

        //called from TankGame::onInit
        sf::Uint32 doInit(sg::TankGame & game, int w, int h);

        //
        sf::Uint32 doLocalInput(sg::TankGame & game);
        sf::Uint32 doLoop(sg::TankGame & game);
        sf::Uint32 doCleanup(sg::TankGame & game);
        sf::Uint32 getSummary();
        void setSummary(sf::Uint32 s);
        sf::Uint32 doDraw(sf::RenderWindow & target);
        
        
    private://internal variables
        
        unsigned int width;
        unsigned int height;
        ImageAsset popupBack;
        ImageAsset button_hover;
        ImageAsset button_pressed;

        sf::Sprite joinSp;
        sf::Sprite hostSp;
        sf::Sprite quitSp;
        sf::Sprite spriteBack;

        sf::Font font;
        sf::Text title;
        sf::Text entryJoin;
        sf::Text entryHost;
        sf::Text entryQuit;
    
        sf::View popupView;
    private://internal functions
        sf::Uint32 summary;
        sf::Uint32 processMouseButtonPressed(sf::RenderWindow & w, sf::Event &e);
        void processMouseButtonReleased(sf::RenderWindow & w, sf::Event &e);
        int setPopupView(sf::View &v);
    };
};



#endif










