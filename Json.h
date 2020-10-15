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
        static void keyTester(std::string data, std::string fname);
public:
        Json();
        ~Json();
        std::map<std::string,std::string> parseFile(std::string fname);
        std::map<std::string,std::string> parseString(std::string data);
        std::map<std::string,std::string> getAdatok();
        friend std::istream& operator>>(std::istream&, Json& j);
};

#endif //JSON_H
