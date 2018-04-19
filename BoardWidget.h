#ifndef BORD_H
#define BORD_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <PawTransWidget.h>
#include <QBitmap>
#include <QPixmap>
#include "MyVec.h"
#include "MyBoardLogic.h"
#include "Models.h"

const char SELECTED = 0b00000001;

class BordWidget:public QWidget
{
    Q_OBJECT
public:
    BordWidget(QWidget *parent = 0);

    void setColor(char color) {
        if (color == 0) {
            whiteOpen = true;
            blackOpen = false;
        }
        else if (color == 1){
            whiteOpen = false;
            blackOpen = true;
        }
    }

    void restart() {
        last = 64;
        targeted = 64;
        storona = 0;
        boardLogic = MyBoardLogic();
        positions = boardLogic.getPositions();
        whiteOpen = false;
        blackOpen = false;
        update();
    }
    void bordChng(char current);
signals:
    void moved(FigurePos, FigurePos);
    void pawOnOtherSide();
    void pawChanged(char);
    void victory(char, char);
    void defeat(char, char);
public slots:
    void chngSto() {
        storona = !storona;
    }

    void afterPawTrans(char chosed) {

        if(boardLogic.pawTrans(chosed)) {
             emit victory(0, 0);
        }
        positions = boardLogic.getPositions();
        update();
    }


    StepEnum moveFig(FigurePos pos1, FigurePos pos2) {
        StepEnum res = boardLogic.moveFig(pos1, pos2);
        switch(res) {
        case StepEnum::PROMOTION: {
            if ((whiteOpen && !boardLogic.getCurColor()) || (blackOpen && boardLogic.getCurColor())) {
                emit pawOnOtherSide();
            }
            break;
        }
        case StepEnum::SIMPLE_STEP: {
            positions = boardLogic.getPositions();
            update();
            break;
        }
        }
        return res;
    }

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
    QImage board;

    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *);

};

#endif // BORD_H
