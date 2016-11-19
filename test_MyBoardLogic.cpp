#include "test_MyBoardLogic.h"
#include <MyBoardLogic.h>
#include <QTest>

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
const char moved[] =    {0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0};

test_MyBoardLogic::test_MyBoardLogic(QObject *parent):QObject(parent)
{

    MyBoardLogic boardLogic;
    //ChessPositions p1 = boardLogic.getPositions();
   // ChessPositions p2 =  ChessPositions(startMas, startSto);
   // QCOMPARE(p1, p2);
}

