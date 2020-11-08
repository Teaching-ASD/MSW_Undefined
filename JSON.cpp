#include "JSON.h"

JSON::JSON(){}

JSON::JSON(std::map<std::string,std::string> adatok_) : adatok(adatok_){}


JSON::~JSON(){
    this->adatok.clear();
}

void JSON::keyTester(std::string data, std::string key){
        //check duplicated keys
        if(data.size() >= data.find(key, data.find(key)+1)){
            throw std::invalid_argument("The data has two" + key + "keys.");
        }
}


void JSON::internalStringParse(std::string data, std::string key){
        std::pair<std::string,std::string>ret;
        if(data.find(key)<data.size())
        {
        this->keyTester(data,key);
        std::string str=data.substr(
        data.find(":\"",data.find(key))+2,
        (
        (data.find("\"",data.find(":\"",data.find(key))+3))-
        (data.find(":\"",data.find(key))+2)
        )
        );
        std::pair<std::string,std::string> ret=std::make_pair(key, str);
        adatok.insert(ret);
        }
}
void JSON::internalNumParse(std::string data, std::string key){
        std::pair<std::string,std::string>ret;
        if(data.find(key)<data.size())
        {
        this->keyTester(data,key);
        if(data.find(',',data.find(key))<data.find('}',data.find(key))){
            std::string str=data.substr(
            data.find(":", data.find(key))+1,
            data.find(',',data.find(key))-data.find(":",data.find(key))-1
	        );
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        std::pair<std::string,std::string> ret=std::make_pair(key, str);
        adatok.insert(ret);
        }

        else{
            std::string str=data.substr(
            data.find(":", data.find(key))+1,
            data.find('}',data.find(key))-data.find(":",data.find(key))-1
	        );
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        std::pair<std::string,std::string> ret=std::make_pair(key, str);
        adatok.insert(ret);
        }
        }
}

void JSON::internalParser(std::string data){
        // remove whitespaces and resize
        data.erase(remove_if(data.begin(), data.end(), isspace), data.end());
        this->internalStringParse(data,"name");
        this->internalNumParse(data,"health_points");
        this->internalNumParse(data,"damage\"");
        this->internalNumParse(data,"attack_cooldown");
        this->internalNumParse(data,"experience_per_level");
        this->internalNumParse(data,"health_point_bonus_per_level");
        this->internalNumParse(data, "damage_bonus_per_level");
        this->internalNumParse(data, "cooldown_multiplier_per_level");
        this->internalStringParse(data, "lore");
        this->internalStringParse(data, "race");
        this->internalStringParse(data, "additional_info");
};

std::map<std::string,std::string> JSON::parseString(std::string data){
        this->internalParser(data);
        return adatok;
}


std::map<std::string, std::string> JSON::parseFile(std::string fname){
        std::ifstream file;
        file.open(fname);
	    if(!file.is_open()){throw std::invalid_argument("The file " +fname+ " not exist");}
        std::string hero,
            line;
        while (getline(file,line))
        {
            hero.append(line);          
        }
        this->internalParser(hero);
        file.close();
        return adatok;
}



JSON JSON::parseFromFile(std::string fname){
    std::map<std::string,std::string> map;
    std::ifstream file;
    file.open(fname);
    if(!file.is_open()){throw JSON::ParseException("The file " +fname+ " not exist");}
            std::string data,
            line;
        while (getline(file,line))
        {
            data.append(line);          
        }
        try{
        // get name
        std::string hero=data.substr(
        data.find(":\"",data.find("hero"))+2,
        (
        (data.find("\"",data.find(":\"",data.find("hero"))+3))-
        (data.find(":\"",data.find("hero"))+2)
        )
        );
        std::string monsters=data.substr(
        data.find(":\"",data.find("monsters"))+2,
        (
        (data.find("\"",data.find(":\"",data.find("monsters"))+3))-
        (data.find(":\"",data.find("monsters"))+2)
        )
        );
        std::pair<std::string,std::string> nev=std::make_pair("hero", hero);
        map.insert(nev);
        std::pair<std::string,std::string> hape=std::make_pair("monsters", monsters);
        map.insert(hape);
        
        file.close();
        
        return JSON(map);
        }
        catch(std::exception& e){
            throw JSON::ParseException(e.what());
        }

};

unsigned int JSON::count(const std::string& data){
    return adatok.count(data);
};