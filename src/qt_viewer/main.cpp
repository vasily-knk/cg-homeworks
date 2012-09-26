#include "stdafx.h"
#include "qt_viewer.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_viewer w;
    w.show();
    return a.exec();
}
