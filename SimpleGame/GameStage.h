#ifndef GameStage_h_
#define GameStage_h_

#include <SFML/Graphics.hpp>

namespace sg
{
    class TankGame;
    class CommEvent;

    class GameStage
    {
    public:
        virtual ~GameStage(){
        }

        virtual sf::Uint32 onRemoteEvent(sg::TankGame & game, sg::CommEvent & e, sf::Uint32 packetType)=0;

        virtual sf::Uint32 onWindowEvent(sg::TankGame & game, sf::RenderWindow & w, sf::Event & event)=0;

        virtual sf::Uint32 doInit(sg::TankGame & game, int w, int h)=0;

        virtual sf::Uint32 doLocalInput(sg::TankGame & game)=0;

        virtual sf::Uint32 doLoop(sg::TankGame & game)=0;

        virtual sf::Uint32 doCleanup(sg::TankGame & game)=0;

        virtual sf::Uint32 doDraw(sf::RenderWindow &window)=0;
    
        void setId(sf::Uint32 id){ this->id = id; }
        sf::Uint32 getId(){ return id; }
    
        void setVisible(bool v){visible=v;}
        bool getVisible(){return visible;}

        void setSummary(sf::Uint32 s){summary=s;}
        sf::Uint32 getSummary(){return summary;}
    private:
        bool visible;
        sf::Uint32 id;
        sf::Uint32 summary;
    };

};


#endif

