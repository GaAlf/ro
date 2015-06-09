#include "artificial_intelligencei.h"


ArtificialIntelligence::ArtificialIntelligence()
{

}

ArtificialIntelligence::~ArtificialIntelligence()
{

}

//template <typename T>
//T random_element(T begin, T end) {
//    const unsigned long n = std::distance(begin,end);
//    const unsigned long divisor = (5 + 1)/n;

//    unsigned long k;
//    do { k = std::rand()/divisor; } while(k>=n);
//    return std::advance(begin,k);
//}

void ArtificialIntelligence::calculateBetterMove(int &i, int &j, Reversi *game)
{
    int limit = game->BOARD_SIZE-1;
    if(game->getPiece(0,0) == Reversi::MARKER) { i = j = 0; return; }
    else if(game->getPiece(0,limit) == Reversi::MARKER) { i = 0; j = limit; return; }
    else if(game->getPiece(limit,0) == Reversi::MARKER) { j = 0; i = limit; return; }
    else if(game->getPiece(limit,limit) == Reversi::MARKER) { i = j = limit; return; }
    else if(!game->findMarkers().empty()) {
//        std::vector< std::pair<int,int> >::iterator it = game->findMarkers().begin();
        std::pair<int,int> pair = *game->findMarkers().begin();
//        std::advance(it,)
        i=pair.first; j=pair.second;
    }
}
