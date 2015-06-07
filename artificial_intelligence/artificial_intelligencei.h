#ifndef ARTIFICIALINTELLIGENCE
#define ARTIFICIALINTELLIGENCE

#include "../game_logic/reversi.h"

class ArtificialIntelligence
{
public:
    ArtificialIntelligence();
    ~ArtificialIntelligence();

    static void calculateBetterMove(int &i, int &j, Reversi *game);

private:

};

#endif // ARTIFICIALINTELLIGENCE

