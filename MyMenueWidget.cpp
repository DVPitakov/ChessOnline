#include "MyMenueWidget.h"

MyMenue::MyMenue(QWidget *parent) : QWidget(parent) {
     backGround = QImage(":/background.jpg");
}

void MyMenue::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QColor color1(255,255,255);
    QColor color2(0,0,0);
    painter.setBrush(color1);
    painter.setPen(color1);
    painter.drawRect(0,0,width() - 1,height() - 1);
    painter.setPen(color2);
    painter.setBrush(QColor(255,255,255));
    QImage backGround2 = backGround.scaled(width(),height());
     painter.drawImage(0,0, backGround2);

    for(int i = 0; i < buttonListLen; i++) {

        if (buttonList[i].type == "button") {
            painter.drawRect(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2);
            painter.drawText(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,buttonList[i].buttonText);
        }
        else if (buttonList[i].type == "header"){
            painter.drawText(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,buttonList[i].buttonText);
        }
    }
}

void MyMenue::addButton(QString eventName, QString buttonName, QString buttonType) {
    buttonList[buttonListLen].buttonActionName = eventName;
    buttonList[buttonListLen].type = buttonType;
    buttonList[buttonListLen].buttonText = buttonName;
    buttonListLen += 1;
}


void MyMenue::releaseButton() {
    buttonListLen = 0;
}

void MyMenue::mouseReleaseEvent(QMouseEvent* event) {
    int x = event->x();
    int y = event->y();
    for (int i = 0; i < buttonListLen; i++) {
        if (width() * 0.05 < x && height() * (0.1 + 0.22 * i) < y && width() * 0.95 > x && height() * (0.3 + 0.22 * i) > y) {
            emit buttonClicked(buttonList[i].buttonActionName);
        }
    }
}

void MyMenue::startMenue() {
    addButton("online", "Играть онлайн");
    addButton("exit", "Выход");
}
void MyMenue::gameMenue() {
    addButton("return", "Вернуться");
    addButton("sdatsa", "Сдаться");
    addButton("nichia", "Предложить ничью");
    addButton("exit", "Выход");
}
void MyMenue::failMenue() {
    addButton("defeat", "Вы проиграли", "header");
    addButton("continue", "Ок");
}
void MyMenue::disconnectMenue() {
    addButton("defeat", "Соединение разорвано", "header");
    addButton("continue", "Ок");
}
void MyMenue::winMenue() {
    addButton("victory", "Вы выиграли", "header");
    addButton("continue", "Ок");
}
void MyMenue::nichiaMenue() {
    addButton("defeat", "Противник предлагает ничью", "header");
    addButton("sayYes", "Согласиться");
    addButton("sayNot", "Отказаться");
}
void MyMenue::staticNichia() {
    addButton("continue", "Ничья", "header");
    addButton("continue", "Ок");
}
void MyMenue::waitMenue() {
    addButton("info", "Ожидание ответа", "header");
}

void MyMenue::showStartGame() {
    releaseButton();
    startMenue();
    this->show();
    update();
}

void MyMenue::showGameMenue() {
    releaseButton();
    gameMenue();
    this->show();
    update();
}

void MyMenue::showWinMenue() {
    releaseButton();
    winMenue();
    this->show();
    update();
}

void MyMenue::showWait() {
    releaseButton();
    waitMenue();
    this->show();
    update();
}

void MyMenue::showFailMenue() {
    releaseButton();
    failMenue();
    this->show();
    update();
}

void MyMenue::showDisconnectMenue() {
    releaseButton();
    disconnectMenue();
    this->show();
    update();
}

void MyMenue::proposedNichia() {
    releaseButton();
    nichiaMenue();
    this->show();
    update();
}

void MyMenue::showNichia() {
    releaseButton();
    staticNichia();
    this->show();
    update();
}
