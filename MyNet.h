#ifndef MYNET_H
#define MYNET_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>
#include <QFile>
#include <QLabel>

class MyNet : public QObject
{
    Q_OBJECT
private:

public:

    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *networkManager;
    QLabel * Label;
    MyNet(QObject *parent = NULL);
    void vtos(QByteArray * parr, QLabel *_Label);

signals:
    void voiceConverted(QString string);
public slots:
    void replyFinished(QNetworkReply* reply) {
        QString str = QString::fromUtf8(reply->readAll());
        qDebug() << str;
        Label->setText(str);
        emit voiceConverted(str);
    }
};

#endif // MYNET_H
