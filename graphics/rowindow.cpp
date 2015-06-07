#include "rowindow.h"
#include "ui_rowindow.h"

ROWindow::ROWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ROWindow)
{
    ui->setupUi(this);
    this->game = new Reversi();
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

    ui->graphicsView->show();

    this->game->initGame();
    this->updateTable();
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

    QGraphicsScene *scene = ui->graphicsView->scene();

    if(pieceName == "empty")
    {
        Piece *piece = this->tableOfPieces[x][y];
        if(piece == NULL)
            return;

        this->tableOfPieces[x][y] = NULL;
        scene->removeItem(piece->getImage());
        delete piece;
        return;
    }

    int x_pixel = calculatePixel(y);
    int y_pixel = calculatePixel(x);

    if(this->tableOfPieces[x][y] != NULL)
    {
        Piece *piece = this->tableOfPieces[x][y];
        if(piece->getType() == pieceName)
            return;

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

void ROWindow::updateTable()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            int pieceType = game->getPiece(i,j);
            switch(pieceType)
            {
                case Reversi::EMPTY:
                    this->setPieceOnTable("empty",i,j);
                    break;
                case Reversi::BLACK:
                    this->setPieceOnTable("black",i,j);
                    break;
                case Reversi::WHITE:
                    this->setPieceOnTable("white",i,j);
                    break;
                case Reversi::MARKER:
                    this->setPieceOnTable("marker",i,j);
                    break;
            }
        }
    }
}

void ROWindow::mousePressEvent(QMouseEvent *event)
{
    int x = QCursor::pos().x();
    x -= 12;
    x -= this->pos().x();
    x -= ui->frame->pos().x();
    x -= ui->graphicsView->pos().x();

    int y = QCursor::pos().y();
    y -= 58;
    y -= this->pos().y();
    y -= ui->frame->pos().y();
    y -= ui->graphicsView->pos().y();

    if( x < 0 || y < 0 || x >= ui->graphicsView->width() || y >= ui->graphicsView->height())
        return;

    int i=0,j=0;
    i = y/50;
    j = x/50;

    bool validMove = this->game->play(i,j);
    if(validMove){
        this->updateTable();
        QChar line = 'A'+i;
        QChar column = '1'+j;
        QString pos = " "+(QString)line+""+(QString)column;
        ui->statusBar->showMessage("Move on "+pos, 5000);
    }
    else{
        ui->statusBar->showMessage("Invalid move!", 5000);
    }
}

