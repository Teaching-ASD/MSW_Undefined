#include"ObserverTextRenderer.h"

void ObserverTextRenderer::render(const Game& game) const{
    bool end = false;
    int x=0;
    int y=0;
    bool firstLine=true;
    int xmax=0;
    out << "\u2554";
    while(!end){
        try{
            if(game.getMarkedMap().get(x,y) == Map::type::Free || game.getMarkedMap().get(x,y) == Map::type::Monster){
                if(game.getHeroPos()!=nullptr &&game.getHeroPos()->x==x && game.getHeroPos()->y==y){
                    out << "┣┫";
                    }
                 else{                     
                     std::list<monsterPos> monsters = game.getMonsters();
                    switch (count_if(monsters.begin(),monsters.end(),[x,y](monsterPos monster){return monster.x == x && monster.y==y;}))
                    {
                    case(0): 
                            out << "\u2591\u2591";
                            break;
                    case(1):
                            out << "M\u2591";
                            break;
                    default:
                            out << "MM";
                            break;
                    }
                 }
                
            }
            else if(firstLine){
                out << "\u2550\u2550";
                
            } else if(x==0){
                out << "\u2551\u2588\u2588";
            }
            
            else{
                out<< "\u2588\u2588";
            }
            
            x++;
        }
        catch(Map::WrongIndexException &e){
            std::string err = e.what();
            if(err=="Y is wrong"){
                end = true;
            }
            else{
                if(!firstLine){
                out << "\u2551" << std::endl;
                y++;
                xmax=x;
                x=0;
                }
                else{
                    out << "\u2557" <<std::endl;
                    firstLine=false;
                    x=0;
                    y=0;
                }
            }
        }
    }
    out << "\u255A";
    for(int i=0;i<xmax;i++){
        out << "\u2550\u2550";
    }
    out << "\u255D" << std::endl;
}