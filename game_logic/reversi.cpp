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

    this->generateNewMarkers();
}

bool Reversi::findMatch(int incX, int incY, int i, int j)
{
    int x,y;
    x = i + incX;
    y = j + incY;

    if(incX == 0 && incY == 0)
    {
        return false;
    }

    int search = Reversi::BLACK;
    if(this->turn == Reversi::BLACK)
        search = Reversi::WHITE;

    if(x >= 0 && y >= 0 && x < 8 && y < 8)
    {
        if(this->table[x][y] == search)
        {
            x += incX;
            y += incY;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    while(x >= 0 && y >= 0 && x < 8 && y < 8)
    {
        if(this->table[x][y] == search)
        {
            x += incX;
            y += incY;
        }
        else
        {
            if(this->table[x][y] == this->turn)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

void Reversi::changePieces(int incX, int incY, int i, int j)
{
     int x,y;
     x = i + incX;
     y = j + incY;

     if(incX == 0 && incY == 0)
     {
         return;
     }

     while(x >= 0 && y >= 0 && x < 8 && y < 8)
     {

         if(this->table[x][y] == this->turn)
             break;

         this->table[x][y] = this->turn;
         x += incX;
         y += incY;

     }
}

void Reversi::transformPieces(int i, int j)
{
    bool match = false;
    for(int x=-1; x<=1; x++)
    {
        for(int y=-1; y<=1; y++)
        {
            if(x==0 && y==0)
                continue;

            match = findMatch(x,y,i,j);
            if(match)
            {
                changePieces(x,y,i,j);
            }
        }
    }
}

bool Reversi::isMarker(int i, int j)
{
    bool match = false;
    for(int x=-1; x<=1; x++)
    {
        for(int y=-1; y<=1; y++)
        {
            if(x==0 && y==0)
                continue;

            match = findMatch(x,y,i,j);
            if(match)
            {
                return match;
            }
        }
    }
    return match;
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

int Reversi::getTotalMarkers()
{
    int total = 0;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(this->table[i][j] == Reversi::MARKER)
            {
                total++;
            }
        }
    }

    return total;
}

bool Reversi::hasMarkers()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(this->table[i][j] == Reversi::MARKER)
            {
                return true;
            }
        }
    }

    return false;
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
    bool match = false;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(this->table[i][j] == Reversi::MARKER || this->table[i][j] == Reversi::EMPTY)
            {
                match = this->isMarker(i,j);
                if(match)
                {
                    this->table[i][j] = Reversi::MARKER;
                }
                else
                {
                    this->table[i][j] = Reversi::EMPTY;
                }
            }
        }
    }
}

bool Reversi::play(int i, int j)
{
    if(this->table[i][j] != Reversi::MARKER)
        return false;

    this->table[i][j] = this->turn;
    this->transformPieces(i,j);

    this->calculateScores();

    this->changeTurn();

    return true;
}

bool Reversi::endGame()
{
    int totalMarkers = this->getTotalMarkers();
    if(totalMarkers == 0)
    {
        this->changeTurn();
        totalMarkers = this->getTotalMarkers();
        this->changeTurn();
        if(totalMarkers == 0)
        {
            return true;
        }
    }
    return false;
}

int Reversi::gameWinner()
{
    if(this->whiteScore > this->blackScore)
    {
        return Reversi::WHITE;
    }

    if(this->whiteScore < this->blackScore)
    {
        return Reversi::BLACK;
    }

    return Reversi::EMPTY;
}

