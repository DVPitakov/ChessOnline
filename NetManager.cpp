#include "NetManager.h"
#include <QObject>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtXml>
#include <QUrlQuery>
#include <QDomElement>
#include <QDomDocument>

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
   sendGameMessage("{\"action\": \"upgrade\"}");

}

void NetManager::runUpdates(int interval) {
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(upgradeGameState()));
    timer->start();

}

void NetManager::performResponse(QString message) {
    QDomDocument doc;
    if (false == doc.setContent(message))
         throw QString("bad XML-file: setContent");
    QDomElement root = doc.documentElement();
    for(QDomNode event = root.firstChild(); !event.isNull(); event = event.nextSibling()) {
        QString action;
        QString user_id;
        QString game_id;
        int newPos;
        int oldPos;
        int pos;
        int figure;
        int color;
        int couse;
        for (QDomNode eventField = event.firstChild(); !eventField.isNull(); eventField = eventField.nextSibling()) {
            if (eventField.nodeName() == "action") {
                action = eventField.firstChild().nodeValue();
            }
            else if (eventField.nodeName() == "oldPos") {
                oldPos = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == "newPos") {
                newPos = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == "figure") {
                figure = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == "pos") {
                pos = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == "userColor") {
                color = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == "user_id") {
                user_id = eventField.firstChild().nodeValue();
            }
            else if (eventField.nodeName() == "game_id") {
                game_id = eventField.firstChild().nodeValue();
            }
            else if (eventField.nodeName() == "couse") {
                couse = eventField.firstChild().nodeValue().toInt();
            }
        }

        if (action == "step") {
            emit(newStep(oldPos, newPos));
        }
        else if (action == "pawTrans") {
            emit pawTransed(figure);
        }
        else if (action == "color") {
            emit friendIsFound(color);
        }
        else if (action == "gameEnd") {
            timer->stop();
            emit gameEnd(couse);
            stop();
        }
        else if (action == "nichia") {
            emit nichia();
        }
        else if (action == "sayYes") {
            emit saidYes();
            stop();
        }
        else if (action == "sayNot") {
            emit saidNot();
        }
        else if (action == "userKey") {
            this->userId = user_id;
            this->gameId = game_id;
            emit wsConnected();
            qDebug() << userId;
            qDebug() << gameId;
        }
    }

}
