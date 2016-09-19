#ifndef WEBSOCKETCONNECTOR_H
#define WEBSOCKETCONNECTOR_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class EchoClient : public QObject
{
    Q_OBJECT
    bool online{false};
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

signals:
    void closed();
    void friendIsFound(int);
    void newStep(int, int);
    void pawTransed(char, char);
    void gameEnd(char);
public slots:
    void open();
    void onConnected();
    void onTextMessageReceived(QString message);
    void sendStep(int oldPos, int newPos) {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"step\"" +
                                         " ,\n\"oldPos\": " + QString::number(oldPos) +
                                         " ,\n\"newPos\": " + QString::number(newPos) +
                                         " \n}"));

        }

    }
    void sendPawTrans(char figure, char pos) {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"pawTrans\"" +
                                         " ,\n\"figure\": " + QString::number(figure) +
                                         " ,\n\"pos\": " + QString::number(pos) +
                                         " \n}"));
        }
    }
    void sendGameEnd(char couse, char pos) {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"gameEnd\"" +
                                         " ,\n\"couse\": " + QString::number(couse) +
                                         " ,\n\"data\": " + QString::number(pos) +
                                         " \n}"));
        }
    }

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};


#endif // WEBSOCKETCONNECTOR_H
