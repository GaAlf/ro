#include "rowindow.h"
#include "ui_rowindow.h"

ROWindow::ROWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ROWindow)
{
    ui->setupUi(this);
    this->game = new Reversi();

    ui->lineEdit_playAt->setMaxLength(2);
    ui->lineEdit_playAt->setInputMask(">AD");

    connect(ui->restartButton, SIGNAL(released()), this, SLOT(restartGame()));
    connect(ui->playCPUButton, SIGNAL(released()), this, SLOT(playCPU()));
    connect(ui->skipTurnButton, SIGNAL(released()), this, SLOT(skipTurn()));
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
    QString imageGridFile = "imgs/reversi_grid.png";
    QImage imageTable(imageTableFile);
    QImage imageGrid(imageGridFile);
    if(imageTable.isNull())
    {
        std::cout << "Error: file " << imageTableFile.toStdString() << " not found." << std::endl;
        return;
    }

    if(imageGrid.isNull())
    {
        std::cout << "Error: file " << imageGridFile.toStdString() << " not found." << std::endl;
        return;
    }

    QGraphicsPixmapItem *itemTable = new QGraphicsPixmapItem(QPixmap::fromImage(imageTable));
    QGraphicsPixmapItem *itemGrid = new QGraphicsPixmapItem(QPixmap::fromImage(imageGrid));
    scene->addItem(itemTable);
    scene->addItem(itemGrid);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->show();

    this->game->initGame();
    this->updateTable();
}

void ROWindow::initTable()
{
    for(int i=0; i<Reversi::BOARD_SIZE; i++) {
        for(int j=0; j<Reversi::BOARD_SIZE; j++) {
            this->tableOfPieces[i][j] = NULL;
        }
    }
}

void ROWindow::setPieceOnTable(QString pieceName, int x, int y)
{
    if(x < 0 || y < 0 || x >= Reversi::BOARD_SIZE || y >= Reversi::BOARD_SIZE)
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

void ROWindow::verifyEndGame()
{
    if(this->game->endGame()){
        ui->statusBar->showMessage("End Game!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

        if(game->getBlackScore() == game->getWhiteScore() ) {
            QMessageBox::question(this,"Reversi", "Game set! There was no winner!",QMessageBox::Ok);
        }
        else {
            QString winner = game->getBlackScore() > game->getWhiteScore() ? "Black" : "White";
            QMessageBox::question(this,"Reversi", "Game set! "+winner+" wins.",QMessageBox::Ok);
        }
    }
}

void ROWindow::updateTable()
{
    for(int i=0; i<Reversi::BOARD_SIZE; i++)
    {
        for(int j=0; j<Reversi::BOARD_SIZE; j++)
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

    int x=0,y=0;
    if(this->game->getLastMove(x,y))
    {
        QChar line = 'A'+x;
        QChar column = '1'+y;
        QString pos = " "+(QString)line+""+(QString)column;
        ui->statusBar->showMessage("Move on "+pos, 5000);
        ui->label_lastMove->setText(pos);
    }
    else
    {
        ui->label_lastMove->setText("");
    }

    QString turn = this->game->getTurn() == Reversi::WHITE ? "White" : "Black";

    QString black_score = QString::number(this->game->getBlackScore());
    QString white_score = QString::number(this->game->getWhiteScore());

    ui->label_scoreBlack->setText(black_score);
    ui->label_scoreWhite->setText(white_score);
    ui->label_turn->setText(turn);

    this->verifyEndGame();
}

void ROWindow::playGame(int i, int j)
{
    if(i < 0 || j < 0 || i >= Reversi::BOARD_SIZE || j >= Reversi::BOARD_SIZE)
    {
        std::cout << "Error: index i:" << i << " or j:" << j << " out of bounding." << std::endl;
        return;
    }

    bool validMove = this->game->play(i,j);
    if(validMove){
        this->updateTable();
    }
    else{
        ui->statusBar->showMessage("Invalid move! ", 5000);
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

    this->playGame(i,j);
}

void ROWindow::playCPU()
{
    /*while(!this->game->endGame())
    {
        if(this->game->getTotalMarkers() == 0)
        {
            this->game->changeTurn();
        }

        //h2 - black
        if(this->game->getTurn() == Reversi::BLACK)
        {
            int i=0,j=0;
            ArtificialIntelligence ia(this->game);
            ia.setAgent(2);
            ia.calculateBetterMove(i,j);
            this->playGame(i,j);
        }
        else
        {*/
            //h3 - white
            int i=0,j=0;
            ArtificialIntelligence ia(this->game);
            ia.setAgent(2);
            ia.setLevel(3);
            ui->statusBar->showMessage("Thinking...");
            ia.calculateBetterMove(i,j);
            ui->statusBar->showMessage("");
            this->playGame(i,j);
        /*}
    }*/
}

void ROWindow::restartGame()
{
    this->game->restartGame();
    this->updateTable();
}

void ROWindow::skipTurn()
{
    int totalMarkers = this->game->getTotalMarkers();
    if(totalMarkers > 0)
    {
        ui->statusBar->showMessage("You can only skip when you can't play.", 5000);
        return;
    }
    else
    {
        this->game->changeTurn();
        this->updateTable();
    }
}


void ROWindow::on_lineEdit_playAt_returnPressed()
{
    QString pos = ui->lineEdit_playAt->text();
    int i = pos.at(0).toUpper().toLatin1() - 'A';
    int j = pos.at(1).toUpper().toLatin1() - '1';

    this->playGame(i,j);
}

void ROWindow::on_undoLastMoveButton_released()
{
    this->game->undoLastMove();
    this->updateTable();
}
