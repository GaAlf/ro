#ifndef PIECE
#define PIECE

#include <QString>
#include <QGraphicsPixmapItem>
#include <iostream>

class Piece
{

public:
    Piece(QString piece, int x_pixel, int y_pixel);
    ~Piece();

    QString getType();
    QGraphicsPixmapItem* getImage();

private:
    QString type;
    QGraphicsPixmapItem *image;

    QGraphicsPixmapItem* loadPiece(QString piece, int x_pixel, int y_pixel);

};

#endif // PIECE
