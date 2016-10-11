#ifndef WEBSOCKETCONNECTOR_H
#define WEBSOCKETCONNECTOR_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTimer>

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
    void pawTransed(char);
    void gameEnd(char);

public slots:
    void connectionError() {
        if (connected == false) {
            qDebug() << "Соединение разорвано";
        }
        else {
            connected = false;
            sendHowAreYou();
            timer->start(3000);
        }
    }

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
            qDebug() << "STEP SENDED:" << oldPos + 0.1 << newPos + 0.1;

        }

    }
    void sendPawTrans(char figure) {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"pawTrans\"" +
                                         " ,\n\"figure\": " + QString::number(figure) +
                                         " ,\n\"pos\": " + QString::number(0) +
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
    void sendHowAreYou() {
        if (online) {
            qDebug() << "how are you sended";
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"howAreYou\"" +
                                         " ,\n\"forBro\": " + "Are you alive bro?" +
                                         " \n}"));
        }
    }

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    QTimer *timer;
    bool m_debug;
    bool connected = true;
};


#endif // WEBSOCKETCONNECTOR_H
