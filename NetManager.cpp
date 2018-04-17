#include "NetManager.h"
#include <QObject>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

NetManager::NetManager(QObject *parent) : QObject(parent) {
    timer = new QTimer(this);
    restclient = new QNetworkAccessManager(this);
    connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}

void NetManager::sendGameMessage(QString msg) {
    QUrl url("http://127.0.0.1:8080");
    QUrlQuery querystr;
    querystr.addQueryItem("user_id", userId);
    querystr.addQueryItem("game_id", gameId);
    querystr.addQueryItem("user_msg", msg);
    url.setQuery(querystr);
    QNetworkRequest request(url);
    restclient->get(request);
}

void NetManager::upgradeGameState() {
   sendGameMessage("{\"action\": \"nothing\"}");

}

void NetManager::runUpdates(int interval) {
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(upgradeGameState()));
    timer->start();

}

void NetManager::performRequest(QString message) {
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject root = document.object();
    QString action = root.value("action").toString();
    if (action == "step") {
        int oldPos = root.value("oldPos").toInt();
        int newPos = root.value("newPos").toInt();
        emit(newStep(oldPos, newPos));
    }
    else if (action == "pawTrans") {
        int figure = root.value("figure").toInt();
        int pos = root.value("pos").toInt();
        emit pawTransed(figure);
    }
    else if (action == "color") {
        int color = root.value("userColor").toInt();
        qDebug() << "color taked";
        timer->start(3000);
        emit friendIsFound(color);
    }
    else if (action == "gameEnd") {
        int couse = root.value("couse").toInt();
        qDebug()  << "!!! " << couse;
        timer->stop();
        emit gameEnd(couse);
        //stop();
    }
    else if (action == "nichia") {
        emit nichia();
    }
    else if (action == "sayYes") {
        emit saidYes();
        //stop();
    }
    else if (action == "sayNot") {
        emit saidNot();
    }
    else if (action == "userKey") {
        userId = root.value("user_id").toString();
        gameId = root.value("game_id").toString();
        qDebug() << userId;
        qDebug() << gameId;
    }
}
