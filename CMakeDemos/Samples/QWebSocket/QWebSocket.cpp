#include "QWebSocket.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "DoubleValidator.h"

QWebSocket::QWebSocket(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //ui.tabWidget->set
    auto strUrl = QString("http://www.ilab-x.com/sys/api/user/validate?username=%1&password=%2&nonce=%3&cnonce=%4");
    auto strName = QString("test");
    auto strPasswd = QString("2760F0245D3C03E7ABDA1CCA310187E2E33EEB886FDE0FCD5C827E971AED44D7");
    auto strnonce = QString("0F2785E6ED1B59AC");
    auto strcnonce = QString("F5A981C203030722");
    pManager = new QNetworkAccessManager(this);
    connect(pManager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(replyFinished(QNetworkReply*)));

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(send()));

    pManager->get(QNetworkRequest(QUrl(strUrl.arg(strName, strPasswd, strnonce, strcnonce))));

    ui.lineEdit->setValidator(new DoubleValidator(0, 200, 3));
}

void QWebSocket::replyFinished(QNetworkReply* reply)
{
    if (reply)
    {
        switch (reply->error())
        {
        case QNetworkReply::NoError:
        {
            auto data = QString::fromUtf8(reply->readAll());
            parseReply(data);
        }
        break;
        case QNetworkReply::ContentNotFoundError:
        {
            QUrl failedUrl;
            failedUrl = reply->request().url();
            int httpStatus = reply->attribute(
                QNetworkRequest::HttpStatusCodeAttribute).toInt();
            QString reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
            qDebug() << "url" << failedUrl << httpStatus << "   " << reason;
        }
        break;
        default:
            break;
        }
    }
}

int QWebSocket::parseReply(QString const& content)
{
    auto json = QJsonDocument::fromJson(content.toUtf8()).object();
    auto it = json.find("code");
    if (it == json.end()) return -1;
    switch (it->toInt())
    {
    case 0:
    {
        // 成功
        return it->toInt();
    }
    break;
    case 4:
    case 5:
    {
        // 用户名或者密码错错
        return it->toInt();
    }
    break;
    default:
        break;
    }
    return -1;
}

void QWebSocket::send()
{
    auto strUrl = QString("http://www.ilab-x.com/project/log/upload?xjwt=type=2%1");
    QString strJsonData = u8R"({
        "username":"用户名",
            " projectTitle" : "项目名称",
            " childProjectTitle" : "子项目名称",
            " status" : 1,
            "score" : 80,
            "startDate" : 1522646936000,
            "endDate" : " 1522647936000",
            "timeUsed" : 15,
            "issuerId" : " PK1502",
            "attachmentId" : 12})";

    // 主要处理这个函数，strURL是拼接地址，参考构造中的get方法
    // post完成后也会触发finished信号
    // strJsonData:服务器需要的json格式
    pManager->post(QNetworkRequest(QUrl(strUrl)), strJsonData.toLocal8Bit());
}
