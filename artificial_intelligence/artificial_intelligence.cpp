#include "artificial_intelligencei.h"


ArtificialIntelligence::ArtificialIntelligence()
{

}

ArtificialIntelligence::~ArtificialIntelligence()
{

}

void ArtificialIntelligence::calculateBetterMove(int &i, int &j, Reversi *game)
{
    int limit = game->BOARD_SIZE-1;
    if(game->getPiece(0,0) == Reversi::MARKER) { i = j = 0; return; }
    else if(game->getPiece(0,limit) == Reversi::MARKER) { i = 0; j = limit; return; }
    else if(game->getPiece(limit,0) == Reversi::MARKER) { j = 0; i = limit; return; }
    else if(game->getPiece(limit,limit) == Reversi::MARKER) { i = j = limit; return; }
}

