#include "Json.h"
#include<iostream>

Json::Json(){}

Json::~Json(){
    this->adatok.clear();
}
void Json::internalParser(std::string data){
            std::string hname,
            dmg_,
            hp_;
        // remove whitespaces and resize
        data.erase(remove_if(data.begin(), data.end(), isspace), data.end());
        // get name
        hname=data.substr(
        data.find(":\"",data.find("name"))+2,
        (
        (data.find("\"",data.find(":\"",data.find("name"))+3))-
        (data.find(":\"",data.find("name"))+2)
        )
        );

        //get hp
		hp_=data.substr(
		data.find(":", data.find("hp"))+1,
		data.find('}' || ',',data.find("hp"))-data.find(":",data.find("hp"))-1
		);

        //get damage
		dmg_=data.substr(
		data.find(":", data.find("dmg"))+1,
		data.find('}' || ',', data.find("dmg"))-data.find(":",data.find("dmg"))-1
		);

        //pair keys and datas
        std::pair<std::string,std::string> nev=std::make_pair("name", hname);
        adatok.insert(nev);
        std::pair<std::string,std::string> hape=std::make_pair("hp", hp_);
        adatok.insert(hape);
        std::pair<std::string,std::string> damago=std::make_pair("dmg", dmg_);
        adatok.insert(damago);
};

std::map<std::string,std::string> Json::parser(std::string data){
        if(data.size() >= data.find("name", data.find("name")+1)){
            throw std::invalid_argument("The string has two name keys.");
        }
        if(data.size() >= data.find("hp", data.find("hp")+1)){
            throw std::invalid_argument("The string  has two hp keys.");
        }
        if(data.size() >= data.find("dmg", data.find("dmg")+1)){
            throw std::invalid_argument("The string  has two dmg keys.");
        }
        this->internalParser(data);
        return adatok;
}


std::map<std::string, std::string> Json::parseFile(std::string fname){
        std::ifstream file;
        const std::exception e;
        file.open(fname);
	    if(!file.is_open()){throw std::invalid_argument("The file " +fname+ " not exist");}
        std::string hero,
            hname,
            dmg_,
            hp_,
            line;
        while (getline(file,line))
        {
            hero.append(line);
                
        }
        //check duplicated keys
        if(hero.size() >= hero.find("name", hero.find("name")+1)){
            throw std::invalid_argument("The file "+fname+" has two name keys.");
        }
        if(hero.size() >= hero.find("hp", hero.find("hp")+1)){
            throw std::invalid_argument("The file "+fname+"  has two hp keys.");
        }
        if(hero.size() >= hero.find("dmg", hero.find("dmg")+1)){
            throw std::invalid_argument("The file "+fname+"  has two dmg keys.");
        }
        this->internalParser(hero);
        return adatok;
}


/*std::istream& operator>>(std::istream& in, Json& j){
    
}*/