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

int ArtificialIntelligence::heuristic(Reversi *game, int level, int i, int j)
{
    int h = 0;
    switch (level) {
    case 1:
        h = ArtificialIntelligence::h1(game,i,j);
        break;
    case 2:
        h = ArtificialIntelligence::h2(game,i,j);
        break;
    default:
        h = ArtificialIntelligence::h0(game,i,j);
        break;
    }

    return h;
}

//The bigest score in one move.
int ArtificialIntelligence::h0(Reversi *game, int i, int j)
{
    int h = 64;
    int old_score = 0;
    if(game->getTurn() == Reversi::BLACK)
        old_score = game->getBlackScore();
    else
        old_score = game->getWhiteScore();

    game->play(i,j);

    int new_score = 0;
    if(game->getTurn() == Reversi::WHITE)
        new_score = game->getBlackScore();
    else
        new_score = game->getWhiteScore();

    game->undoLastMove();

    int move_score = new_score - old_score;

    h -= move_score;

    return h;
}

//The least number of markers.
int ArtificialIntelligence::h1(Reversi *game, int i, int j)
{
    int h = 0;

    game->play(i,j);

    h = game->getTotalMarkers();

    game->undoLastMove();

    return h;
}

//the least distance between edges.
int ArtificialIntelligence::h2(Reversi *game, int i, int j)
{
    int h = 64;

    int distance_weight = 0;

    for(int x=0; x<4; x++)
    {
        int tempX = (x/2 == 0) ? 0 : 7;
        int tempY = (x/2 == 1) ? 7 : 0;

        if(!game->isPlayableAt(tempX,tempY))
            continue;

        tempX = std::abs(tempX - i);
        tempY = std::abs(tempY - j);

        distance_weight = tempX + tempY;

        if(distance_weight < h)
            h = distance_weight;

        if(h == 1 || (tempX == 1 && tempY == 1))
        {
            h += 100;
            break;
        }
    }

    return h;
}

int ArtificialIntelligence::h3(Reversi *game, int i, int j)
{
    int h = 0;

    //H2
    int h2 = ArtificialIntelligence::h2(game,i,j);

    if(h2 == 0)
        return h2;

    //H1
    int h1 = 0;
    //H0
    int h0 = 64;

    int old_score = 0;
    if(game->getTurn() == Reversi::BLACK)
        old_score = game->getBlackScore();
    else
        old_score = game->getWhiteScore();

    game->play(i,j);

    int new_score = 0;
    if(game->getTurn() == Reversi::WHITE)
        new_score = game->getBlackScore();
    else
        new_score = game->getWhiteScore();

    h1 = game->getTotalMarkers();

    game->undoLastMove();

    int move_score = new_score - old_score;

    h0 -= move_score;

    //H3
    h = h0 + h1 + h2;

    return h;
}
