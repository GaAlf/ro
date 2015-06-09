#ifndef REVERSI
#define REVERSI

#include <cstring>
#include <map>

class Reversi
{
public:
    Reversi();
    ~Reversi();

    static const int BOARD_SIZE = 8;
    enum PieceType{EMPTY, WHITE, BLACK, MARKER};

    int getPiece(int x,  int y);
    void initGame();
    void restartGame();
    int getWhiteScore();
    int getBlackScore();
    int getTurn();
    void changeTurn();
    bool play(int i, int j);
    bool hasMarkers();
    int getTotalMarkers();
    bool endGame();

private:
    int table[BOARD_SIZE][BOARD_SIZE];
    PieceType turn;
    std::map<PieceType,int> score;
    int markers;

    bool scout(int incX, int incY, int i, int j);
    void flipPieces(int incX, int incY, int i, int j);
    void transformPieces(int i, int j);
    bool isMarker(int i, int j);
    void generateNewMarkers();
};

#endif // REVERSI

