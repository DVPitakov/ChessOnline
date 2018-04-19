#ifndef MYBOARDLOGIC_H
#define MYBOARDLOGIC_H

#include <memory.h>
#include <memory>
#include "MyVec.h"
#include "Models.h"

const char MOZHNO = 0b00000010;
const char VRAG   = 0b00000100;
const int BOARD_FIELDS_COUNT = 64;


enum class StoronaEnum {
    WHITE, BLACK
};

enum class StepEnum {
    SIMPLE_STEP, NOT_TARGETED_USER_OR_FREE_FIELD, KING_UNDER_ATTACK, WRONG_STEP, PROMOTION, VICTORY_STEP
};

struct Step {
    char _posOld;
    char _posNew;
    char _storona;
    char _figura;
    char _eaten;
    bool isWhite{0};

    Step(char posOld, char posNew, char storona = 3, char figura = 0, char eaten = 0):
        _posOld(posOld),_posNew(posNew),_storona(storona),_figura(figura),_eaten(eaten) {}
};

struct ChessPositions {
    char type[BOARD_FIELDS_COUNT];
    char color[BOARD_FIELDS_COUNT];
    ChessPositions(){}
    ChessPositions(const ChessPositions& oth) {
        memcpy(this->type, oth.type, sizeof(this->type));
        memcpy(this->color, oth.color, sizeof(this->color));
    }
    ChessPositions(const char* newType64, const char* newColor64) {
        memcpy(this->type, newType64, sizeof(this->type));
        memcpy(this->color, newColor64, sizeof(this->color));
    }
    bool operator==(const ChessPositions& oth) {
        for(int i = 0; i  < BOARD_FIELDS_COUNT; i++) {
            if (type[i] != oth.type[i] || color[i] != oth.color[i]) {
                return false;
            }
        }
        return true;
}
};

class MyBoardLogic {
public:
    bool podUdarom(const FigurePos pos);
    void backStep();

    char kingPos(const char kingColor) const;
    ChessPositions getPositions() {
        ChessPositions positions;
        memcpy(positions.type, mas, BOARD_FIELDS_COUNT);
        memcpy(positions.color, sto, BOARD_FIELDS_COUNT);
        return positions;
    }

    int pawTrans(const char chosed) {
        mas[target] = chosed;
        target = BOARD_FIELDS_COUNT;
        curColor = 1 - curColor;
        return thisIsVictory(kingPos(curColor));
    }

    char getCurColor() const {
        return curColor;
    }

    MyBoardLogic();
    MyVec<char> steps(char pos);
    StepEnum moveFig(FigurePos pos1, FigurePos pos2, bool b = true);

private:
    MyVec<Step> history;
    char curColor{0};
    unsigned char hodil[BOARD_FIELDS_COUNT]{{0}};
    unsigned char sto[BOARD_FIELDS_COUNT];
    unsigned char mas[BOARD_FIELDS_COUNT];
    unsigned char masBuf[BOARD_FIELDS_COUNT];
    unsigned char stoBuf[BOARD_FIELDS_COUNT];
    unsigned char target{BOARD_FIELDS_COUNT};
    inline bool isEmpty(const FigurePos _pos) {return mas[_pos] == 0;}
    inline bool isNotEmpty(const FigurePos _pos) {return mas[_pos] != 0;}
    inline bool isRival(const FigurePos pos1, const FigurePos pos2) {return sto[pos1] != sto[pos2];}
    bool thisIsVictory(const char pos);
};

#endif // MYBOARDLOGIC_H
