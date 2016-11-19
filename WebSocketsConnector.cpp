#include "WebSocketsConnector.h"

EchoClient::EchoClient(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_url(url)
{
    timer = new QTimer(this);
    openTimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(connectionError()));
    connect(openTimer, SIGNAL(timeout()), this, SLOT(open()));
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);


}

void EchoClient::open() {

    if (!isConnected) {
        openTimer->start(2000);
        m_webSocket.close();
        m_webSocket.open(QUrl(m_url));
    }
    else {
        openTimer->stop();
        isConnected = false;
    }
}
void EchoClient::onConnected()
{
    online = true;
    isConnected = true;
    isActive = true;
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &EchoClient::onTextMessageReceived);
    emit wsConnected();
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
            int couse = root.value("couse").toInt();
            qDebug()  << "!!! " << couse;
            timer->stop();
            isConnected = false;
            emit gameEnd(couse);
            stop();
        }
        else if (action == "howAreYou") {
            isActive = true;
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
    }
}
