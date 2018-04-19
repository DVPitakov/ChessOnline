#include "NetManager.h"
#include <QObject>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtXml>
#include <QDomElement>
#include <QDomDocument>

NetManager::NetManager(QObject *parent) : QObject(parent) {
    timer = new QTimer(this);
    restclient = new QNetworkAccessManager(this);
    connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}

void NetManager::sendGameMessage(QString msg) {
    QUrl url(QString("http://127.0.0.1:8000")
             + "?user_id=" + userId
             + "&game_id=" + gameId
             + "&user_msg=" + msg
             );
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
    const char * const ACTION_TAG = "action";
    const char * const OLD_POS_TAG = "oldPos";
    const char * const NEW_POS_TAG = "newPos";
    const char * const FIGURE_TAG = "figure";
    const char * const POS_TAG = "pos";
    const char * const USER_COLOR_TAG = "userColor";
    const char * const USER_ID_TAG = "user_id";
    const char * const GAME_ID_TAG = "game_id";
    const char * const COURSE_TAG = "course";


    QDomDocument doc;
    if (false == doc.setContent(message)) {
        errorCounter += 1;
    }
    else {
        errorCounter = 0;
    }
    QDomElement root = doc.documentElement();
    for(QDomNode event = root.firstChild(); !event.isNull(); event = event.nextSibling()) {
        QString action;
        QString userId;
        QString gameId;
        int newPos;
        int oldPos;
        int pos;
        int figure;
        int color;
        int couse;
        for (QDomNode eventField = event.firstChild(); !eventField.isNull(); eventField = eventField.nextSibling()) {
            if (eventField.nodeName() == ACTION_TAG) {
                action = eventField.firstChild().nodeValue();
            }
            else if (eventField.nodeName() == OLD_POS_TAG) {
                oldPos = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == NEW_POS_TAG) {
                newPos = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == FIGURE_TAG) {
                figure = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == POS_TAG) {
                pos = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == USER_COLOR_TAG) {
                color = eventField.firstChild().nodeValue().toInt();
            }
            else if (eventField.nodeName() == USER_ID_TAG) {
                userId = eventField.firstChild().nodeValue();
            }
            else if (eventField.nodeName() == GAME_ID_TAG) {
                gameId = eventField.firstChild().nodeValue();
            }
            else if (eventField.nodeName() == COURSE_TAG) {
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
            this->userId = userId;
            this->gameId = gameId;
            emit userDataReceived();
        }
    }

}
