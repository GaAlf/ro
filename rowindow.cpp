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
     QGraphicsScene *scene = new QGraphicsScene();

     QString imageFile = "imgs/reversi_table.png";

     QImage image(imageFile);
     QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
     scene->addItem(item);
     ui->graphicsView->setScene(scene);
     ui->graphicsView->show();
}
