#include "QDemo.h"
#include <QtWidgets/QApplication>
#include <QPrintEngine>
#include <QtGui/QTextDocument>
#include <QtCore/QTextStream>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QWebEngineView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWebEngineView w;
    w.load(QUrl("http://qt-project.org/"));
    w.show();

    //QFile file;
    //file.setFileName("E:/OtherSpace/OnJava8/_book/docs/book/05-Control-Flow.html");
    //if (!file.open(QIODevice::ReadOnly))
    //    return 0;
    //QString html_text = file.readAll();
    //file.close();
    //QPrinter html_printer;
    //html_printer.setOutputFormat(QPrinter::PdfFormat);
    //html_printer.setOutputFileName("E:/OtherSpace/OnJava8/_book/docs/book/05-Control-Flow.pdf");
    //QTextDocument doc;
    //doc.setHtml(html_text);
    //doc.print(&html_printer);

    return a.exec();
}
