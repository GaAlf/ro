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
    bool play(int i, int j);

private:
    int table[8][8];
    int turn;
    int whiteScore;
    int blackScore;

    void changeTurn();
    void transformPieces(int i, int j);
    void calculateScores();
    void removeMarkers();
    void generateNewMarkers();
};

#endif // REVERSI

