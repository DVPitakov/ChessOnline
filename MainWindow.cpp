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
    connect(netManager, SIGNAL(userDataReceived()), connectionForm, SLOT(connected()));
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

void MainWindow::paintEvent(QPaintEvent* event) {
    int x0 = 0;
    int y0 = 0;
    bool b =  width() > height();
    int awidth = width();
    int aheight = height();
    if (b) {
        if (double(awidth) / aheight < 1.2) {
           aheight =  awidth / 1.2;
           y0 = (height() - aheight)/2;
        }
        else if (double(awidth) / aheight > 1.3) {
            awidth = aheight * 1.3;
            x0 = (width() - awidth)/2;
        }
    }
    else {
        if (double(aheight) / awidth < 1.2) {
            awidth = aheight / 1.2;
            x0 = (width() - awidth)/2;
        } else if (double(aheight) / awidth > 1.3) {
            aheight = awidth * 1.3;
            y0 = (height() - aheight)/2;
        }
    }
    int bw;
    b = awidth > aheight;
    bw = b ? aheight : awidth;
    int w0 = 0;
    int h0 = 0;
    int dw = 0;
    int dh = 0;

    int w;
    int h;

    if (b) {
        w = awidth - aheight;
        h = aheight / 3;
    }
    else {
        w = awidth / 3;
        h = aheight - awidth;
    }
    b ? w0 = bw : h0 = bw;
    b ? dh = aheight / 3 : dw = awidth / 3;
    whiteUser->setGeometry(x0 + w0,y0 + h0, w, h);
    menueButton->setGeometry(x0 + w0 + dw, y0 + h0 +  dh, w, h);
    blackUser->setGeometry(x0 + w0 + 2 * dw, y0 + h0 + 2 * dh, w, h);
    bord->setGeometry(x0,y0,bw,bw);
    connectionForm->setGeometry(0, 0, width() ,height());
    menue->setGeometry(0,0,width(),height());

}

MainWindow::~MainWindow() {}
