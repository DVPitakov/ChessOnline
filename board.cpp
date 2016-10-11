#include "board.h"

Bord::Bord(QWidget* parent):QWidget(parent)
{
    positions = boardLogic.getPositions();
    qDebug() << positions.toString();
    blackKing = QImage(":/blackKing.png");
    blackPeshka = QImage(":/blackPeshka.png");
    blackFerz = QImage(":/blackFerz.png");
    blackKon = QImage(":/blackKon.png");
    blackLadia = QImage(":/blackLadia.png");
    blackSlon = QImage(":/blackSlon.png");

    whiteKing = QImage(":/whiteKing.png");
    whitePeshka = QImage(":/whitePeshka.png");
    whiteFerz = QImage(":/whiteFerz.png");
    whiteKon = QImage(":/whiteKon.png");
    whiteLadia = QImage(":/whiteLadia.png");
    whiteSlon = QImage(":/whiteSlon.png");

    pawTrans = new PawTrans(this);
    pawTrans->hide();
    last = 64;
    targeted = 64;
    storona = 0;
    connect(pawTrans, SIGNAL(figureChosed(char)), this, SLOT(afterPawTrans(char)));
    connect(this, SIGNAL(pawOnOtherSide()), pawTrans, SLOT(activ()));
    connect(pawTrans, SIGNAL(figureChosed(char)), this, SIGNAL(pawChanged(char)));
}

void Bord::bordChng(char current) {
    char bufa = storona;
    if ((positions.type[current] != 0) && (positions.color[current] == storona)
            && ((whiteOpen && (storona == 0)) || (blackOpen && (storona == 1)))) {
        for(int i = 0; i < 64; i++) {
            masView[i] = 0;
        }
        masView[current] = masView[current] | SELECTED;
        MyVec<char> vec = boardLogic.steps(current);
        for(; vec.lastNum() >= 0;) {
            int num = vec.pop();
            masView[num] = masView[num] | MOZHNO;
        }
        targeted = current;
    }
    else if(targeted != 64) {
        MyVec<char> vec = boardLogic.steps(targeted);
        if (vec.pos(current) != -1) {    
                int res = moveFig(targeted, current);
                if ((res == 0) || (res == 4)) {
                    storona = !storona;
                    emit moved(targeted, current);
                    if (boardLogic.thisIsVictory(boardLogic.kingPos(1 - bufa))) {
                        qDebug() << "Victory!";
                        emit victory(0, 0);
                    }
                }

        }
        for(int i = 0; i < 64; i++) {
            masView[i] = 0;
        }
        targeted = 64;
    }
    update();

}

void Bord::mouseReleaseEvent(QMouseEvent* event) {
    int x = (event->x() << 3) / width();
    int y = (event->y() << 3) / height();
    int current = x + (y << 3);
    bordChng(current);
}

void Bord::paintEvent(QPaintEvent *) {
    pawTrans->setGeometry(width() * 0.1, height() * 0.1 , width() * 0.8, height() * 0.8);
    QPainter painter(this);
    bool b = true;
    int r_w = (width()-1)/8;
    int r_h = (height()-1)/8;
    QImage blackKing2 = blackKing.scaled(0.9*r_w,0.9*r_h);
    QImage blackKon2 = blackKon.scaled(0.9*r_w,0.9*r_h);
    QImage blackLadia2 = blackLadia.scaled(0.9*r_w,0.9*r_h);
    QImage blackPeshka2 = blackPeshka.scaled(0.9*r_w,0.9*r_h);
    QImage blackFerz2 = blackFerz.scaled(0.9*r_w,0.9*r_h);
    QImage blackSlon2 = blackSlon.scaled(0.9*r_w,0.9*r_h);
    QImage whiteKing2 = whiteKing.scaled(0.9*r_w,0.9*r_h);
    QImage whiteKon2 = whiteKon.scaled(0.9*r_w,0.9*r_h);
    QImage whiteLadia2 = whiteLadia.scaled(0.9*r_w,0.9*r_h);
    QImage whitePeshka2 = whitePeshka.scaled(0.9*r_w,0.9*r_h);
    QImage whiteFerz2 = whiteFerz.scaled(0.9*r_w,0.9*r_h);
    QImage whiteSlon2 = whiteSlon.scaled(0.9*r_w,0.9*r_h);
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            QColor color = b?QColor(255,255,232):QColor(81,37,2);
            if (i + (j << 3) == targeted) {
                painter.setBrush(Qt::blue);
            }
            else {
                painter.setBrush(color);

            }
            if (masView[i+j*8] & MOZHNO) {
                painter.setBrush(QColor(20,200,20,100));
            }
            painter.drawRect(i*r_w,j*r_h,r_w,r_h);
            if (positions.type[i+j*8] != 0) {

                QColor color2 = (positions.color[i + j*8])?QColor(30,35,51):QColor(199,254,209);
                painter.setBrush(color2);
                painter.setPen(color2);
                switch (positions.type[i + (j << 3)]) {
                case LADIA: positions.color[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackLadia2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteLadia2);
                    break;
                case KON:  positions.color[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackKon2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteKon2);
                    break;
                case SLON:  positions.color[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackSlon2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteSlon2);
                    break;
                case FERZ:  positions.color[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackFerz2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteFerz2);
                    break;
                case KOROL: positions.color[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackKing2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteKing2);
                    break;
                case PESHKA: positions.color[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackPeshka2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whitePeshka2);
                    break;

                default:
                    break;
                }
                if(masView[i + j*8] & VRAG) {
                    painter.setBrush(Qt::red);
                    painter.setPen(Qt::red);
                    painter.drawEllipse((i+0.3)*r_w,(j+0.3)*r_h,0.4*r_w,0.4*r_h);
                }
                painter.setPen(QColor(0,0,0));
            }

            b = !b;
        }
        b = !b;

    }
}
