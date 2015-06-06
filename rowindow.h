#ifndef ROWINDOW_H
#define ROWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QImage>
#include <QString>
#include <QFileDialog>
#include <iostream>


#include "piece.h"


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

private:
    Ui::ROWindow *ui;
    Piece* tableOfPieces[8][8];

    int calculatePixel(int x);
    void initTable();
};

#endif // ROWINDOW_H
