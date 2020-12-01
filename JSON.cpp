#include "JSON.h"

JSON::JSON(){}


JSON::~JSON(){
    this->adatok.clear();
}

void JSON::keyTester(std::string data, std::string key){
        //check duplicated keys
        if(data.size() >= data.find(key, data.find(key)+1)){
            throw JSON::ParseException("The data has two" + key + "keys.");
        }
}


void JSON::internalStringParse(std::string data, std::string key){
        if(data.find(key)<data.size()){
            this->keyTester(data,key);
            std::string str=data.substr(
            data.find("\"",data.find(":",data.find(key)))+1,
                (
                    (data.find("\"",data.find("\"", data.find(":",data.find(key)))+1))-
                    (data.find("\"",data.find(":",data.find(key)))+1)
                )
            );
            std::pair<std::string,std::variant<std::string, int, double>> ret=std::make_pair(key, str);
            adatok.insert(ret);
        }
}

void JSON::internalStringParseMonster(std::string data, std::string key){
        if(data.find(key)<data.size()){
            this->keyTester(data,key);
            std::string str=data.substr(
            data.find("\"",data.find(":",data.find(key))),
            data.find("]")-(data.find("\"",data.find(":",data.find(key)))) );
            std::pair<std::string,std::variant<std::string, int, double>> ret=std::make_pair(key, str);
            adatok.insert(ret);
        }
}
void JSON::internalNumParse(std::string data, std::string key){
        //remove whitespaces
        data.erase(remove_if(data.begin(), data.end(), isspace), data.end());
        //
        if(data.find(key)<data.size()){
        this->keyTester(data,key);
        if(data.find(',',data.find(key))<data.find('}',data.find(key))){
             std::string str=data.substr(
                data.find(":", data.find(key))+1,
                data.find(',',data.find(key))-data.find(":",data.find(key))-1
	        );
            key.erase(remove(key.begin(), key.end(), '\"'), key.end());
            if(str.find('.')!=std::string::npos){
                std::pair<std::string, std::variant<std::string, int, double>> ret=std::make_pair(key, stod(str));
            adatok.insert(ret);
            }
            else {
                std::pair<std::string, std::variant<std::string, int, double>> ret=std::make_pair(key, stoi(str));
                adatok.insert(ret);
            }
        }
        else{
            std::string str=data.substr(
                data.find(":", data.find(key))+1,
                data.find('}',data.find(key))-data.find(":",data.find(key))-1
	        );
            key.erase(remove(key.begin(), key.end(), '\"'), key.end());
            if(std::string::npos != str.find('.')){
                std::pair<std::string, std::variant<std::string, int, double>> ret=std::make_pair(key, stod(str));
            adatok.insert(ret);
            }
            else {
                std::pair<std::string, std::variant<std::string, int, double>> ret=std::make_pair(key, stoi(str));
                adatok.insert(ret);
            }
        }
        }
}

void JSON::internalParser(std::string data){
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
        this->internalStringParse(data,"hero");
        this->internalStringParseMonster(data,"monsters");
};

void JSON::parseString(std::string data){
        this->internalParser(data);
}


void JSON::parseFile(std::string fname){
        this->internalParser(this->readFile(fname));
}

std::string JSON::readFile(std::string fname){
        std::ifstream file;
        file.open(fname);
	    if(!file.is_open()){throw JSON::ParseException("The file " +fname+ " not exist");}
        std::string adatok,
            line;
        while (getline(file,line))
        {
            adatok.append(line);          
        }
        file.close();
        return adatok;
}

JSON JSON::parseFromFile(char* fname){
        JSON object;
        object.internalParser(object.readFile(fname));
        return object;
}

unsigned int JSON::count(const std::string& data){
    return adatok.count(data);
}

std::istream& operator>>(std::istream& in, JSON& j){
    std::string temp;
    char a;
    while(in.get(a) && a!='\n')
    {
        temp.push_back(a);
    }
    j.internalParser(temp);
    return in;
}