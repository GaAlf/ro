#include "artificial_intelligencei.h"


ArtificialIntelligence::ArtificialIntelligence(Reversi *game)
{
    this->game = game;
    this->agent = 0;
    this->level = 2;
    this->myPiece = this->game->getTurn();
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

void ArtificialIntelligence::calculateBetterMove(int &i, int &j)
{
    this->switchHeuristcs();
    this->minMaxNLevel(i,j);
}

void ArtificialIntelligence::minMax2Levels(int &i, int &j)
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
    std::pair<int,int> betterMove(-1,-1);
    int h = -1;

    while(!markers.empty())
    {
        std::pair<int,int> move = markers.front();
        markers.pop_front();

        int localH = this->minMaxRecursive(move,1,h);
        if(betterMove.first == -1 || localH < h) //The root node is min.
        {
            h = localH;
            betterMove = move;
        }
    }

    i = betterMove.first;
    j = betterMove.second;
}


int ArtificialIntelligence::minMaxRecursive(std::pair<int,int> move, int level, int alfaBeta)
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

        int h = this->minMaxRecursive(move,level+1,localH);

        if(level % 2 == 0)// Node min
        {
            if(localH == -1 || h < localH)
                localH = h;

            if(alfaBeta != -1 && localH < alfaBeta)
            {
                localH = alfaBeta;
                break;
            }
        }
        else //Node max
        {
            if(localH == -1 || h > localH)
                localH = h;

            if(alfaBeta != -1 && localH > alfaBeta)
            {
                localH = alfaBeta;
                break;
            }
        }
    }

    this->game->undoLastMove();
    return localH;
}

void ArtificialIntelligence::switchHeuristcs()
{
    if(this->agent == -1)
    {
        int countMyCorners = 0;
        int countCorners = 0;

        for(int x=0; x<4; x++)
        {
            int tempX = (x/2 == 0) ? 0 : 7;
            int tempY = (x/2 == 1) ? 7 : 0;

            int piece = this->game->getPiece(tempX,tempY);
            if(piece == this->myPiece)
                countMyCorners++;

            if(piece == Reversi::BLACK || piece == Reversi::WHITE)
                countCorners++;

            if(this->game->getPiece(tempX,tempY) == Reversi::MARKER)
            {
                this->agent = 2;
                return;
            }
        }

        if( countCorners < 3 && countMyCorners < 3)
        {
            this->agent = 2; // agent to get corners.
            return;
        }

        int scoreDiff = this->game->getBlackScore() - this->game->getWhiteScore();
        if(this->myPiece == Reversi::BLACK)
        {
            if(scoreDiff > 0)
                this->agent = 1; // agent to get the biggest number of markers.
            else
                this->agent = 0; // agent to improve score.
        }
        else
        {
            if(scoreDiff < 0)
                this->agent = 1; // agent to get the biggest number of markers.
            else
                this->agent = 0; // agent to improve score.
        }
    }
}

int ArtificialIntelligence::heuristic()
{
    int h = 0;

    switch (this->agent) {
        case 1: // maximize the number of markers.
            h = 64 - this->game->getTotalMarkers();
            break;
        case 2: // try to aproach of corners.
        {
            std::deque< std::pair<int,int> > markers = this->game->findDequeOfMarkers();
            while(!markers.empty())
            {
                std::pair<int,int> move = markers.front();
                markers.pop_front();
                h += this->h2(move.first,move.second);
            }
            h = 1000000 - h; // the value of h must be positive.
            break;
        }
        default: //maximize your score.
        {
            if(this->myPiece == Reversi::BLACK)
                h = 64 - this->game->getBlackScore() + this->game->getWhiteScore();
            else
                h = 64 + this->game->getBlackScore() - this->game->getWhiteScore();
            break;
        }
    }

    return h;
}

//the least distance between corners.
//this function try to return the biggest value possible to pieces too close of corners.
int ArtificialIntelligence::h2(int i, int j)
{
    int h = 64;

    int distance_weight = 0;
    int weight = 1;

    for(int x=0; x<4; x++)
    {
        int tempX = (x/2 == 0) ? 0 : 7;
        int tempY = (x/2 == 1) ? 7 : 0;

        int tempXDiff = std::abs(tempX - i);
        int tempYDiff = std::abs(tempY - j);

        distance_weight = tempXDiff + tempYDiff;

        if(distance_weight < h)
            h = distance_weight;

        if(this->game->getPiece(tempX,tempY) == this->myPiece)
            weight += 100;
    }

    if(h == 0)
        h = 300;

    h = (14 - h)*weight;
    return h;
}
