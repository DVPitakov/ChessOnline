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

const unsigned char SELECTED = 0b00000001;

class BordWidget:public QWidget
{
    Q_OBJECT
public:
    BordWidget(QWidget *parent = 0);

    void setColor(Storona color);

    void restart();

    void bordChng(unsigned char current);
signals:
    void moved(FigurePos, FigurePos);
    void pawOnOtherSide();
    void pawChanged(unsigned char);
    void victory(EndCouse, unsigned char);
    void defeat(unsigned char, unsigned char);
public slots:
    void chngSto() {
        storona = !storona;
    }

    void afterPawTrans(unsigned char chosed);


    StepEnum moveFig(FigurePos pos1, FigurePos pos2);

private:
    MyBoardLogic boardLogic;
    ChessPositions positions;
    bool whiteOpen{false};
    bool blackOpen{false};
    PawTrans* pawTrans;
    unsigned char masView[64]{0};
    unsigned char targeted;
    unsigned char last;
    unsigned char storona;
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
