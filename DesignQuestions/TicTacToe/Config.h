#include<unordered_map>
#include "Enums.h"

using namespace std;

class Config {
public:
    static const int MAXBOARDSIZE;
    static const int MAXPLAYERS;
    static const unordered_map<int, Symbol> playerIdToSymbol;
};

const int Config::MAXBOARDSIZE = 10;
const int Config::MAXPLAYERS = 5;

const unordered_map<int, Symbol> Config::playerIdToSymbol = {
    {0, Symbol::X},
    {1, Symbol::O},
    {2, Symbol::M},
    {3, Symbol::N},
    {4, Symbol::P}
};