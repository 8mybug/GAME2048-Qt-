#include "widget2048.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 20 140
    QApplication a(argc, argv);
    Widget2048 w;
    w.show();

    return a.exec();
}
