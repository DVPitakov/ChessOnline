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
const char SELECTED = 0b00000001;
const char  MOZHNO  = 0b00000010;
const char VRAG = 0b00000100;
const char POD_UDAROM = 0b00000100;



const char startMas[] = {1,2,3,4,5,3,2,1,
                         6,6,6,6,6,6,6,6,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         6,6,6,6,6,6,6,6,
                         1,2,3,4,5,3,2,1};

const char startSto[] = {0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         1,1,1,1,1,1,1,1,
                         1,1,1,1,1,1,1,1};
class Bord:public QWidget
{
    Q_OBJECT
private:
    bool whiteOpen{false};
    bool blackOpen{false};
#define isRival(pos) ((sto[pos]) != storona)
    QImage *king;
    inline bool isEmpty(char _pos) {return mas[_pos] == 0;}
    inline bool isNotEmpty(char _pos) {return mas[_pos] != 0;}
    PawTrans* pawTrans;
    char masView[64];
    char mas[64];
    char hodil[64];
    char sto[64];
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
    MyVec<Step>history;
    char masBuf[64];
    char stoBuf[64];
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

    void backStep();

    void bordChng(char current);
signals:
    void moved(int, int);
    void pawOnOtherSide(char);
    void pawChanged(char, char);
    void victory(char, char);
public slots:
    void chngSto() {
            storona = !storona;
    }

    void afterPawTrans(char chosed, char pos) {
        mas[pos] = chosed;
        pawTrans->hide();
        update();
    }

    void setBord(char* arr) {
        memcpy(mas, arr, 64);
        update();
    }
    void startBoard() {
        memcpy(mas, startMas, 64);

    }

    void myDebug();

    bool thisIsVictory(char pos) {

        if (!podUdarom(pos)) {

            for(int i = 0; i < 64; i++) {
                if ((sto[i] == sto[pos]) && mas[i]) {
                    MyVec<char> vec = steps(i % 8, i /8);
                    if (vec.lastNum() != -1) {
                        return false;
                    }
                }
            }

        }
        else {
            MyVec<char> vecs = steps(pos % 8, pos /8);
            if (vecs.lastNum() != - 1) {
                qDebug() << "becouse step is enable: from:" << pos + 0 + "to: " << vecs.pop();
                return false;
            }
            for(int i = 0; i < 64; i++) {
                if ((sto[i] == sto[pos]) && mas[i] && (i != pos)) {
                    MyVec<char> vec = steps(i % 8, i /8);
                    while(vec.lastNum() >= 0) {
                        char posa = vec.pop();
                        moveFig(i, posa);
                        if (!podUdarom(pos)) {
                            backStep();
                            qDebug() << "becouse step is enable: from:" << i + 0 << "to: " << posa;
                            return false;
                        }
                        else {
                             backStep();
                        }
                    }
                }
            }
        }

        return true;
    }

    int moveFig(int pos1, int pos2);
    bool podUdarom(int pos);
    MyVec<char> attacers(int x0, int y0);
    MyVec<char> steps(int x0, int y0);
};

#endif // BORD_H
