#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>
#include <QNetworkReply>
#include <QTimer>
#include <Models.h>

class NetManager : public QObject
{
    Q_OBJECT
public:
    explicit NetManager(QObject *parent = 0);
    void run();

private:
    bool online{false};
    bool isConnected{false};
    bool isActive{false};
    long int myId{0};
    int errorCounter{0};
    QNetworkAccessManager *restclient;
    QString userId;
    QString gameId;
    QTimer * timer;

    void runUpdates(int interval);
    void onTextMessageReceived(QString message);
    void performResponse(QString message);
    void sendGameMessage(QString msg);


signals:
    void friendIsFound(int);
    void newStep(FigurePos, FigurePos);
    void pawTransed(char);
    void gameEnd(EndCouse);
    void userDataReceived();
    void connectionFail();
    void nichia();
    void anotheUserAnsweredYes();
    void anotheUserAnsweredNot();


public slots:
    void upgradeGameState();

    void replyFinished(QNetworkReply * reply);

    void stop();

    void sendStep(FigurePos oldPos, FigurePos newPos);

    void sendNichia();

    void sendPawTrans(char figure);

    void sendGameEnd(EndCouse couse, char pos);

    void sayYes();

    void sayNot();

private slots:
    void connectionError();

};

#endif // NETMANAGER_H
