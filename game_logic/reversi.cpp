#include "reversi.h"

Reversi::Reversi()
{
    memset( table, EMPTY, BOARD_SIZE*BOARD_SIZE*sizeof(table[0][0]) );
}

Reversi::~Reversi() { ; }


void Reversi::initGame()
{
    this->table[3][3] = Reversi::WHITE;
    this->table[3][4] = Reversi::BLACK;
    this->table[4][3] = Reversi::BLACK;
    this->table[4][4] = Reversi::WHITE;

    this->turn = Reversi::BLACK;
    this->score[BLACK] = 2;
    this->score[WHITE] = 2;
    this->score[MARKER] = 0;

    this->generateNewMarkers();
}

void Reversi::restartGame()
{
    memset( table, EMPTY, BOARD_SIZE*BOARD_SIZE*sizeof(table[0][0]) );
    this->initGame();
}

int Reversi::getWhiteScore() { return this->score[WHITE]; }
int Reversi::getBlackScore() { return this->score[BLACK]; }
int Reversi::getPiece(int x,  int y) { return this->table[x][y]; }
int Reversi::getTurn() { return this->turn; }
int Reversi::getTotalMarkers() { return this->score[MARKER]; }
bool Reversi::hasMarkers() { return ( this->score[MARKER] > 0 ); }

void Reversi::changeTurn()
{
    this->turn = this->turn == Reversi::WHITE ? Reversi::BLACK : Reversi::WHITE;
    this->generateNewMarkers();
}

bool Reversi::scout(int incX, int incY, int i, int j)
{
    if(incX == 0 && incY == 0) { return false; }

    int x,y;
    x = i + incX;
    y = j + incY;

    int search = this->turn != Reversi::BLACK ? Reversi::BLACK : Reversi::WHITE;

    if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) { return false; }

    if(this->table[x][y] == search) { x += incX; y += incY; }
    else { return false; }

    while(x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE)
    {
        if(this->table[x][y] == search)
        {
            x += incX;
            y += incY;
        }
        else
        {
            if(this->table[x][y] == this->turn) { return true; }
            else { return false; }
        }
    }

    return false;
}

void Reversi::flipPieces(int incX, int incY, int i, int j)
{
    if(incX == 0 && incY == 0) { return; }

    int x,y;
    x = i + incX;
    y = j + incY;

    PieceType ally = this->turn;
    PieceType enemy = this->turn == WHITE ? BLACK : WHITE;

    while(x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE)
    {
        if(this->table[x][y] == ally) { return; }
        if(this->table[x][y] == enemy) { this->score[enemy]--; }

        this->table[x][y] = this->turn;
        this->score[ally]++;
        x += incX;
        y += incY;

    }
}

void Reversi::transformPieces(int i, int j)
{
    score[MARKER]--;
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            if( scout(x,y,i,j) ) flipPieces(x,y,i,j);
        }
    }
}

bool Reversi::isMarker(int i, int j)
{
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            if( scout(x,y,i,j) ) return true;
        }
    }
    return false;
}

void Reversi::generateNewMarkers()
{
    for(int i=0; i < BOARD_SIZE; i++) {
        for(int j=0; j < BOARD_SIZE; j++) {
            if(this->table[i][j] == Reversi::MARKER && !this->isMarker(i,j)) { this->table[i][j] = EMPTY; this->score[MARKER]--; }
            else if(this->table[i][j] == Reversi::EMPTY && this->isMarker(i,j)) { this->table[i][j] = MARKER; this->score[MARKER]++; }
        }
    }
}

bool Reversi::play(int i, int j)
{
    if(this->table[i][j] != Reversi::MARKER)
        return false;

    this->table[i][j] = this->turn;
    this->score[this->turn]++;
    this->transformPieces(i,j);

    this->changeTurn();

    return true;
}

bool Reversi::endGame()
{
    int totalMarkers = this->score[MARKER];
    if(totalMarkers == 0)
    {
        this->changeTurn();
        totalMarkers = this->score[MARKER];
        this->changeTurn();
        if(totalMarkers == 0)
        {
            return true;
        }
    }
    return false;
}
