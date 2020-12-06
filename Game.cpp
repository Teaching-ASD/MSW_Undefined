#include "Game.h"
#include<iostream>


Game::Game(){MarkedMap map;};

Game::Game(std::string& mapfilename):map(MarkedMap(mapfilename)){
    beeMap=true;
}

void Game::setMap(const MarkedMap &map){

    if(monsters.size() > 0 || heroPos != nullptr ){throw AlreadyHasUnitsException(" You can't change the map, because it contains units.");}

    if(gameIsRunning){throw GameAlreadyStartedException("You can't change the map, because the game started");}
    
    this->map = map;
    beeMap=true;
}


void Game::putHero(Hero hero, int x, int y) {
    if(beeMap == false){ throw Map::WrongIndexException(" There is no map loaded.");}
    if(map.get(x,y)==Map::type::Wall){throw OccupiedException(" Occupied block. ");};
    
    if(gameIsRunning) throw GameAlreadyStartedException("You can't change the Hero, because the game started");

    if(heroPos != nullptr){ throw AlreadyHasHeroException(" Map already has a hero." );}
    Hero* hero_ = new Hero(hero);
    heroPos = new Pos(hero_,x,y);
}

void Game::putMonster(Monster monster,int x,int y){

    if(beeMap == false){ throw Map::WrongIndexException(" There is no map loaded."); }

    if(map.get(x,y)==Map::type::Wall){throw OccupiedException(" Occupied block. ");};

    monsters.push_back(monsterPos(monster,x,y));
};
void Game::run(){
        gameIsRunning = true;
        if(beeMap == false || heroPos==nullptr){ throw Game::NotInitializedException(" Map or Hero is not initialized."); }
        this->step(this->heroPos->x, this->heroPos->y);
        while(monsters.size()!=0 && heroPos->hero->isAlive()){
            this->drawMap();
            std::string direction;
            std::cout << "Enter a direction!"<<std::endl;
            std::cin >> direction;
            if(direction == "north"){
                this->step(this->heroPos->x, this->heroPos->y-1);

            }else if(direction == "south"){
                this->step(this->heroPos->x, this->heroPos->y+1);

            }else if(direction == "east"){
                this->step(this->heroPos->x+1, this->heroPos->y);

            }else if(direction == "west"){
                this->step(this->heroPos->x-1, this->heroPos->y);
            }else if(direction == "exit"){
                return ;
            }
            else std::cout << "Wrong direction! try again!" << std::endl;
        }
        if(heroPos->hero->isAlive()){
        this->drawMap();
        std::cout << heroPos->hero->getName() << " cleared the map." << std::endl;
        }
        gameIsRunning = false;

}

void Game::step(int x, int y){
    if(this->map.get(x,y) == Map::type::Free || this->map.get(x,y) == Map::type::Monster){
        std::list<monsterPos>::iterator i = monsters.begin();
        while(i!=monsters.end()){
            if(i->x == x && i->y==y){
            this->heroPos->hero->fightTilDeath(i->monster);
            i= monsters.erase(i);
            }
            else {++i;}
        }
        if(this->heroPos->hero->isAlive()){
            this->heroPos->x = x;
            this->heroPos->y = y;
        }
        else {
            std::cout << "The hero died."<< std::endl;
        }
    }
    else std::cout << "Wrong direction! This is a wall!"<< std::endl;
}



void Game::setChInMap(const std::list<Monster>& monsters, const Hero& hero){
    this->drawMap();
    int x = 0, y=0;
    std::cout<<"Hero position:"<<std::endl; 
    std::cin>>x>>y;
    this->putHero(hero,x,y);
    this->drawMap();

    for(auto i : monsters){
        std::cout<<"Monster" <<i.getName()<< " position:" <<std::endl; 
        std::cin>>x>>y;
        this->putMonster(i,x,y);
        this->drawMap();
    }

};



