#include "board.h"

void Bord::bordChng(char current) {
    char bufa = storona;
    qDebug() << "storona: " << storona + 0;
    for(int i = 0; i < 64; i++) {
        masView[i] = 0;
    }
    int kingPos = 0;
    for(int i = 0; i < 64; i++) {
        if ((sto[i] == sto[current]) && (mas[i] == KOROL)) {
            kingPos = i;
            break;
        }
    }
    if ((mas[current] != 0) && (sto[current] == storona)
            && ((whiteOpen && (storona == 0)) || (blackOpen && (storona == 1)))
            && ((kingPos == current)  || !podUdarom(kingPos))) {
        masView[current] = masView[current] | SELECTED;
        MyVec<char> vec = steps(current % 8, current / 8);
        for(; vec.lastNum() >= 0;) {
            int num = vec.pop();
            masView[num] = masView[num] | MOZHNO;
        }
        MyVec<char> attac = attacers(current % 8, current / 8);
        for(; attac.lastNum() >= 0;) {
            int num = attac.pop();
            masView[num] = masView[num] | VRAG;
        }
        targeted = current;
    }
    else if(targeted != 64) {
        int kingPos = 0;
        for(int i = 0; i < 64; i++) {
            if ((sto[i] == sto[targeted]) && (mas[i] == KOROL)) {
                kingPos = i;
                break;
            }
        }
        if ((kingPos == targeted)  || !podUdarom(kingPos)) {
            qDebug() << "step";
            MyVec<char> vec = steps(targeted % 8, targeted / 8);
            if (vec.pos(current) != -1) {
                moveFig(targeted, current);
                storona = !storona;
                emit moved(targeted, current);
                for(int i = 0; i < 64; i++) {
                    masView[i] = 0;
                }
                for(int i = 0; i < 64; i++) {
                    if ((bufa != sto[i]) && (mas[i] == KOROL)) {
                        if (thisIsVictory(i)) {
                            qDebug() << "Victory!";
                            emit victory(0, 0);
                            break;
                        }
                    }
                }

            }
            targeted = 64;
        }

    }
    update();

}

