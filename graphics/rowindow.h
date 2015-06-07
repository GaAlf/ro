#ifndef ROWINDOW_H
#define ROWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QImage>
#include <QString>
#include <iostream>
#include <QMessageBox>


#include "piece.h"
#include "../game_logic/reversi.h"
#include "../artificial_intelligence/artificial_intelligencei.h"


namespace Ui {
class ROWindow;
}

class ROWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ROWindow(QWidget *parent = 0);
    ~ROWindow();

    void initGame();
    void setPieceOnTable(QString piece, int x, int y);
    void updateTable();

    void mousePressEvent(QMouseEvent *event);

private slots:
    void playCPU();
    void restartGame();
    void skipTurn();

private:
    Ui::ROWindow *ui;
    Piece* tableOfPieces[8][8];
    Reversi* game;

    int calculatePixel(int x);
    void initTable();
    void playGame(int i, int j);
    void verifyEndGame();
};

#endif // ROWINDOW_H
