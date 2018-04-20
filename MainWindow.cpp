#include <QInputDialog>
#include "MainWindow.h"
MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    showURLInputDialog();
    netManager = new NetManager(this);
    bord = new BordWidget(this);
    blackUser = new MyUser(this);
    whiteUser = new MyUser(this);
    menueButton = new QPushButton(this);
    menue = new MyMenue(this);
    connectionForm = new MyConnectionStatusWidget(this);
    connect(this, SIGNAL(readyToShow(unsigned char)), menue, SLOT(update()));
    connect(menueButton, SIGNAL(clicked(bool)), menue, SLOT(showGameMenue()));
    connect(menue, SIGNAL(buttonClicked(QString)), this, SLOT(buttonManager(QString)));
    connect(bord, SIGNAL(moved(FigurePos, FigurePos)), netManager, SLOT(sendStep(FigurePos,FigurePos)));
    connect(bord, SIGNAL(pawChanged(unsigned char)), netManager, SLOT(sendPawTrans(unsigned char)));
    connect(bord, SIGNAL(victory(EndCouse, unsigned char)), netManager, SLOT(sendGameEnd(EndCouse,unsigned char)));
    connect(bord, SIGNAL(victory(EndCouse, unsigned char)), menue, SLOT(showWinMenue()));
    connect(netManager, SIGNAL(friendIsFound(int)), this, SLOT(startGame(int)));
    connect(netManager, SIGNAL(friendIsFound(int)), connectionForm, SLOT(friendFounded()));
    connect(netManager, SIGNAL(friendIsFound(int)), menue, SLOT(hide()));
    connect(netManager, SIGNAL(newStep(FigurePos, FigurePos)), bord, SLOT(moveFig(FigurePos, FigurePos)));
    connect(netManager, SIGNAL(newStep(FigurePos, FigurePos)), bord, SLOT(chngSto()));
    connect(netManager, SIGNAL(pawTransed(unsigned char)), bord, SLOT(afterPawTrans(unsigned char)));
    connect(netManager, SIGNAL(gameEnd(EndCouse)), this, SLOT(chooseEndMenue(EndCouse)));
    connect(netManager, SIGNAL(userDataReceived()), connectionForm, SLOT(connected()));
    connect(netManager, SIGNAL(connectionFail()), menue, SLOT(showDisconnectMenue()));
    connect(netManager, SIGNAL(nichia()), menue, SLOT(proposedNichia()));
    connect(netManager, SIGNAL(anotheUserAnsweredYes()), menue, SLOT(showNichia()));
    connect(netManager, SIGNAL(anotheUserAnsweredNot()), menue, SLOT(hide()));

    setGeometry(100,100,700,600);
    menueButton->setText("Меню");
    whiteUser->setIsWhite(true);
    blackUser->setIsWhite(false);
    menue->startMenue();
    connectionForm->hide();
}

void MainWindow::chooseEndMenue(EndCouse couse) {
    if(couse == EndCouse::YOUR_FAIL_ONE) {
        menue->showFailMenue();
    }
    else if (couse == EndCouse::YOUR_WIN) {
        menue->showWinMenue();
    }
    else if (couse == EndCouse::YOUR_FAIL_TWO) {
        menue->showFailMenue();
    }
    else if (couse == EndCouse::RIVAL_SURENDED) {
        menue->showWinMenue();
    }
}

void MainWindow::buttonManager(QString eventName) {
    if (eventName ==  "sdatsa") {
        menue->showFailMenue();
        netManager->sendGameEnd(EndCouse::RIVAL_SURENDED,0);
    }
    else if (eventName ==  "online") {
        connectionForm->friendSearch();
        netManager->run();
    }
    else if (eventName ==  "continue") {
        bord->restart();
        menue->showStartGame();
        whiteUser->setIsUser(false);
        blackUser->setIsUser(false);
        menue->update();
    }
    else if (eventName == "return") {
        menue->hide();
        bord->setHidden(false);
    }
    else if (eventName ==  "settings") {

    }
    else if (eventName ==  "exit") {
        this->close();
    }
    else if (eventName == "nichia") {
        netManager->sendNichia();
        menue->showWait();
    }
    else if (eventName == "breakGame") {

    }
    else if (eventName == "sayYes") {
        netManager->sayYes();
        menue->showNichia();
    }
    else if (eventName == "sayNot") {
        netManager->sayNot();
        menue->setHidden(true);
    }
    else {
    }
}

void MainWindow::startGame(int color) {
    activeBoard();
    whiteUser->setMyStep(true);
    if(color) {
        whiteUser->setIsUser(true);
        bord->setColor(0);
    }
    else {
        blackUser->setIsUser(true);
        bord->setColor(1);
    }
    update();
}

void MainWindow::showMenue() {
    bord->setEnabled(false);
    menueButton->setEnabled(false);
    menue->setEnabled(true);
    menue->setHidden(false);
    emit readyToShow(1);
}

void MainWindow::activeBoard() {
    bord->setEnabled(true);
    menueButton->setEnabled(true);
}

void MainWindow::paintEvent(QPaintEvent*) {
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

void MainWindow::showURLInputDialog() {
    const char DEFAULT_IP_AND_PORT[]="http://127.0.0.1:8000";
    bool bOk;
    QString ipInput = QInputDialog::getText( 0, "Ввод URL", "Введите URL:", QLineEdit::Normal, DEFAULT_IP_AND_PORT, &bOk);
    if (!bOk) {
        NetManager::setTargetedUrlString(DEFAULT_IP_AND_PORT);
    }
    else {
        NetManager::setTargetedUrlString(ipInput);
    }
}

MainWindow::~MainWindow() {}
