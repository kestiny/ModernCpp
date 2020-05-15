#pragma once

#include <QtWidgets/QMainWindow>
#include <QNetworkAccessManager>
#include "ui_QWebSocket.h"

class QWebSocket : public QMainWindow
{
    Q_OBJECT

public:
    QWebSocket(QWidget *parent = Q_NULLPTR);

private slots:
    void replyFinished(QNetworkReply* reply);
    void send();

private:
    int parseReply(QString const& content);

private:
    Ui::QWebSocketClass ui;
    QNetworkAccessManager* pManager;
};
