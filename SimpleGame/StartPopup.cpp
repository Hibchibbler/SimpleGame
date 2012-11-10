#include "StartPopup.h"


sg::StartPopup::StartPopup(){
    summary = 0;
}
sf::Uint32 sg::StartPopup::onRemoteEvent(sg::TankGame & game, sg::CommEvent & e, sf::Uint32 packetType)
{
    return 0;
}
//called from TankGame::onLocalEvent
sf::Uint32 sg::StartPopup::onWindowEvent(sg::TankGame & game, sf::RenderWindow & w, sf::Event & event){
    switch (event.type){
    case sf::Event::KeyPressed:
        break;
    case sf::Event::Closed:
        //the window is closed already
        //break;
        return 2;
    case sf::Event::MouseButtonPressed:
        return processMouseButtonPressed(w,event);
    case sf::Event::MouseButtonReleased:
        processMouseButtonReleased(w,event);
        break;
    case sf::Event::Resized:
        width = event.size.width;
        height = event.size.height;
        break;
    }
    return 3;
}

//called from TankGame::onInit
sf::Uint32 sg::StartPopup::doInit(sg::TankGame & game, int w, int h){
    width = w;
    height = h;

    //Font
    font.loadFromFile("Assets\\digital-7mono.ttf");
    //Background
        
    popupBack.load("Assets\\popup1.png");
    button_hover.load("Assets\\button_hover1.png");
    button_pressed.load("Assets\\button_pushed1.png");
       
    spriteBack.setTexture(popupBack.getTexture());
        
    //text should be 15 offset from top
    title.setString("Tank Game!");
    title.setFont(font);
    title.setColor(sf::Color::Green);
    title.setScale(1.3,1.3);
    title.setPosition(300,105);

    entryJoin.setColor(sf::Color::Green);


    entryJoin.setString("Join");
    entryJoin.setFont(font);
    entryJoin.setColor(sf::Color::Green);
    entryJoin.setPosition(125-entryJoin.getGlobalBounds().width/2,65);
    //entryJoin.scale(2.07f,2.0f);
        
        

        
    entryHost.setString("Host");
    entryHost.setFont(font);
    entryHost.setColor(sf::Color::Green);
    entryHost.setPosition(125-entryHost.getGlobalBounds().width/2,160);
       

    entryQuit.setString("Quit");
    entryQuit.setFont(font);
    entryQuit.setColor(sf::Color::Green);
    entryQuit.setPosition(125-entryQuit.getGlobalBounds().width/2,370);
  


    //buttonJoin
    joinSp.setTexture(button_hover.getTexture());joinSp.setPosition(125-joinSp.getGlobalBounds().width/2,50);
    hostSp.setTexture(button_hover.getTexture());hostSp.setPosition(125-hostSp.getGlobalBounds().width/2, 145);
    quitSp.setTexture(button_hover.getTexture());quitSp.setPosition(125-quitSp.getGlobalBounds().width/2, 355);

    setPopupView(popupView);
    return 0;
        
}

//
sf::Uint32 sg::StartPopup::doLocalInput(sg::TankGame & game){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
    {
        std::cout << "!";
    }
    return 0;
}
sf::Uint32 sg::StartPopup::doLoop(sg::TankGame & game)
{
    return summary;
}
sf::Uint32 sg::StartPopup::doCleanup(sg::TankGame & game)
{
    return 0;
}
sf::Uint32 sg::StartPopup::getSummary(){
    return summary;
}
void sg::StartPopup::setSummary(sf::Uint32 s){
    summary = s;
}
sf::Uint32 sg::StartPopup::doDraw(sf::RenderWindow & target){

    //Save old view, and set a new
    sf::View oldView;
    oldView = target.getView();
    target.setView(popupView);
        
    //render window images
            
    target.draw(spriteBack);
    target.draw(title);
    target.draw(joinSp);
    target.draw(hostSp);
    target.draw(quitSp);
    target.draw(entryJoin);
    target.draw(entryHost);
    target.draw(entryQuit);


    //reset old view
    target.setView(oldView);
    return 0;

}

sf::Uint32 sg::StartPopup::processMouseButtonPressed(sf::RenderWindow & w, sf::Event &e){
    //if click intersects button 1,2 or 3 boundary, then
    //change the pic to pressed, and do
    //if (e.mouseButton.x
    sf::Vector2f worldCoord;
    worldCoord = w.convertCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y),popupView);
    //std::cout << worldCoord.x << ", " << worldCoord.y << std::endl;
    if (joinSp.getGlobalBounds().contains(worldCoord)){
        std::cout << "Clicked Join" << std::endl;
        joinSp.setTexture(button_pressed.getTexture());
        setSummary(0x00000001);
        return 0;
    }else if (hostSp.getGlobalBounds().contains(worldCoord)){
        std::cout << "Clicked Host" << std::endl;
        hostSp.setTexture(button_pressed.getTexture());
        setSummary(0x00000002);
        return 1;
    }else if (quitSp.getGlobalBounds().contains(worldCoord)){
        std::cout << "Clicked Quit" << std::endl;
        quitSp.setTexture(button_pressed.getTexture());
        setSummary(0x00000003);
        return 2;
    }else{//Nothing happened
        setSummary(0x00000000);
    }
    return 3;
}
void sg::StartPopup::processMouseButtonReleased(sf::RenderWindow & w, sf::Event &e){
    joinSp.setTexture(button_hover.getTexture());joinSp.setPosition(125-joinSp.getGlobalBounds().width/2,50);
    hostSp.setTexture(button_hover.getTexture());hostSp.setPosition(125-hostSp.getGlobalBounds().width/2, 145);
    quitSp.setTexture(button_hover.getTexture());quitSp.setPosition(125-quitSp.getGlobalBounds().width/2, 355);
}
int sg::StartPopup::setPopupView(sf::View &v)
{
    v.setCenter(width/2,height/2);
    v.setSize(width,height);
    sf::FloatRect viewport;
    viewport.top = 0.25;
    viewport.left= 0.25;
    viewport.width = 0.5*(width/height);
    viewport.height = 0.5;
    v.setViewport(viewport);
    return 0;
}


























