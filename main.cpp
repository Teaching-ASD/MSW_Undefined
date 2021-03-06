#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
#include<iostream>
#include<fstream>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include "PreparedGame.h"
#include "Renderer.h"
#include "TextRenderer.h"
#include "HeroTextRenderer.h"
#include "ObserverTextRenderer.h"
#include "SVGRenderer.h"
#include "ObserverSVGRenderer.h"
#include "CharacterSVGRenderer.h"


const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided or the second argument should be Map.txt ." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." },
    { 5 , "The map file not exist." }
};

void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    if (argc != 3 && argc != 2 ) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);
    try{
        std::string str = argv[1];
        PreparedGame pgame(str);
        std::ofstream ofstream_ = std::ofstream("log.txt");
        pgame.registerRenderer(new HeroTextRenderer());
        pgame.registerRenderer(new ObserverTextRenderer());
        pgame.registerRenderer(new ObserverTextRenderer(ofstream_));
        pgame.registerRenderer(new ObserverSVGRenderer("file.svg"));
        pgame.registerRenderer(new CharacterSVGRenderer("file1.svg"));

        pgame.run();
    }catch(const JSON::ParseException& e)
    {
        bad_exit(4);
    }
    return 0;
}

