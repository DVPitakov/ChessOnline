#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>

#include <QObject>
#include <QNetworkReply>
#include <QTimer>

class NetManager : public QObject
{
    Q_OBJECT
public:
    bool online{false};
    bool isConnected{false};
    bool isActive{false};
    long int myId{0};
    explicit NetManager(QObject *parent = 0);
    void run() {
        runUpdates(1000);
    }

private:
    QNetworkAccessManager *restclient;
    QString userId;
    QString gameId;
    QTimer * timer;
    void runUpdates(int interval);
    void onTextMessageReceived(QString message);
    void performRequest(QString message);
    void sendGameMessage(QString msg);


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
    void upgradeGameState();

    void replyFinished(QNetworkReply * reply) {
        performRequest(reply->readAll());
    }

    void connectionError() {
        if (isActive == false) {
            timer->stop();
            emit lose();
        }
        else {
            isActive = false;
        }
    }

    void stop() {
        online = false;
        isConnected = false;
        isActive = false;
        myId = 0;
        timer->stop();
    }

    void sendStep(int oldPos, int newPos) {
        if (online) {
            sendGameMessage((QString("{\"action\": ") + " \"step\"" +
                                     " ,\n\"oldPos\": " + QString::number(oldPos) +
                                     " ,\n\"newPos\": " + QString::number(newPos) +
                                     " \n}"));

        }

    }
    void sendNichia() {
        if (online) {
            sendGameMessage((QString("{\"action\": ") + " \"nichia\"" +  " \n}"));
        }
    }

    void sendPawTrans(char figure) {
        if (online) {
            sendGameMessage((QString("{\"action\": ") + " \"pawTrans\"" +
                                     " ,\n\"figure\": " + QString::number(figure) +
                                     " ,\n\"pos\": " + QString::number(0) +
                                     " \n}"));
        }
    }

    void sendGameEnd(char couse, char pos) {
        if (online) {
            timer->stop();
            sendGameMessage((QString("{\"action\": ") + " \"gameEnd\"" +
                                     " ,\n\"couse\": " + QString::number(couse) +
                                     " ,\n\"data\": " + QString::number(pos) +
                                     " \n}"));
            stop();
        }
    }

    void sayYes() {
        if (online) {
            sendGameMessage((QString("{\"action\": ") + " \"sayYes\"" + " \n}"));
            stop();
        }
    }

    void sayNot()  {
        if (online) {
            sendGameMessage((QString("{\"action\": ") + " \"sayNot\"" + " \n}"));
        }
    }

};

#endif // NETMANAGER_H
