#include "cMainWindow.h"

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ReadyGPS | Système de navigation par GPS");
    resize(400, 300);
}

cMainWindow::~cMainWindow()
{
}
