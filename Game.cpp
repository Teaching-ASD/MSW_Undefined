#include "Game.h"
#include<iostream>


Game::Game():MarkedMap(){};

Game::Game(std::string& mapfilename):MarkedMap(mapfilename){
    beeMap=true;
}

void Game::setMap(std::string filename){
    long unsigned int max=0;
    std::ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        throw "The file not exists";
    }
    std::string line;
    while(getline(file,line))
    {
        if(line.size()>max){max=line.size();}
        mapvector.push_back(line);

    }
    for(long unsigned int i=0;i<mapvector.size();i++){
        mapvector.at(i).pop_back();
        while(mapvector.at(i).size()<=max){
            mapvector.at(i)+="#";
        }
    }
    file.close();
    beeMap = true;
}


void Game::putHero(Hero hero, int x, int y) {
    if(beeMap == false){ throw Map::WrongIndexException(" There is no map loaded.");}

    if(get(x,y)==Map::type::Wall){throw OccupiedException(" Occupied block. ");};
    
    if(std::any_of(monsters.begin(),monsters.end(),[x,y](monsterPos i){return i.x == x && i.y==y;})){
            throw OccupiedException(" Occupied block. There is a monster in here.");

    }
    if(gameIsRunning) throw GameAlreadyStartedException("You can't change the map, because the game started");

    if(heroPos != nullptr){ throw AlreadyHasHeroException(" Map already has a hero." );}
    Hero* hero_ = new Hero(hero);
    heroPos = new Pos(hero_,x,y);
}

void Game::putMonster(Monster monster,int x,int y){

    if(beeMap == false){ throw Map::WrongIndexException(" There is no map loaded."); }

    if(get(x,y)==Map::type::Wall){throw OccupiedException(" Occupied block. ");};
    
    if(heroPos!=nullptr){
        if(heroPos->x == x && heroPos->y==y){

            throw OccupiedException(" Occupied block. There is a Hero in here.  ");

        }
    }
    monsters.push_back(monsterPos(monster,x,y));
};
void Game::run(){
        gameIsRunning = true;
        if(beeMap == false || heroPos==nullptr){ throw Game::NotInitializedException(" Map or Hero is not initialized."); }
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
    if(this->get(x,y) == Map::type::Free){
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
    else {std::cout << "The hero died."<< std::endl;
    }
    }
    else std::cout << "Wrong direction! This is a wall!"<< std::endl;
}



void Game::setChInMap(std::list<Monster>& monsters,Hero& hero,Game& game)const{

    std::vector<std::string> v = getVector();
    
    game.mapCout(v);
   // for(auto x : v){ std::cout<<x<<std::endl;}

    int x = 0, y=0;
    std::cout<<"Hero position:"<<std::endl; 
    std::cin>>x>>y;
    game.putHero(hero,x,y);
    v[y][x]='H';

    game.mapCout(v);

    for(auto i : monsters){
        std::cout<<"Monster" <<i.getName()<< " position:" <<std::endl; 
        std::cin>>x>>y;

        if(v[y][x]==' '){v[y][x]='M';}
        else{v[y][x]='W';}

        game.putMonster(i,x,y);
        game.mapCout(v);
    }

};


void Game::mapCout(std::vector<std::string> v) const {

    unsigned int max = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if(v[i].size() > max){max = v[i].size();}
    } 

    std::cout<<"╔";
    for (unsigned int i = 0; i < max*2; i++)
    {
        std::cout<<"═";
    }
    std::cout<<"╗"<<std::endl;;

    for(auto y : v){
        std::cout<<"║";
        for(auto x : y){
            
            if(x==' '){
                std::cout<<"░░";
            }
            else if(x=='#'){
                std::cout<<"██";
            }
            else if(x=='H'){
                std::cout<<"┣┫";
            }
            else if(x=='M'){
                std::cout<<"M░";
            }
            else if(x=='W'){ //W==tobb monster
                std::cout<<"MM";
            }
        }
        std::cout<<"║";
        std::cout<<"\n";
    }

    std::cout<<"╚";
    for (unsigned int i = 0; i < (max*2); i++)
    {
        std::cout<<"═";
    }
    std::cout<<"╝"<<std::endl;;
}



void Game::drawMap(){
    bool end = false;
    int x=0;
    int y=0;
    bool firstLine=true;
    int m=0;
    int xmax=0;
    std::cout << "\u2554";
    while(!end){
        try{
            if(this->get(x,y) == Map::type::Free){
                if(this->heroPos->x==x && this->heroPos->y==y){
                    std::cout << "┣┫";
                    }
                 else{  
                     m= count_if(monsters.begin(),monsters.end(),[x,y](monsterPos monster){return monster.x == x && monster.y==y;});
                    switch (m)
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
                    m=0;
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
