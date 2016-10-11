#ifndef MYBOARDLOGIC_H
#define MYBOARDLOGIC_H
#include <memory.h>
#include "myvec.h"

const char  MOZHNO  =   0b00000010;
const char VRAG =       0b00000100;


struct ChessPositions {
    char type[64];
    char color[64];
    ChessPositions(){}
    ChessPositions(const ChessPositions& oth) {
        memcpy(this->type, oth.type, sizeof(this->type));
        memcpy(this->color, oth.color, sizeof(this->color));
    }
    QString toString() {
        QString out;
        for(int i = 0; i < 8; i++)
        {
            out += "text mas \n";
            for (int j = 0; j < 8; j++)
            {
                out += QString::number(type[8*i + j]);
                out += ' ';
            }
            out += "\n";
        }
    }
};

class MyBoardLogic
{
private:
    MyVec<Step> history;
    char blackKingPos;
    char curColor{0};
    char hodil[64]{{0}};
    char sto[64];
    char mas[64];
    char masBuf[64];
    char stoBuf[64];
    char target{64};
    inline bool isEmpty(char _pos) {return mas[_pos] == 0;}
    inline bool isNotEmpty(char _pos) {return mas[_pos] != 0;}
    inline bool isRival(char pos1, char pos2) {return sto[pos1] != sto[pos2];}


public:

    bool podUdarom(char pos);
    void backStep();

    char kingPos(char kingColor);
    ChessPositions getPositions() {
        ChessPositions positions;
        memcpy(positions.type, mas, 64);
        memcpy(positions.color, sto, 64);
        return positions;
    }

    int pawTrans(char chosed) {
        mas[target] = chosed;
        target = 64;
        curColor = 1 - curColor;
        return 0;
    }
    char getCurColor() {
        return curColor;
    }

    MyBoardLogic();
    MyVec<char> steps(char pos);
    int moveFig(char pos1, char pos2, bool b = true);
    bool thisIsVictory(char pos);
};

#endif // MYBOARDLOGIC_H
