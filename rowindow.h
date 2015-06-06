#ifndef ROWINDOW_H
#define ROWINDOW_H

#include <QMainWindow>

namespace Ui {
class ROWindow;
}

class ROWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ROWindow(QWidget *parent = 0);
    ~ROWindow();

private:
    Ui::ROWindow *ui;
};

#endif // ROWINDOW_H
