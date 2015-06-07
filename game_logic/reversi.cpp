#include "reversi.h"


Reversi::Reversi()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            this->table[i][j] = EMPTY;
        }
    }

}

Reversi::~Reversi(){}

int Reversi::getPiece(int x,  int y)
{
    return this->table[x][y];
}

void Reversi::initGame()
{
    this->table[3][3] = Reversi::WHITE;
    this->table[3][4] = Reversi::BLACK;
    this->table[4][3] = Reversi::BLACK;
    this->table[4][4] = Reversi::WHITE;

    this->turn = Reversi::BLACK;
    this->whiteScore = 2;
    this->blackScore = 2;

    this->generateNewMarkers();
}

void Reversi::restartGame()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            this->table[i][j] = EMPTY;
        }
    }

    this->initGame();
}

int Reversi::getWhiteScore()
{
    return this->whiteScore;
}

int Reversi::getBlackScore()
{
    return this->blackScore;
}

int Reversi::getTurn()
{
    return this->turn;
}

void Reversi::changeTurn()
{
    if(this->turn == Reversi::BLACK)
        this->turn = Reversi::WHITE;
    else{
        this->turn = Reversi::BLACK;
    }
}

void Reversi::transformPieces(int i, int j)
{
    //TODO caculate the pieces that will change.
}

void Reversi::calculateScores()
{
    this->whiteScore = 0;
    this->blackScore = 0;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(this->table[i][j] == Reversi::BLACK)
            {
                this->blackScore++;
            }
            else
            {
                if(this->table[i][j] == Reversi::WHITE)
                {
                    this->whiteScore++;
                }
            }
        }
    }
}

void Reversi::removeMarkers()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(this->table[i][j] == Reversi::MARKER)
            {
                this->table[i][j] = Reversi::EMPTY;
            }
        }
    }
}

void Reversi::generateNewMarkers()
{
    this->removeMarkers();
    //TODO calculateNewPossible markers.
}

bool Reversi::play(int i, int j)
{
    if(this->table[i][j] != Reversi::MARKER)
        return false;

    this->table[i][j] = this->turn;
    this->transformPieces(i,j);

    this->calculateScores();

    this->changeTurn();
    this->generateNewMarkers();

    return true;
}

