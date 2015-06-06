#ifndef ROWINDOW_H
#define ROWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QImage>
#include <QString>
#include <QFileDialog>


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

private:
    Ui::ROWindow *ui;
};

#endif // ROWINDOW_H
