#include "Json.h"
#include<iostream>

Json::Json(){}

Json::~Json(){
    this->adatok.clear();
}

void Json::keyTester(std::string data, std::string fname=" "){
        //check duplicated keys
        if(data.size() >= data.find("name", data.find("name")+1)){
            throw std::invalid_argument("The Hero "+fname+" has two name keys.");
        }
        if(data.size() >= data.find("hp", data.find("hp")+1)){
            throw std::invalid_argument("The Hero "+fname+"  has two hp keys.");
        }
        if(data.size() >= data.find("dmg", data.find("dmg")+1)){
            throw std::invalid_argument("The Hero "+fname+"  has two dmg keys.");
        }
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
        if(data.find(',',data.find("hp"))<data.find('}',data.find("hp"))){
            hp_=data.substr(
            data.find(":", data.find("hp"))+1,
            data.find(',',data.find("hp"))-data.find(":",data.find("hp"))-1
	        );
        }
        else{
            hp_=data.substr(
            data.find(":", data.find("hp"))+1,
            data.find('}',data.find("hp"))-data.find(":",data.find("hp"))-1
	        );
        }

        //get damage
        if(data.find(',', data.find("dmg"))<data.find('}', data.find("dmg"))){
            dmg_=data.substr(
            data.find(":", data.find("dmg"))+1,
            data.find(',', data.find("dmg"))-data.find(":",data.find("dmg"))-1
            );
        }
        else{
            dmg_=data.substr(
            data.find(":", data.find("dmg"))+1,
            data.find('}', data.find("dmg"))-data.find(":",data.find("dmg"))-1
            );
        }

        //pair keys and datas
        std::pair<std::string,std::string> nev=std::make_pair("name", hname);
        adatok.insert(nev);
        std::pair<std::string,std::string> hape=std::make_pair("hp", hp_);
        adatok.insert(hape);
        std::pair<std::string,std::string> damago=std::make_pair("dmg", dmg_);
        adatok.insert(damago);


};

std::map<std::string,std::string> Json::parseString(std::string data){
        this->keyTester(data);
        this->internalParser(data);
        return adatok;
}


std::map<std::string, std::string> Json::parseFile(std::string fname){
        std::ifstream file;
        const std::exception e;
        file.open(fname);
	    if(!file.is_open()){throw std::invalid_argument("The file " +fname+ " not exist");}
        std::string hero,
            line;
        while (getline(file,line))
        {
            hero.append(line);          
        }
        this->keyTester(hero, fname);
        this->internalParser(hero);
        file.close();
        return adatok;
}


std::istream& operator>>(std::istream& in, Json& j){
    std::string temp;
    char a;
    while(in.get(a) && a!='\n')
    {
        temp.push_back(a);
    }
    j.keyTester(temp);
    j.internalParser(temp);
    return in;
}

std::map<std::string,std::string> Json::getAdatok(){
    return this->adatok;
}