void Bord::myDebug() {

    qDebug() << "mas mas:";
    for (int i = 0; i < 64; i += 8) {
        qDebug() << masBuf[i] + 0 << masBuf[i+ 1] + 0 << masBuf[i + 2] + 0 << masBuf[i + 3] + 0<< masBuf[i + 4]  + 0<< masBuf[i + 5] + 0 << masBuf[i + 6] + 0<< masBuf[i + 7] + 0 <<
                    "  " <<   mas[i] + 0 << mas[i+ 1] + 0 << mas[i + 2] + 0 << mas[i + 3] + 0<< mas[i + 4]  + 0<< mas[i + 5] + 0 << mas[i + 6] + 0<< mas[i + 7] + 0;
    }
    qDebug() << "sto mas:";
    for (int i = 0; i < 64; i += 8) {
        qDebug() << stoBuf[i] + 0 << stoBuf[i+ 1] + 0 << stoBuf[i + 2] + 0 << stoBuf[i + 3] + 0<< stoBuf[i + 4]  + 0<< stoBuf[i + 5] + 0 << stoBuf[i + 6] + 0<< stoBuf[i + 7] + 0 <<
                    "  " << sto[i] + 0 << sto[i+ 1] + 0 << sto[i + 2] + 0 << sto[i + 3] + 0<< sto[i + 4]  + 0<< sto[i + 5] + 0 << sto[i + 6] + 0<< sto[i + 7] + 0;
    }
    qDebug() << "end";
    for(int i = 0; i < 64; i++) {
        stoBuf[i] = sto[i];
        masBuf[i] = mas[i];
    }
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
            if (mas[i+j*8] != 0) {

                QColor color2 = (sto[i + j*8])?QColor(30,35,51):QColor(199,254,209);
                painter.setBrush(color2);
                painter.setPen(color2);
                switch (mas[i + (j << 3)]) {
                case LADIA: sto[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackLadia2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteLadia2);
                    break;
                case KON:  sto[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackKon2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteKon2);
                    break;
                case SLON:  sto[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackSlon2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteSlon2);
                    break;
                case FERZ:  sto[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackFerz2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteFerz2);
                    break;
                case KOROL: sto[i + (j << 3)]?
                                painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, blackKing2):painter.drawImage((i+0.1)*r_w,(j+0.1)*r_h, whiteKing2);
                    break;
                case PESHKA: sto[i + (j << 3)]?
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

Bord::Bord(QWidget* parent):QWidget(parent)
{
    for (int i = 0; i < 64; i++) {
        masBuf[i] = startMas[i];
        stoBuf[i] = startSto[i];
    }
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

    qDebug() << king;
    pawTrans = new PawTrans(this);
    pawTrans->hide();
    for(int i = 0; i < 64; i++) {
        mas[i] = 0;
        masView[i] = 0;
        hodil[i] = 0;
        sto[i] = startSto[i];
    }
    last = 64;
    targeted = 64;
    storona = 0;
    startBoard();
    connect(pawTrans, SIGNAL(figureChosed(char, char)), this, SLOT(afterPawTrans(char, char)));
    connect(this, SIGNAL(pawOnOtherSide(char)), pawTrans, SLOT(activ(char)));
    connect(pawTrans, SIGNAL(figureChosed(char, char)), this, SIGNAL(pawChanged(char, char)));
}

void Bord::backStep() {
    Step st= history.pop();
    mas[st._posOld] = mas[st._posNew];
    if(st._eaten) {
        mas[st._posNew] = st._eaten;
        sto[st._posOld] = st._storona;
        sto[st._posNew] = 1 - st._storona;
    }
    else {
        mas[st._posNew] = 0;
    }
}

int Bord::moveFig(int pos1, int pos2) {
    qDebug() << "pos1:" << pos1 + 0 << "pos2:" << pos2 + 0;
    history.push(Step(pos1, pos2, sto[pos1], mas[pos1], mas[pos2]));
    if ((mas[pos1] == PESHKA) && (mas[pos2] == 0) && (pos2 - pos1 != 8) && (pos1 - pos2 !=8) && (pos2 - pos1 != 16) && (pos1 - pos2 !=16)) {
        int len;
        if (sto[pos1]) len = + 8; else len = - 8;
        if (mas[pos2 + len] == PESHKA) {
            mas[pos2 + len] = 0;
            sto[pos2 + len] = 0;
        }

    }
    if ((mas[pos1] == PESHKA) && (((pos2 / 8 == 0) &&  blackOpen)|| ((pos2 / 8 == 7) && whiteOpen))) {
        emit pawOnOtherSide(pos2);
    }
    if ((mas[pos1] == KOROL) && ((pos2 - pos1) == 2)) {
        hodil[pos1 + 3] = 1;
        mas[pos2] = mas[pos1];
        mas[pos1] = 0;
        mas[pos1 + 1] = mas[pos1 + 3];
        mas[pos1 + 3] = 0;
    }
    else {
        if ((mas[pos1] == KOROL) && ((pos1 - pos2) == 2)) {
            hodil[pos1 - 4] = 1;
            mas[pos2] = mas[pos1];
            mas[pos1] = 0;
            mas[pos1 - 1] = mas[pos1 - 4];
            mas[pos1 - 4] = 0;
        }
        else {
            mas[pos2] = mas[pos1];
            sto[pos2] = sto[pos1];
        }
        hodil[pos1] = 1;
        hodil[pos2] = 1;
        mas[pos1] = 0;
    }

    myDebug();
    return 0;
}

bool Bord::podUdarom(int pos) {
    int x0 = pos % 8;
    int y0 = pos / 8;
    int x1 = x0;
    int y1 = y0 << 3;
    char cend = pos - 9 * ((x0 > y0)?y0:x0);
    char cbuf;

    for (cbuf = pos - 9; cbuf >= cend && mas[cbuf] == 0; cbuf -= 9);
    if (cbuf >= cend && ((mas[cbuf]) == SLON || (mas[cbuf]) == FERZ) && isRival(cbuf)) return true;

    cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
    for (cbuf = pos + 9; cbuf <= cend && mas[cbuf] == 0; cbuf += 9);
    if (cbuf <= cend && (((mas[cbuf]) == SLON) || (mas[cbuf]) == FERZ) && isRival(cbuf)) return true;

    cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
    for (cbuf = pos + 7; cbuf <= cend && mas[cbuf] == 0; cbuf += 7);
    if (cbuf <= cend && (((mas[cbuf]) == SLON) || (mas[cbuf]) == FERZ) && isRival(cbuf)) return true;

    cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
    for (cbuf = pos - 7; cbuf >= cend && mas[cbuf] == 0; cbuf -= 7);
    if (cbuf >= cend && ((mas[cbuf] == SLON) || (mas[cbuf]) == FERZ) &&  isRival(cbuf)) return true;
    x1 = x0;
    y1 = y0 << 3;
    x1--;
    while(x1 >= 0 && (mas[x1 + y1] == 0)) x1--;
    if (x1 >= 0 && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) return true;

    x1 = x0 + 1;
    while(x1 < 8 && (mas[x1 + y1] == 0)) x1++;
    if (x1 < 8 && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) return true;

    x1 = x0;
    y1 -= 8;
    while(y1 >= 0 && (mas[x1 + y1] == 0)) y1 -= 8;
    if (y1 >= 0  && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) return true;

    y1 = y0 << 3;
    y1 += 8;
    while(y1 < 64 && (mas[x1 + y1] == 0))
        y1 += 8;
    if (y1 < 64 && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) return true;

    x1 = x0;
    y1 = y0 << 3;
    if (x1 < 7 && y1 >= 16 && ((mas[x1 + y1 - 15]) == 2) && isRival(x1 + y1 - 15)) return true;
    if (x1 > 0 && y1 >= 16 && ((mas[x1 + y1 - 17]) == 2) && isRival(x1 + y1 - 17)) return true;
    if (x1 < 6 && y1 >= 8 &&  ((mas[x1 + y1 - 6]) == 2) && isRival(x1 + y1 - 6)) return true;
    if (x1 > 1 && y1 >= 8 &&  ((mas[x1 + y1 - 10]) == 2) && isRival(x1 + y1 - 10)) return true;

    if (x1 < 7 && y1 < 48 && (((mas[x1 + y1 + 17]) == 2) && isRival(x1 + y1 + 17))) return true;
    if (x1 > 0 && y1 < 48 && (((mas[x1 + y1 + 15]) == 2) && isRival(x1 + y1 + 15))) return true;
    if (x1 < 6 && y1 < 56 && (((mas[x1 + y1 + 10]) == 2) && isRival(x1 + y1 + 10))) return true;
    if (x1 > 1 && y1 < 56 && (((mas[x1 + y1 + 6]) == 2) && isRival(x1 + y1 + 6))) return true;
    if (mas[pos] == PESHKA) {
        if (sto[pos]) {
            if ((y1 > 8) && (x1 > 0) && ((mas[pos - 9]) == PESHKA) && isRival(pos - 9)) return true;
            if ((y1 > 8) && (x1 < 7) && ((mas[pos - 7]) == PESHKA) && isRival(pos - 7)) return true;
            if (y1 == 32 && history.lastNum() != -1) {
                Step st = history.getLast();

                if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == -16 && st._posNew == pos))
                {
                    if (x0 > 0 && mas[pos - 1] == PESHKA && isRival(pos - 1)) return true;
                    if (x0 < 7 && mas[pos + 1] == PESHKA && isRival(pos + 1)) return true;

                }
            }
        }
    }
    else {
        if ((y1 < 48) && (x1 > 0) && (( mas[x1 + y1 + 7])) == PESHKA && isRival(x1 + y1 + 7)) return true;
        if ((y1 < 48) && (x1 < 7) && (( mas[x1 + y1 + 9])) == PESHKA && isRival(x1 + y1 + 9)) return true;
        if (y1 == 24 && history.lastNum() != -1) {
            Step st = history.getLast();
            if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == 16 && st._posNew == pos))
            {
                if (x0 > 0 && mas[pos - 1] == PESHKA && isRival(pos - 1)) {return true;}
                if (x0 < 7 && mas[pos + 1] == PESHKA && isRival(pos + 1)) {return true;}

            }
        }
    }
    if (x1 > 0) {
        if (( mas[pos - 1] == 5) && isRival(pos - 1)) return true;
        if (y1 > 0 && (( mas[pos - 9]) == 5) && isRival(pos - 9)) return true;
        if (y1 < 56 && (( mas[pos + 7]) == 5) &&  isRival(pos + 7))return true;
    }
    if (x1 < 7) {
        if (( mas[pos + 1] == 5) && isRival(pos + 1)) return true;
        if (y1 > 0 && (( mas[pos - 7]) == 5) && isRival(pos - 7)) return true;
        if (y1 < 56 && (( mas[pos + 9]) == 5) && isRival(pos + 9)) return true;
    }
    if (y1 > 0 && ((( mas[pos - 8]) == 5) && isRival(pos - 8))) return true;
    if (y1 < 56 && ((( mas[pos + 8]) == 5) &&isRival(pos + 8))) return true;

    return false;
}

