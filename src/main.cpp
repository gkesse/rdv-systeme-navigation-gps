#include <QApplication>
#include "cMainWindow.h"

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(resources);
    QApplication app(argc, argv);
    cMainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
