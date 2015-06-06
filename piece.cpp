#include "piece.h"

Piece::Piece(QString piece, int x_pixel, int y_pixel)
{
    this->type = piece;
    this->image = loadPiece(piece,x_pixel,y_pixel);
}

Piece::~Piece()
{
    delete image;
}

QString Piece::getType()
{
    return this->type;
}

QGraphicsPixmapItem* Piece::getImage()
{
    return this->image;
}

QGraphicsPixmapItem* Piece::loadPiece(QString piece, int x_pixel, int y_pixel)
{
    if(piece != "white" && piece != "black")
    {
        std::cout << "Error: wrong name of piece '" << piece.toStdString() << "', please try 'white' or 'black'." << std::endl;
        return NULL;
    }

    QString imagePieceFile = "imgs/"+piece+"_piece.png";

    QImage imagePiece(imagePieceFile);
    if(imagePiece.isNull())
    {
        std::cout << "Error: file " << imagePieceFile.toStdString() << " not found." << std::endl;
        return NULL;
    }

    QGraphicsPixmapItem *itemPiece = new QGraphicsPixmapItem(QPixmap::fromImage(imagePiece));

    itemPiece->setPos(x_pixel,y_pixel);
    return itemPiece;
}
