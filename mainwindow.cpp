#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ws = new EchoClient(QUrl("ws://localhost:8081"), true);
    bord = new Bord(this);
    blackUser = new MyUser(this);
    blackUser->setIsWhite(false);
    whiteUser = new MyUser(this);
    whiteUser->setIsWhite(true);
    menueButton = new QPushButton(this);
    menueButton->setText("Меню");
    setGeometry(100,100,700,600);
    menue = new MyMenue(this);
    connectionForm = new MyConnectionForm(this);

    connect(menueButton, SIGNAL(clicked(bool)), this, SLOT(showMenue()));
    connect(this, SIGNAL(readyToShow(char)), menue, SLOT(update()));

    connect(menue, SIGNAL(debugChosed()), this, SLOT(activeBoard()));
    connect(menue, SIGNAL(buttonClicked(QString)), this, SLOT(buttonManager(QString)));
    menue->startMenue();
    connect(bord, SIGNAL(moved(int, int)), ws, SLOT(sendStep(int,int)));

    connect(ws, SIGNAL(friendIsFound(int)), this, SLOT(startGame(int)));
    connect(ws, SIGNAL(friendIsFound(int)), connectionForm, SLOT(friendFounded()));
    connect(ws, SIGNAL(friendIsFound(int)), menue, SLOT(hide()));

    connect(ws, SIGNAL(newStep(int,int)), bord, SLOT(moveFig(int,int)));
    connect(ws, SIGNAL(newStep(int,int)), bord, SLOT(update()));
    connect(ws, SIGNAL(pawTransed(char,char)), bord, SLOT(afterPawTrans(char,char)));
    connect(bord, SIGNAL(pawChanged(char, char)), ws, SLOT(sendPawTrans(char, char)));
    connect(bord, SIGNAL(victory(char, char)), ws, SLOT(sendGameEnd(char,char)));
    connect(ws, SIGNAL(gameEnd(char)), menue, SLOT(update()));
    connect(ws, SIGNAL(newStep(int,int)), bord, SLOT(chngSto()));

    bord->setEnabled(false);
    menueButton->setEnabled(false);
    connectionForm->hide();
}

MainWindow::~MainWindow() {

}
