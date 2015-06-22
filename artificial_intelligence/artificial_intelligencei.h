#ifndef ARTIFICIALINTELLIGENCE
#define ARTIFICIALINTELLIGENCE

#include <cmath>
#include "../game_logic/reversi.h"

class ArtificialIntelligence
{
public:
    ArtificialIntelligence(Reversi *game);
    ~ArtificialIntelligence();

    int heuristic();
    void calculateBetterMove(int &i, int &j);
    void minMax2Levels(int &i, int &j);
    void minMaxNLevel(int &i, int &j);

    void setAgent(int agent);
    void setLevel(int level);

private:
    Reversi *game;
    int myPiece;
    int agent;
    int level;

    int minMaxRecursive(std::pair<int,int> move, int level, int alfaBeta);
    void switchHeuristcs();
    int h2(int i, int j);
};

#endif // ARTIFICIALINTELLIGENCE

