#include <QApplication>

#include <QWidget>
#include "StatsWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StatsWindow window;
    window.show();
    return app.exec();
}