void Game::drawMap(){
    
    bool end = false;
    int x=0;
    int y=0;
    bool firstLine=true;
    int xmax=0;
    std::cout << "\u2554";
    while(!end){
        try{
            if(this->map.get(x,y) == Map::type::Free || this->map.get(x,y) == Map::type::Monster){
                if(this->heroPos!=nullptr &&this->heroPos->x==x && this->heroPos->y==y){
                    std::cout << "┣┫";
                    }
                 else{
                    switch (count_if(monsters.begin(),monsters.end(),[x,y](monsterPos monster){return monster.x == x && monster.y==y;}))
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
                
            } else if(x==0){
                std::cout << "\u2551\u2588\u2588";
            }
            
            else{
                std::cout<< "\u2588\u2588";
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
                std::cout << "\u2551" << std::endl;
                y++;
                xmax=x;
                x=0;
                }
                else{
                    std::cout << "\u2557" <<std::endl;
                    firstLine=false;
                    x=0;
                    y=0;
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


void Game::lightradius()const {
    int x = this->heroPos->x;
    int y = this->heroPos->y;
    int r = this->heroPos->hero->getLightRadius();
    int max=0;
    int xk=0;
    int ymax=0;
    int xmax=0;
    bool end = false;
    int rowmax=0;
    while(!end)
    {
        try
        {
            map.get(0,ymax);
            try
            {
                xk++;
                map.get(xk,ymax);
                rowmax++;
            }
            catch(Map::WrongIndexException &e)
            {
                
                xk = -1;
                ymax++;
                if(xmax<rowmax)
                {
                    xmax=rowmax;
                    
                }
                rowmax=0;
            }
        }
        catch(Map::WrongIndexException &e)
        {end=true;}
    }


    try{
        for(int o = 0; o < r*2+1;o++){
            for(int i=0; i < r*2+1; i++)
            {
                if(x-r+i>=0 && y-r+o>=0)
                {
                    map.get(x-r+i,y-r+o);
                    max++;
                }
            
            }
            if(max>0)
            {
                break;
            }
        }
        
    }catch(Map::WrongIndexException &e)
    {
    }

    std::cout<<"╔";
    for (unsigned int i = 0; i < max*2; i++)
    {
        std::cout<<"═";
    }
    std::cout<<"╗"<<std::endl;

    int i = 0;
    try
    {
        bool print = true;
        bool monsterfound = false;
        for(int o = 0; o< r*2+1 ; o++)
        {   
            if(print == true &&  ymax > y-r+o)
            {
                if(x-r+i>=0 && y-r+o>=0 && x-r+i<xmax)
                {
                    map.get(x-r+i,y-r+o);
                }
                
                std::cout<<"║";
            }
            for(i = 0; i < r*2+1; i++)
            {
                if(x-r+i>=0 && y-r+o>=0 && x-r+i<xmax)
                {

                    print = true;
                    if(x-r+i==x && y-r+o==y)
                    {
                        std::cout<<"┣┫";
                    }
                    else if(map.get(x-r+i,y-r+o)==0)
                    {
                        std::cout<<"░░";
                    }
                    else if(map.get(x-r+i,y-r+o)==1)
                    {
                        std::cout<<"██";
                    }
                    else
                    {
                        
                        for(auto k : monsters)
                        {
                            if(x-r+i==k.x && y-r+o==k.y)
                            {
                                std::cout<<"M░";
                                monsterfound = true;
                            }
                        }
                        if(!monsterfound)
                        {
                            std::cout<<"░░";
                        }
                        monsterfound = false;
                    }
                    
                }
                else
                {
                    print = false;
                }
            }
            
            if(print == true ||( x-r+i>=xmax && y-r+o>=0))
            {
                std::cout<<"║";
                std::cout<<std::endl;
                print = true;
            }
            
        }
    }
    catch(Map::WrongIndexException &e)
    {}
    std::cout<<"╚";
    for (unsigned int i = 0; i < max*2; i++)
    {
        std::cout<<"═";
    }
    std::cout<<"╝"<<std::endl;
}