MyVec<char> Bord::steps(int x0, int y0) {
    MyVec<char> out;
    int x1, y1;
    x1 = x0;
    y1 = y0 << 3;
    int pos = x1 + y1;
    char storona = sto[pos];
    switch (mas[pos])
    {
    case LADIA:
        x1--;
        while(x1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1--;}
        if (x1 >= 0 && (mas[x1 + y1] != 0) && storona != (sto[x1 + y1])) { out.push(x1 + y1);}

        x1 = x0 + 1;
        while(x1 < 8 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1++;}
        if (x1 < 8 && (mas[x1 + y1] != 0) && storona != (sto[x1 + y1])) {out.push(x1 + y1);}

        x1 = x0;
        y1 -= 8;
        while(y1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 -= 8;}
        if (y1 >= 0  && (mas[x1 + y1] != 0) && storona != (sto[x1 + y1])) {out.push(x1 + y1);}

        y1 = y0 << 3;
        y1 += 8;
        while(y1 < 64 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 += 8;}
        if (y1 < 64 && (mas[x1 + y1] != 0) && isRival(x1 + y1)) out.push(x1 + y1);
        break;
    case KON:
        if (x1 < 7 && y1 >= 16 && (isEmpty(x1 + y1 - 15) || isRival(x1 + y1 - 15))) out.push(x1 + y1 - 15);
        if (x1 > 0 && y1 >= 16 && (isEmpty(x1 + y1 - 17) || isRival(x1 + y1 - 17))) out.push(x1 + y1 - 17);
        if (x1 < 6 && y1 >= 8 && (isEmpty(x1 + y1 - 6) || isRival(x1 + y1 - 6))) out.push(x1 + y1 - 6);
        if (x1 > 1 && y1 >= 8 && (isEmpty(x1 + y1 - 10) || isRival(x1 + y1 - 10))) out.push(x1 + y1 - 10);

        if (x1 < 7 && y1 < 48 && (isEmpty(x1 + y1 + 17) || isRival(x1 + y1 + 17))) out.push(x1 + y1 + 17);
        if (x1 > 0 && y1 < 48 && (isEmpty(x1 + y1 + 15) || isRival(x1 + y1 + 15))) out.push(x1 + y1 + 15);
        if (x1 < 6 && y1 < 56 && (isEmpty(x1 + y1 + 10) || isRival(x1 + y1 + 10))) out.push(x1 + y1 + 10);
        if (x1 > 1 && y1 < 56 && (isEmpty(x1 + y1 + 6) ||  isRival(x1 + y1 + 6))) out.push(x1 + y1 + 6);
        break;
    case SLON: {
        char cend = pos - 9 * ((x0 > y0)?y0:x0);
        char cbuf;

        for (cbuf = pos - 9; cbuf >= cend && mas[cbuf] == 0; cbuf -= 9) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && isRival(cbuf)) out.push(cbuf);

        cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
        for (cbuf = pos + 9; cbuf <= cend && mas[cbuf] == 0; cbuf += 9) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(cbuf))) out.push(cbuf);

        cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
        for (cbuf = pos + 7; cbuf <= cend && mas[cbuf] == 0; cbuf += 7) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(cbuf))) out.push(cbuf);

        cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
        for (cbuf = pos - 7; cbuf >= cend && mas[cbuf] == 0; cbuf -= 7) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && (isRival(cbuf))) out.push(cbuf);

        break;}
    case FERZ:
    {char cend = pos - 9 * ((x0 > y0)?y0:x0);
        char cbuf;

        for (cbuf = pos - 9; cbuf >= cend && mas[cbuf] == 0; cbuf -= 9) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && (isRival(cbuf))) out.push(cbuf);

        cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
        for (cbuf = pos + 9; cbuf <= cend && mas[cbuf] == 0; cbuf += 9) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(cbuf))) out.push(cbuf);

        cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
        for (cbuf = pos + 7; cbuf <= cend && mas[cbuf] == 0; cbuf += 7) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(cbuf))) out.push(cbuf);

        cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
        for (cbuf = pos - 7; cbuf >= cend && mas[cbuf] == 0; cbuf -= 7) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && (isRival(cbuf))) out.push(cbuf);
        x1--;
        while(x1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1--;}
        if (x1 >= 0 && (mas[x1 + y1] != 0) && storona != (sto[x1 + y1])) {out.push(x1 + y1);}

        x1 = x0 + 1;
        while(x1 < 8 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1++;}
        if (x1 < 8 && (mas[x1 + y1] != 0) && storona != (sto[x1 + y1])) {out.push(x1 + y1);}

        x1 = x0;
        y1 -= 8;
        while(y1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 -= 8;}
        if (y1 >= 0  && (mas[x1 + y1] != 0) && storona != (sto[x1 + y1])) {out.push(x1 + y1);}

        y1 = y0 << 3;
        y1 += 8;
        while(y1 < 64 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 += 8;}
        if (y1 < 64 && (mas[x1 + y1] != 0) && storona != (sto[x1 + y1])) {out.push(x1 + y1);}
        break;}
    case KOROL:
        if((hodil[pos] == 0) && hodil[pos + 3] == 0
                && mas[pos + 1] == 0 && mas[pos + 2] == 0
                && !podUdarom(pos) && !podUdarom(pos - 1) && !podUdarom(pos + 2)) {
            out.push(pos + 2);
        }
        if((hodil[pos] == 0) && hodil[pos - 4] == 0
                && mas[pos - 1] == 0 && mas[pos - 2] == 0 && mas[pos - 3] == 0
                && !podUdarom(pos) && !podUdarom(pos - 1) && !podUdarom(pos - 2))
            out.push(pos - 2);
        if (x1 > 0) {
            if (((mas[pos - 1] == 0) || isRival(pos - 1)) && !podUdarom(pos - 1)) out.push(pos - 1);
            if (y1 > 0 && ((mas[pos - 9] == 0) || (isRival(pos - 9)))  && !podUdarom(pos - 9)) out.push(pos - 9);
            if (y1 < 56 && ((mas[pos + 7] == 0) || (isRival(pos + 7)))  && !podUdarom(pos + 7)) out.push(pos + 7);
        }
        if (x1 < 7) {
            if (((mas[pos + 1] == 0) || isRival(pos + 1))  && !podUdarom(pos + 1)) out.push(pos + 1);
            if (y1 > 0 && ((mas[pos - 7] == 0) || isRival(pos - 7))  && !podUdarom(pos - 7)) out.push(pos - 7);
            if (y1 < 56 && ( (mas[pos + 9] == 0) || isRival(pos + 9))  && !podUdarom(pos + 9)) out.push(pos + 9);
        }
        if (y1 > 0 && (mas[pos - 8] == 0 ||  isRival(pos - 8))  && !podUdarom(pos - 8)) out.push(pos - 8);
        if (y1 < 56 && (mas[pos + 8] == 0 ||isRival(pos + 8))  && !podUdarom(pos + 8)) out.push(pos + 8);

        break;
    case PESHKA:

        if (sto[x1 + y1] == 1) {
            if (y1 == 48 && mas[pos - 8] == 0 && mas[pos - 16] == 0) out.push(pos - 16);
            if ((y1 > 7) && mas[x1 + y1 - 8] == 0) out.push(x1 + y1 - 8);
            if ((y1 > 7) && (x1 < 7) && mas[x1 + y1 - 7] != 0 && !(sto[x1 + y1 - 7])) out.push(x1 + y1 - 7);
            if ((y1 > 7) && (x1 > 0) && mas[x1 + y1 - 9] != 0 && !(sto[x1 + y1 - 9])) out.push(x1 + y1 - 9);
            if (y1 == 24 && history.lastNum() != -1) {
                Step st = history.getLast();
                if ((st._figura == PESHKA) && (st._posNew - st._posOld  == 16)
                        && ((x0 < 7 && st._posNew - pos == 1) || (x0 > 0 && pos -st._posNew == 1))) {
                    out.push(st._posNew - 8);
                }
            }
        }
        else {
            if (y1 == 8 && mas[pos + 8] == 0
                    && mas[pos + 16] == 0) out.push(pos + 16);
            if ((y1 < 56) && mas[x1 + y1 + 8] == 0) out.push(x1 + y1 + 8);
            if ((y1 < 56) && (x1 < 7) && mas[x1 + y1 + 9] != 0 && (sto[x1 + y1 + 9])) out.push(x1 + y1 + 9);
            if ((y1 < 56) && (x1 > 0) && mas[x1 + y1 + 7] != 0 && (sto[x1 + y1 + 7])) out.push(x1 + y1 + 7);
            if (y1 == 32 && history.lastNum() != -1) {
                Step st = history.getLast();
                if ((st._figura == PESHKA) && (st._posOld - st._posNew  == 16)
                        && ((x0 < 7 && st._posNew - pos == 1) || (x0 > 0 && pos -st._posNew == 1))) {
                    out.push(st._posNew + 8);
                }
            }
        }
        break;
    default: break;
    }
   for(int i = 0; i <= out.lastNum(); i++) {
       qDebug() << "myVec: " << out.buf[i] + 0;
   }
    return out;
}

