#include "QWebSocket.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWebSocket w;
    w.show();
    return a.exec();
}
