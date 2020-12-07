#include"CharacterSVGRenderer.h"

void CharacterSVGRenderer::render(const Game& game) const{
    std::string nf = "svg/not_found.svg";
    std::string out;
    int xmax=0;
    int jmax=0;
    for(int j=((game.getHeroPos()->y)-(game.getHeroPos()->hero->getLightRadius()));j<=((game.getHeroPos()->y)+(game.getHeroPos()->hero->getLightRadius()));j++){
        if(j>=0){
        int max=0;
        for(int i=((game.getHeroPos()->x)-(game.getHeroPos()->hero->getLightRadius()))-1;i<=((game.getHeroPos()->x)+(game.getHeroPos()->hero->getLightRadius()));i++){
        try{
            if(game.getMarkedMap().get(i,j) == Map::type::Free || game.getMarkedMap().get(i,j) == Map::type::Monster){
                max++;
                if(game.getHeroPos()!=nullptr &&game.getHeroPos()->x==i && game.getHeroPos()->y==j){
                    if(std::filesystem::exists(game.getHeroPos()->hero->getTexture())){
                        out += "<image href=\""+game.getHeroPos()->hero->getTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                    }
                    else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                    }
                    }
                 else{
                    std::list<monsterPos> monsters = game.getMonsters();

                    bool monsterExist = false;
                    for(monsterPos monster : monsters){
                        if(monster.x == i && monster.y==j){
                            if(std::filesystem::exists(monster.monster.getTexture())){
                                out += "<image href=\""+monster.monster.getTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                            }
                            else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                            }
                            monsterExist = true;
                        }

                    }
                    if(!monsterExist){
                         if(std::filesystem::exists(game.getFreeTexture())){
                                out += "<image href=\""+game.getFreeTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                            }
                            else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                            }
                    }
                 }
                
            }
            else if(game.getMarkedMap().get(i,j) == Map::type::Wall){
                if(std::filesystem::exists(game.getWallTexture())){
                                out += "<image href=\""+game.getWallTexture() +"\" height=\"10\" width=\"10\" x=\""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                            }
                            else{
                        out += "<rect fill=\"#000000\" height=\"10\" width=\"10\" x= \""+std::to_string(i*10)+"\" y=\""+std::to_string(j*10)+"\"/>\n"; 
                            }
                                max++;
            }
        if(max>xmax){xmax=max;}
        }
        catch(Map::WrongIndexException &e){jmax=j;}
    }
}
    std::string out1= "<svg width=\""+std::to_string(xmax*10)+ "\" height=\"" +std::to_string((jmax+1)*10)+ "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    out1+=out;
    out1+="</svg>";
    std::ofstream fileos(fname);
    fileos << out1;
    fileos.close();
}

}