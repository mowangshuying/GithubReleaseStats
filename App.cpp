#include <QApplication>

#include "StatsWindow.h"
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StatsWindow window;
    window.show();
    return app.exec();
}
