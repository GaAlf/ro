#ifndef REVERSI
#define REVERSI

class Reversi
{
public:
    Reversi();
    ~Reversi();

    enum PieceType{EMPTY, WHITE, BLACK, MARKER};

    int getPiece(int x,  int y);
    void initGame();
    void restartGame();
    int getWhiteScore();
    int getBlackScore();
    int getTurn();
    bool play(int i, int j);
    bool hasMarkers();
    int getTotalMarkers();

private:
    int table[8][8];
    int turn;
    int whiteScore;
    int blackScore;

    void changeTurn();
    bool findMatch(int incX, int incY, int i, int j);
    void changePieces(int incX, int incY, int i, int j);
    void transformPieces(int i, int j);
    bool isMarker(int i, int j);
    void calculateScores();
    void removeMarkers();
    void generateNewMarkers();
};

#endif // REVERSI

