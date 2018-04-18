#include "MainWindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //ws = new EchoClient(QUrl("ws://chess12.herokuapp.com"), this);
    ws = new NetManager(this);
    bord = new Bord(this);
    blackUser = new MyUser(this);
    whiteUser = new MyUser(this);
    menueButton = new QPushButton(this);
    menue = new MyMenue(this);
    connectionForm = new MyConnectionForm(this);

    connect(this, SIGNAL(readyToShow(char)), menue, SLOT(update()));
    connect(menueButton, SIGNAL(clicked(bool)), menue, SLOT(showGameMenue()));
    connect(menue, SIGNAL(buttonClicked(QString)), this, SLOT(buttonManager(QString)));
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

    setGeometry(100,100,700,600);
    menueButton->setText("Меню");
    whiteUser->setIsWhite(true);
    blackUser->setIsWhite(false);
    menue->startMenue();
    connectionForm->hide();
}

MainWindow::~MainWindow() {

}
