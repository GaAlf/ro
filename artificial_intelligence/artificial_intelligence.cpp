#include "artificial_intelligencei.h"


ArtificialIntelligence::ArtificialIntelligence(Reversi *game)
{
    this->game = game;
    this->agent = 0;
    this->level = 2;
}

ArtificialIntelligence::~ArtificialIntelligence()
{
    this->game = NULL;
}

void ArtificialIntelligence::setAgent(int agent)
{
    if(agent >= -1 && agent < 4)
        this->agent = agent;
    else
        this->agent = 0;
}

void ArtificialIntelligence::setLevel(int level)
{
    if(level > 0 && level < 100)
        this->level = level;
    else
        this->level = 1;
}

//template <typename T>
//T random_element(T begin, T end) {
//    const unsigned long n = std::distance(begin,end);
//    const unsigned long divisor = (5 + 1)/n;

//    unsigned long k;
//    do { k = std::rand()/divisor; } while(k>=n);
//    return std::advance(begin,k);
//}

void ArtificialIntelligence::calculateBetterMove(int &i, int &j)
{
    /*int limit = game->BOARD_SIZE-1;
    if(game->getPiece(0,0) == Reversi::MARKER) { i = j = 0; return; }
    else if(game->getPiece(0,limit) == Reversi::MARKER) { i = 0; j = limit; return; }
    else if(game->getPiece(limit,0) == Reversi::MARKER) { j = 0; i = limit; return; }
    else if(game->getPiece(limit,limit) == Reversi::MARKER) { i = j = limit; return; }
    else if(!game->findMarkers().empty()) {
//        std::vector< std::pair<int,int> >::iterator it = game->findMarkers().begin();
        std::pair<int,int> pair = *game->findMarkers().begin();
//        std::advance(it,)
        i=pair.first; j=pair.second;
    }*/

    this->minMaxNLevel(i,j);
}

void ArtificialIntelligence::minMax(int &i, int &j)
{
    std::deque< std::pair<int,int> > markers = this->game->findDequeOfMarkers();

    std::pair< std::pair<int,int>, int> betterMove(std::pair<int,int>(-1,-1),-1);

    while(!markers.empty())
    {
        std::pair<int,int> move = markers.front();
        markers.pop_front();

        this->game->play(move.first, move.second);

        std::deque< std::pair<int,int> > markersLevel2 = this->game->findDequeOfMarkers();
        std::pair< std::pair<int,int>, int> worstMove(std::pair<int,int>(-1,-1),-1);

        while(!markersLevel2.empty())
        {
            std::pair<int,int> move2 = markersLevel2.front();
            markersLevel2.pop_front();

            this->game->play(move2.first, move2.second);

            int h = this->heuristic();
            this->game->undoLastMove();

            if(worstMove.second < h)
            {
                worstMove.first = move2;
                worstMove.second = h;
            }


        }

        this->game->undoLastMove();

        if(betterMove.second == -1 || betterMove.second > worstMove.second)
        {
            betterMove.first = move;
            betterMove.second = worstMove.second;
        }

    }

    i = betterMove.first.first;
    j = betterMove.first.second;
}


void ArtificialIntelligence::minMaxNLevel(int &i, int &j)
{
    std::deque< std::pair<int,int> > markers = this->game->findDequeOfMarkers();
    int h = 0;
    std::pair<int,int> betterMove(-1,-1);

    while(!markers.empty())
    {
        std::pair<int,int> move = markers.front();
        markers.pop_front();

        int localH = this->minMaxRecursive(move,1);
        if(betterMove.first == -1 || localH < h)
        {
            h = localH;
            betterMove = move;
        }
    }

    i = betterMove.first;
    j = betterMove.second;
}


int ArtificialIntelligence::minMaxRecursive(std::pair<int,int> move, int level)
{
    this->game->play(move.first,move.second);

    if(level == this->level) // The end of recursivity
    {
        int h = this->heuristic();
        this->game->undoLastMove();
        return h;
    }

    if(this->game->getTotalMarkers() == 0) // case the current player can't play.
    {
        this->game->changeTurn();
        level++;
        if(level == this->level) // The end of recursivity
        {
            int h = this->heuristic();
            this->game->undoLastMove();
            return h;
        }
    }

    if(this->game->getTotalMarkers() == 0) // case the game end;
    {
        int h = this->heuristic();
        this->game->undoLastMove();
        return h;
    }

    std::deque< std::pair<int,int> > markers = this->game->findDequeOfMarkers();
    int localH = -1; //this value is impossible to heuristic to return

    while(!markers.empty())
    {
        std::pair<int,int> move = markers.front();
        markers.pop_front();

        int h = this->minMaxRecursive(move,level+1);

        if(level % 2 == 0)// Node min
        {
            if(localH == -1 || h < localH)
                localH = h;
        }
        else //Node max
        {
            if(localH == -1 || h > localH)
                localH = h;
        }
    }

    this->game->undoLastMove();
    return localH;
}

int ArtificialIntelligence::heuristic()
{
    int h = 0;

    std::deque< std::pair<int,int> > markers = this->game->findDequeOfMarkers();

    while(!markers.empty())
    {
        std::pair<int,int> move = markers.front();
        markers.pop_front();

        switch (this->agent) {
        case 1:
            h += this->h1(move.first,move.second);
            break;
        case 2:
            h += this->h2(move.first,move.second);
            break;
        case 3:
            h += this->h3(move.first,move.second);
            break;
        default:
            h += this->h0(move.first,move.second);
            break;
        }

    }

    return h;
}

//The bigest score in one move.
int ArtificialIntelligence::h0(int i, int j)
{
    int h = 64;
    int old_score = 0;
    if(this->game->getTurn() == Reversi::BLACK)
        old_score = this->game->getBlackScore();
    else
        old_score = this->game->getWhiteScore();

    this->game->play(i,j);

    int new_score = 0;
    if(this->game->getTurn() == Reversi::WHITE)
        new_score = this->game->getBlackScore();
    else
        new_score = this->game->getWhiteScore();

    this->game->undoLastMove();

    int move_score = new_score - old_score;

    h -= move_score;

    return h;
}

//The least number of markers.
int ArtificialIntelligence::h1(int i, int j)
{
    int h = 0;

    this->game->play(i,j);

    h = this->game->getTotalMarkers();

    this->game->undoLastMove();

    return h;
}

//the least distance between corners.
int ArtificialIntelligence::h2(int i, int j)
{
    int h = 64;

    int distance_weight = 0;

    for(int x=0; x<4; x++)
    {
        int tempX = (x/2 == 0) ? 0 : 7;
        int tempY = (x/2 == 1) ? 7 : 0;

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

int ArtificialIntelligence::h3(int i, int j)
{
    int h = 0;

    //H2
    int h2 = this->h2(i,j);

    if(h2 == 0)
        return h2;

    //H1
    int h1 = 0;
    //H0
    int h0 = 64;

    int old_score = 0;
    if(this->game->getTurn() == Reversi::BLACK)
        old_score = this->game->getBlackScore();
    else
        old_score = this->game->getWhiteScore();

    this->game->play(i,j);

    int new_score = 0;
    if(this->game->getTurn() == Reversi::WHITE)
        new_score = this->game->getBlackScore();
    else
        new_score = this->game->getWhiteScore();

    h1 = this->game->getTotalMarkers();

    this->game->undoLastMove();

    int move_score = new_score - old_score;

    h0 -= move_score;

    //H3
    h = h0 + h1 + h2;

    return h;
}
