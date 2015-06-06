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
