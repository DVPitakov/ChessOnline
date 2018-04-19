#include "MainWindow.h"
MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    netManager = new NetManager(this);
    bord = new BordWidget(this);
    blackUser = new MyUser(this);
    whiteUser = new MyUser(this);
    menueButton = new QPushButton(this);
    menue = new MyMenue(this);
    connectionForm = new MyConnectionStatusWidget(this);

    connect(this, SIGNAL(readyToShow(char)), menue, SLOT(update()));
    connect(menueButton, SIGNAL(clicked(bool)), menue, SLOT(showGameMenue()));
    connect(menue, SIGNAL(buttonClicked(QString)), this, SLOT(buttonManager(QString)));
    connect(bord, SIGNAL(moved(int, int)), netManager, SLOT(sendStep(int,int)));
    connect(bord, SIGNAL(pawChanged(char)), netManager, SLOT(sendPawTrans(char)));
    connect(bord, SIGNAL(victory(char, char)), netManager, SLOT(sendGameEnd(char,char)));
    connect(bord, SIGNAL(victory(char,char)), menue, SLOT(showWinMenue()));
    connect(netManager, SIGNAL(friendIsFound(int)), this, SLOT(startGame(int)));
    connect(netManager, SIGNAL(friendIsFound(int)), connectionForm, SLOT(friendFounded()));
    connect(netManager, SIGNAL(friendIsFound(int)), menue, SLOT(hide()));
    connect(netManager, SIGNAL(newStep(int,int)), bord, SLOT(moveFig(int,int)));
    connect(netManager, SIGNAL(newStep(int,int)), bord, SLOT(chngSto()));
    connect(netManager, SIGNAL(pawTransed(char)), bord, SLOT(afterPawTrans(char)));
    connect(netManager, SIGNAL(gameEnd(char)), this, SLOT(chooseEndMenue(char)));
    connect(netManager, SIGNAL(wsConnected()), connectionForm, SLOT(connected()));
    connect(netManager, SIGNAL(lose()), menue, SLOT(showDisconnectMenue()));
    connect(netManager, SIGNAL(nichia()), menue, SLOT(proposedNichia()));
    connect(netManager, SIGNAL(saidYes()), menue, SLOT(showNichia()));
    connect(netManager, SIGNAL(saidNot()), menue, SLOT(hide()));

    setGeometry(100,100,700,600);
    menueButton->setText("Меню");
    whiteUser->setIsWhite(true);
    blackUser->setIsWhite(false);
    menue->startMenue();
    connectionForm->hide();
}

MainWindow::~MainWindow() {}
