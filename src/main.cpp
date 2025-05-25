#include <QApplication>
#include <QWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget widget;
    widget.setWindowTitle("ReadyGPS | Système de navigation par GPS");
    widget.resize(400, 300);
    widget.show();
    return app.exec();
}
