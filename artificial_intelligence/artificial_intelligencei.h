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
    void minMax(int &i, int &j);

    void setAgent(int agent);
    void setLevel(int level);

private:
    Reversi *game;
    int agent;
    int level;

    int h0(int i, int j);
    int h1(int i, int j);
    int h2(int i, int j);
    int h3(int i, int j);
};

#endif // ARTIFICIALINTELLIGENCE

