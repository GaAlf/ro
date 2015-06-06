#include "rowindow.h"
#include "ui_rowindow.h"

ROWindow::ROWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ROWindow)
{
    ui->setupUi(this);
}

ROWindow::~ROWindow()
{
    delete ui;
}

void ROWindow::initGame()
{
    this->initTable();
    QGraphicsScene *scene = new QGraphicsScene();

    QString imageTableFile = "imgs/reversi_table.png";
    QImage imageTable(imageTableFile);
    if(imageTable.isNull())
    {
        std::cout << "Error: file " << imageTableFile.toStdString() << " not found." << std::endl;
        return;
    }

    QGraphicsPixmapItem *itemTable = new QGraphicsPixmapItem(QPixmap::fromImage(imageTable));
    scene->addItem(itemTable);
    ui->graphicsView->setScene(scene);

    setPieceOnTable("white",0,0);
    setPieceOnTable("black",0,1);
    setPieceOnTable("black",0,2);
    setPieceOnTable("black",0,2);
    setPieceOnTable("white",0,2);

    ui->graphicsView->show();


}

void ROWindow::initTable()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            this->tableOfPieces[i][j] = NULL;
        }
    }
}

void ROWindow::setPieceOnTable(QString pieceName, int x, int y)
{
    if(x < 0 || y < 0 || x >= 8 || y >= 8)
    {
        std::cout << "Error: index x:" << x << " or y:" << y << " out of bounding." << std::endl;
        return;
    }

    int x_pixel = calculatePixel(y);
    int y_pixel = calculatePixel(x);

    QGraphicsScene *scene = ui->graphicsView->scene();

    if(this->tableOfPieces[x][y] != NULL && this->tableOfPieces[x][y]->getType() != pieceName)
    {
        Piece *piece = this->tableOfPieces[x][y];
        this->tableOfPieces[x][y] = NULL;
        scene->removeItem(piece->getImage());
        delete piece;
    }

    this->tableOfPieces[x][y] = new Piece(pieceName,x_pixel,y_pixel);
    scene->addItem(this->tableOfPieces[x][y]->getImage());
}

int ROWindow::calculatePixel(int x)
{
    int x_pixel = 1 + x*50;
    return x_pixel;
}



