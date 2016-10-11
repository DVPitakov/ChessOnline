#ifndef BORD_H
#define BORD_H
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <pawtrans.h>
#include <QBitmap>
#include <QPixmap>
#include "myvec.h"
#include "MyBoardLogic.h"

const char SELECTED = 0b00000001;

class Bord:public QWidget
{
    Q_OBJECT
private:
    MyBoardLogic boardLogic;
    ChessPositions positions;
    bool whiteOpen{false};
    bool blackOpen{false};
    PawTrans* pawTrans;
    char masView[64]{0};
    char targeted;
    char last;
    char storona;
    QImage blackKing;
    QImage blackKon;
    QImage blackPeshka;
    QImage blackFerz;
    QImage blackLadia;
    QImage blackSlon;
    QImage whiteKing;
    QImage whiteKon;
    QImage whitePeshka;
    QImage whiteFerz;
    QImage whiteLadia;
    QImage whiteSlon;

    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *);

public:
    Bord(QWidget *parent = 0);
    void setColor(char color) {
        if (color == 0) {
            whiteOpen = true;
        }
        else if (color == 1){
            blackOpen = true;
        }
    }


    void bordChng(char current);
signals:
    void moved(int, int);
    void pawOnOtherSide();
    void pawChanged(char);
    void victory(char, char);
    void defeat(char, char);
public slots:
    void chngSto() {
        storona = !storona;
    }

    void afterPawTrans(char chosed) {
        boardLogic.pawTrans(chosed);
        positions = boardLogic.getPositions();
        update();
    }

    int moveFig(int pos1, int pos2) {
        int res = boardLogic.moveFig(pos1, pos2);
        switch(res) {
        case 4: {
            if ((whiteOpen && !boardLogic.getCurColor()) || (blackOpen && boardLogic.getCurColor())) {
                emit pawOnOtherSide();
            }
            break;
        }
        case 0: {
            positions = boardLogic.getPositions();
            update();
            break;
        }
        }
        return res;
    }

};

#endif // BORD_H
