#pragma once
#ifndef JSON_H
#define JSON_H
#include <string>
#include<fstream>
#include"Hero.h"
#include <map>
#include <algorithm>

class Json
{
private:
        std::map<std::string,std::string> adatok;
        void internalParser(std::string data);
public:
        std::map<std::string,std::string> parseFile(std::string fname);
        std::map<std::string,std::string> parser(std::string data);
        Json();
        ~Json();
};
//std::istream& operator>>(std::istream&, Json& j);
#endif //JSON_H
