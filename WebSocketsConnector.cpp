#include "WebSocketsConnector.h"

#include <QtCore/QDebug>

EchoClient::EchoClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(connectionError()));
    if (m_debug)

        connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);


}

void EchoClient::open() {

    m_webSocket.open(QUrl(m_url));
}
void EchoClient::onConnected()
{
    online = true;
    if (m_debug)
        connect(&m_webSocket, &QWebSocket::textMessageReceived,
                this, &EchoClient::onTextMessageReceived);
}
void EchoClient::onTextMessageReceived(QString message)
{
    if (m_debug) {
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
            connected = false;
            emit friendIsFound(color);
        }
        else if (action == "gameEnd") {
            emit gameEnd(0);
        }
        else if (action == "howAreYou") {
            qDebug() << "TIME UPDATE";
            connected = true;
        }
    }
}
