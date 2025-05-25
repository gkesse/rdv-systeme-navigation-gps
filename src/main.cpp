#include <QApplication>
#include "cMainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    cMainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
