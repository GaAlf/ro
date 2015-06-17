#ifndef ARTIFICIALINTELLIGENCE
#define ARTIFICIALINTELLIGENCE

#include <cmath>
#include "../game_logic/reversi.h"

class ArtificialIntelligence
{
public:
    ArtificialIntelligence();
    ~ArtificialIntelligence();

    static int heuristic(Reversi *game, int level, int i, int j);
    static void calculateBetterMove(int &i, int &j, Reversi *game);

private:
    static int h0(Reversi *game, int i, int j);
    static int h1(Reversi *game, int i, int j);
    static int h2(Reversi *game, int i, int j);
    static int h3(Reversi *game, int i, int j);
};

#endif // ARTIFICIALINTELLIGENCE

