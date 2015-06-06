#include "rowindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ROWindow w;
    w.initGame();
    w.show();

    return a.exec();
}
