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
    bool isConnected{false};
    bool isActive{false};
    long int myId{0};
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

signals:
    void closed();
    void friendIsFound(int);
    void newStep(int, int);
    void pawTransed(char);
    void gameEnd(char);
    void wsConnected();
    void lose();
    void nichia();
    void saidYes();
    void saidNot();

public slots:
    void connectionError() {
        if (isActive == false) {
            qDebug() << "Соединение разорвано";
            timer->stop();
            emit lose();
        }
        else {
            isActive = false;
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
    void sendNichia() {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"nichia\"" +  " \n}"));
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
            timer->stop();
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"gameEnd\"" +
                                         " ,\n\"couse\": " + QString::number(couse) +
                                         " ,\n\"data\": " + QString::number(pos) +
                                         " \n}"));
        }
    }
    void sayYes() {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"sayYes\"" +
                                         " \n}"));
        }
    }
    void sayNot()  {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"sayNot\"" +
                                         " \n}"));
        }
    }

    void sendHowAreYou() {
        if (online) {
            m_webSocket.sendTextMessage((QString(
                                             "{\"action\": ") + " \"howAreYou\"" +
                                         " \n}"));
        }
    }

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    QTimer *timer;
    QTimer *openTimer;
    bool m_debug;
    bool connected = true;
};


#endif // WEBSOCKETCONNECTOR_H
