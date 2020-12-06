#include"HeroTextRenderer.h"

void HeroTextRenderer::render(const Game& game) const{
    int xmax=0;
    bool firstLine=true;
    std::cout << "\u2554";
    for(int j=((game.getHeroPos()->y)-(game.getHeroPos()->hero->getLightRadius()));j<=((game.getHeroPos()->y)+(game.getHeroPos()->hero->getLightRadius()));j++){
        if(j>=0||firstLine){
        int id;
        int max=0;
        bool hasleft=false;
        for(int i=((game.getHeroPos()->x)-(game.getHeroPos()->hero->getLightRadius()))-1;i<=((game.getHeroPos()->x)+(game.getHeroPos()->hero->getLightRadius()));i++){
        if(i==((game.getHeroPos()->x)-(game.getHeroPos()->hero->getLightRadius()))-1 && !hasleft && j>=0){
                if(!firstLine){
                try{
                game.getMarkedMap().get(game.getHeroPos()->x,j);
                std::cout << "\u2551";
                hasleft=true;
            }
            catch(Map::WrongIndexException &e){}
                }
        }
        else{
        try{
            if(game.getMarkedMap().get(i,j) == Map::type::Free || game.getMarkedMap().get(i,j) == Map::type::Monster){
                max++;
                if(firstLine){
                std::cout << "\u2550\u2550";     
                }
                else
                if(game.getHeroPos()!=nullptr &&game.getHeroPos()->x==i && game.getHeroPos()->y==j){
                    std::cout << "┣┫";
                    }
                 else{
                     std::list<monsterPos> monsters = game.getMonsters();
                    switch (count_if(monsters.begin(),monsters.end(),[i,j](monsterPos monster){return monster.x == i && monster.y==j;}))
                    {
                    case(0): 
                            std::cout << "\u2591\u2591";
                            break;
                    case(1):
                            std::cout << "M\u2591";

                            break;
                    default:
                            std::cout << "MM";

                            break;
                    }
                 }
                
            }
            else if(firstLine){
                std::cout << "\u2550\u2550";     
            }
            else if(game.getMarkedMap().get(i,j) == Map::type::Wall){
                std::cout<< "\u2588\u2588";
                                max++;
            }

            //x++;
        if(max>xmax){xmax=max;}
        }
        catch(Map::WrongIndexException &e){}
        }
        id=i;
        }
        if(id!=(((game.getHeroPos()->x)-(game.getHeroPos()->hero->getLightRadius()))-1)){
        try{
            game.getMarkedMap().get(id+1,j);
            if(firstLine){
            std::cout << "\u2557"<< std::endl;
            firstLine=false;
            j--;
            }
            else{
            std::cout << "\u2551";
            std::cout << std::endl;
            }
            }
            catch(Map::WrongIndexException &e){
            std::string err = e.what();
            if(err!="Y is wrong"){          if(firstLine){
            std::cout << "\u2557"<< std::endl;
            firstLine=false;
            j--;
            }
            else{std::cout << "\u2551" << std::endl;}}
            }
        }
    
    }
    }
        std::cout << "\u255A";
    for(int i=0;i<xmax;i++){
        std::cout << "\u2550\u2550";
    }
    std::cout << "\u255D" << std::endl;
}
    