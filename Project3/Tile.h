#include <iostream>
#include <string>

using namespace std;

class Tile{
public:
    Tile(string LettersToTile) : TileLetters(LettersToTile), Visited(false){};
    ~Tile(void){};
    string getTile(){return TileLetters;}
    bool getVisited(){return Visited;}
    void setUsed(){Visited = true;}
    void ClearUsed(){Visited = false;}
private:
    string TileLetters;
    bool Visited;
};