#include "LobbyPopup.h"
#include "TankGame.h"


sf::Uint32 sg::LobbyPopup::onRemoteEvent(sg::TankGame & game, sg::CommEvent & e, sf::Uint32 packetType){
    return 0;
}
sf::Uint32 sg::LobbyPopup::onWindowEvent(sg::TankGame & game, sf::RenderWindow & w, sf::Event & event){
        
    //Pass it down to textbox which wants to know if it was clicked in or not.
    if (event.type == sf::Event::MouseButtonPressed){
        //sf::vector<Team*>::iterator
        for (auto i = team1.begin();i != team1.end();++i){
            (*i)->processMouseButtonPressed(w, event, popupView);
        }
        for (auto i = team2.begin();i != team2.end();++i){
            (*i)->processMouseButtonPressed(w, event, popupView);
        }
        //name1.processMouseButtonPressed(*w,e);
    }else if (event.type == sf::Event::KeyPressed){
        for (auto i = team1.begin();i != team1.end();++i){
            (*i)->processKeypress(event);
        }

        for (auto i = team2.begin();i != team2.end();++i){
            (*i)->processKeypress(event);
        }
    }else if (event.type == sf::Event::Resized){

    }
        
    return 0;
}
sf::Uint32 sg::LobbyPopup::doInit(sg::TankGame & game, int w, int h){
    
    this->w = w;
    this->h = h;

    lobbyBackground.load("Assets\\lobby_background.png");


    startBtn.load("Assets\\button_hover1.png");
    startBtnSprite.setTexture(startBtn.getTexture());

    
    for (int h = 0;h < 5;h++){

        team1.push_back(new TextBox());
        team1.back()->load();
        team1.back()->scale(sf::Vector2f(1.09,1.0));
        team1.back()->setString(std::string(""));
        team1.back()->setPosition(sf::Vector2f(57,59+h*30));
    }
    //team1.push_back(new TextBox());
    //team1.back()->load();
    //team1.back()->scale(sf::Vector2f(1.09,1.0));
    //team1.back()->setString(std::string("Guapodotsa"));
    //team1.back()->setPosition(sf::Vector2f(57,89));
    for (int h = 0;h < 5;h++){
        team2.push_back(new TextBox());
        team2.back()->load();
        team2.back()->scale(sf::Vector2f(1.09,1.0));
        team2.back()->setString(std::string(""));
        team2.back()->setPosition(sf::Vector2f(275,59+h*30));
    }
    

    //team2.push_back(new TextBox());
    //team2.back()->load();
    //team2.back()->scale(sf::Vector2f(1.09,1.0));
    //team2.back()->setString(std::string("Cheryl"));
    //team2.back()->setPosition(sf::Vector2f(157,109));

    //lobbyBackground.getImage().createMaskFromColor(sf::Color::Cyan,0);
    lobbyBackgroundSprite.setTexture(lobbyBackground.getTexture());
    startBtnSprite.setPosition(65,450);
    setPopupView(popupView);
    return 0;
}
sf::Uint32 sg::LobbyPopup::doLocalInput(sg::TankGame & game){
    return 0;
}
sf::Uint32 sg::LobbyPopup::doLoop(sg::TankGame & game){

    

    return 0;
}
sf::Uint32 sg::LobbyPopup::doCleanup(sg::TankGame & game){
    return 0;
}

sf::Uint32 sg::LobbyPopup::doDraw(sf::RenderWindow & target) {
     //Save old view, and set a new
    sf::View oldView;
    oldView = target.getView();
    target.setView(popupView);

    target.draw(lobbyBackgroundSprite);
    target.draw(startBtnSprite);
    for (auto i = team1.begin();i != team1.end();++i){
        target.draw(*(*i));
    }

    for (auto i = team2.begin();i != team2.end();++i){
        target.draw(*(*i));
    }


     //reset old view
    target.setView(oldView);
    return 0;
}


int sg::LobbyPopup::setPopupView(sf::View &v)
{
    v.setCenter(w/2,h/2);
    v.setSize(w,h);
    sf::FloatRect viewport;
    viewport.top = 0.25;
    viewport.left= 0.25;
    viewport.width = 0.5*(w/h);
    viewport.height = 0.5;
    v.setViewport(viewport);
    return 0;
}

