#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ws = new EchoClient(QUrl("ws://127.0.0.1:8081"), true);
    bord = new Bord(this);
    blackUser = new MyUser(this);
    blackUser->setIsWhite(false);
    whiteUser = new MyUser(this);
    whiteUser->setIsWhite(true);
    //myTimer = new MyTimer(this);
    //myTimer->setTime(60);
    menueButton = new QPushButton(this);
    menueButton->setText("Меню");
    setGeometry(100,100,700,600);
    menue = new MyMenue(this);
    connectionForm = new MyConnectionForm(this);

    connect(menueButton, SIGNAL(clicked(bool)), menue, SLOT(showGameMenue()));
    connect(this, SIGNAL(readyToShow(char)), menue, SLOT(update()));

    connect(menue, SIGNAL(buttonClicked(QString)), this, SLOT(buttonManager(QString)));
    menue->startMenue();
    connect(bord, SIGNAL(moved(int, int)), ws, SLOT(sendStep(int,int)));
    connect(bord, SIGNAL(pawChanged(char)), ws, SLOT(sendPawTrans(char)));
    connect(bord, SIGNAL(victory(char, char)), ws, SLOT(sendGameEnd(char,char)));
    connect(bord, SIGNAL(victory(char,char)), menue, SLOT(showWinMenue()));

    connect(ws, SIGNAL(friendIsFound(int)), this, SLOT(startGame(int)));
    connect(ws, SIGNAL(friendIsFound(int)), connectionForm, SLOT(friendFounded()));
    connect(ws, SIGNAL(friendIsFound(int)), menue, SLOT(hide()));
    connect(ws, SIGNAL(newStep(int,int)), bord, SLOT(moveFig(int,int)));
    connect(ws, SIGNAL(pawTransed(char)), bord, SLOT(afterPawTrans(char)));
    connect(ws, SIGNAL(gameEnd(char)), this, SLOT(chooseEndMenue(char)));
    connect(ws, SIGNAL(newStep(int,int)), bord, SLOT(chngSto()));
    connect(ws, SIGNAL(wsConnected()), connectionForm, SLOT(connected()));
    connect(ws, SIGNAL(lose()), menue, SLOT(showDisconnectMenue()));
    connect(ws, SIGNAL(nichia()), menue, SLOT(proposedNichia()));
    connect(ws, SIGNAL(saidYes()), menue, SLOT(showNichia()));
    connect(ws, SIGNAL(saidNot()), menue, SLOT(hide()));

    bord->setEnabled(false);
    menueButton->setEnabled(false);
    connectionForm->hide();
}

MainWindow::~MainWindow() {

}
