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
    static void setTargetedUrlString(QString str);
    explicit NetManager(QObject *parent = 0);
    void run();

private:
    static QString defaultUrlString;
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
    void pawTransed(unsigned char);
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

    void sendPawTrans(unsigned char figure);

    void sendGameEnd(EndCouse couse, unsigned char pos);

    void sayYes();

    void sayNot();

private slots:
    void connectionError();

};

#endif // NETMANAGER_H