MyVec<char> Bord::attacers(int x0, int y0) {
    MyVec<char>out;
    int x1, y1;
    x1 = x0;
    y1 = y0 << 3;
    int pos = x1 + y1;
    char storona = sto[pos];
    char cend = pos - 9 * ((x0 > y0)?y0:x0);
    char cbuf;

    for (cbuf = pos - 9; cbuf >= cend && mas[cbuf] == 0; cbuf -= 9);
    if (cbuf >= cend && ((mas[cbuf] ) == SLON || (mas[cbuf]) == FERZ) && isRival(cbuf)) out.push(cbuf);

    cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
    for (cbuf = pos + 9; cbuf <= cend && mas[cbuf] == 0; cbuf += 9);
    if (cbuf <= cend && (((mas[cbuf] ) == SLON) || (mas[cbuf]) == FERZ) && isRival(cbuf)) out.push(cbuf);

    cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
    for (cbuf = pos + 7; cbuf <= cend && mas[cbuf] == 0; cbuf += 7);
    if (cbuf <= cend && (((mas[cbuf] ) == SLON) || (mas[cbuf]) == FERZ) && isRival(cbuf)) out.push(cbuf);

    cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
    for (cbuf = pos - 7; cbuf >= cend && mas[cbuf] == 0; cbuf -= 7);
    if (cbuf >= cend && ((mas[cbuf]  == SLON) || (mas[cbuf]) == FERZ) &&  isRival(cbuf)) out.push(cbuf);
    x1 = x0;
    y1 = y0 << 3;
    x1--;
    while(x1 >= 0 && (mas[x1 + y1] == 0)) x1--;
    if (x1 >= 0 && (( mas[x1 + y1]) == LADIA || ( mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) out.push(x1 + y1);

    x1 = x0 + 1;
    while(x1 < 8 && (mas[x1 + y1] == 0)) x1++;
    if (x1 < 8 && (( mas[x1 + y1]) == LADIA || ( mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) out.push(x1 + y1);

    x1 = x0;
    y1 -= 8;
    while(y1 >= 0 && (mas[x1 + y1] == 0)) y1 -= 8;
    if (y1 >= 0  && (( mas[x1 + y1]) == LADIA || ( mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) out.push(x1 + y1);

    y1 = y0 << 3;
    y1 += 8;
    while(y1 < 64 && (mas[x1 + y1] == 0))
        y1 += 8;
    if (y1 < 64 && (( mas[x1 + y1]) == LADIA || ( mas[x1 + y1]) == FERZ) && isRival(x1 + y1)) out.push(x1 + y1);

    x1 = x0;
    y1 = y0 << 3;
    if (x1 < 7 && y1 >= 16 && (( mas[x1 + y1 - 15]) == 2) && isRival(x1 + y1 - 15)) out.push(x1 + y1 - 15);
    if (x1 > 0 && y1 >= 16 && (( mas[x1 + y1 - 17]) == 2) && isRival(x1 + y1 - 17)) out.push(x1 + y1 - 17);
    if (x1 < 6 && y1 >= 8 &&  (( mas[x1 + y1 - 6]) == 2) && isRival(x1 + y1 - 6)) out.push(x1 + y1 - 6);
    if (x1 > 1 && y1 >= 8 &&  (( mas[x1 + y1 - 10]) == 2) && isRival(x1 + y1 - 10)) out.push(x1 + y1 - 10);

    if (x1 < 7 && y1 < 48 && ((( mas[x1 + y1 + 17]) == 2) && isRival(x1 + y1 + 17))) out.push(x1 + y1 + 17);
    if (x1 > 0 && y1 < 48 && ((( mas[x1 + y1 + 15]) == 2) && isRival(x1 + y1 + 15))) out.push(x1 + y1 + 15);
    if (x1 < 6 && y1 < 56 && ((( mas[x1 + y1 + 10]) == 2) && isRival(x1 + y1 + 10))) out.push(x1 + y1 + 10);
    if (x1 > 1 && y1 < 56 && ((( mas[x1 + y1 + 6]) == 2) && isRival(x1 + y1 + 6))) out.push(x1 + y1 + 6);

    if (sto[pos]) {
        if ((y1 > 8) && (x1 > 0) && (( mas[pos - 9]) == PESHKA) && isRival(pos - 9)) out.push(x1 + y1 - 9);
        if ((y1 > 8) && (x1 < 7) && (( mas[pos - 7]) == PESHKA) && isRival(pos - 7)) out.push(x1 + y1 - 7);
        if (y1 == 32 && history.lastNum() != -1) {
            Step st = history.getLast();
            if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == -16 && st._posNew == pos))
            {
                if (x0 > 0 && mas[pos - 1] == PESHKA && isRival(pos - 1)) {out.push(pos - 1);}
                if (x0 < 7 && mas[pos + 1] == PESHKA && isRival(pos + 1)) {out.push(pos + 1);}

            }
        }

    }
    else {
        if ((y1 < 48) && (x1 > 0) && (( mas[x1 + y1 + 7])) == PESHKA && isRival(x1 + y1 + 7)) out.push(x1 + y1 + 7);
        if ((y1 < 48) && (x1 < 7) && (( mas[x1 + y1 + 9])) == PESHKA && isRival(x1 + y1 + 9)) out.push(x1 + y1 + 9);
        if (y1 == 24 && history.lastNum() != -1) {
            Step st = history.getLast();
            if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == 16 && st._posNew == pos))
            {
                if (x0 > 0 && mas[pos - 1] == PESHKA && isRival(pos - 1)) {out.push(pos - 1);}
                if (x0 < 7 && mas[pos + 1] == PESHKA && isRival(pos + 1)) {out.push(pos + 1);}

            }
        }
    }
    if (x1 > 0) {
        if (( mas[pos - 1] == 5) && isRival(pos - 1)) out.push(pos - 1);
        if (y1 > 0 && (( mas[pos - 9]) == 5) && isRival(pos - 9)) out.push(pos - 9);
        if (y1 < 56 && (( mas[pos + 7]) == 5) &&  isRival(pos + 7)) out.push(pos + 7);
    }
    if (x1 < 7) {
        if (( mas[pos + 1] == 5) && isRival(pos + 1)) out.push(pos + 1);
        if (y1 > 0 && (( mas[pos - 7]) == 5) && isRival(pos - 7)) out.push(pos - 7);
        if (y1 < 56 && (( mas[pos + 9]) == 5) && isRival(pos + 9)) out.push(pos + 9);
    }
    if (y1 > 0 && ((( mas[pos - 8]) == 5) && isRival(pos - 8))) out.push(pos - 8);
    if (y1 < 56 && ((( mas[pos + 8]) == 5) &&isRival(pos + 8))) out.push(pos + 8);

    return out;
}
