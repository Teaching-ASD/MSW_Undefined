#include"ObserverSVGRenderer.h"

void ObserverSVGRenderer::render(const Game& game) const{
    std::string nf = "svg/not_found.svg";
    std::string out;
    bool end = false;
    int x=0;
    int y=0;
    int xmax=0;
    while(!end){
        try{
            if(game.getMarkedMap().get(x,y) == Map::type::Free || game.getMarkedMap().get(x,y) == Map::type::Monster){
                if(game.getHeroPos()!=nullptr &&game.getHeroPos()->x==x && game.getHeroPos()->y==y){
                    if(std::filesystem::exists(game.getHeroPos()->hero->getTexture())){
                        out += "<image href=\""+game.getHeroPos()->hero->getTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                    }
                    else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                    }
                    }
                 else{                     
                    std::list<monsterPos> monsters = game.getMonsters();

                    bool monsterExist = false;
                    for(monsterPos monster : monsters){
                        if(monster.x == x && monster.y==y){
                            if(std::filesystem::exists(monster.monster.getTexture())){
                                out += "<image href=\""+monster.monster.getTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                            }
                            else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                            }
                            monsterExist = true;
                        }

                    }
                    if(!monsterExist){
                         if(std::filesystem::exists(game.getFreeTexture())){
                                out += "<image href=\""+game.getFreeTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                            }
                            else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                            }
                    }
                 }
                
            }   
            else{
               if(std::filesystem::exists(game.getWallTexture())){
                                out += "<image href=\""+game.getWallTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                            }
                            else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(x*10)+"\" y=\""+std::to_string(y*10)+"\"/>\n"; 
                            }
            }
            
            x++;
        }
        catch(Map::WrongIndexException &e){
            std::string err = e.what();
            if(err=="Y is wrong"){
                end = true;
            }
            else{
                out+="\n";
                y++;
                xmax=x;
                x=0;
            }
        }
    }
    std::string out1= "<svg width=\""+std::to_string(xmax*10)+ "\" height=\"" +std::to_string(y*10)+ "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    out1+=out;
    out1+="</svg>";
    std::ofstream fileos(fname);
    fileos << out1;
    fileos.close();
}