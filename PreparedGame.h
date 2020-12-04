#include <string>
#include "Game.h"
#include "JSON.h"


class PreparedGame:public Game{
    public:
        PreparedGame(std::string str_);
};