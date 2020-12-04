#include <string>
#include "Game.h"
#include "JSON.h"
#include "MarkedMap.h"

class PreparedGame:public Game{
    public:
        explicit PreparedGame(std::string str_);
        void run();
};