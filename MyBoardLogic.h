#ifndef MYBOARDLOGIC_H
#define MYBOARDLOGIC_H

#include <memory.h>
#include <memory>
#include "MyVec.h"
#include "Models.h"

const unsigned char MOZHNO = 0b00000010;
const unsigned char VRAG   = 0b00000100;
const int BOARD_FIELDS_COUNT = 64;

enum class StepEnum {
    SIMPLE_STEP, NOT_TARGETED_USER_OR_FREE_FIELD, KING_UNDER_ATTACK, WRONG_STEP, PROMOTION, VICTORY_STEP
};

struct Step {
    FigurePos _posOld;
    FigurePos _posNew;
    unsigned char _storona;
    unsigned char _figura;
    unsigned char _eaten;
    bool isWhite{0};

    Step(unsigned char posOld, unsigned char posNew, unsigned char storona = 3, unsigned char figura = 0, unsigned char eaten = 0):
        _posOld(posOld),_posNew(posNew),_storona(storona),_figura(figura),_eaten(eaten) {}
};

struct ChessPositions {
    unsigned char type[BOARD_FIELDS_COUNT];
    unsigned char color[BOARD_FIELDS_COUNT];
    ChessPositions(){}

    ChessPositions(const ChessPositions& oth);

    ChessPositions(const unsigned char* newType64, const unsigned char* newColor64);

    bool operator==(const ChessPositions& oth) const;
};


class MyBoardLogic {
public:
    bool podUdarom(const FigurePos pos) const;
    void backStep();
    unsigned char kingPos(Storona kingColor) const;
    ChessPositions getPositions();
    int pawTrans(const unsigned char chosed);
    unsigned char getCurColor() const;
    MyBoardLogic();
    StepEnum moveFig(FigurePos pos1, FigurePos pos2, bool b = true);
    MyVec<unsigned char> steps(FigurePos pos) const;

private:
    MyVec<Step> history;
    unsigned char curColor{0};
    bool hodil[BOARD_FIELDS_COUNT]{{false}};
    Storona blackPoses[BOARD_FIELDS_COUNT];
    unsigned char figuresTypes[BOARD_FIELDS_COUNT];
    unsigned char blackPosesBuf[BOARD_FIELDS_COUNT];
    unsigned char target{BOARD_FIELDS_COUNT};

    inline bool isEmpty(const FigurePos _pos) const {return figuresTypes[_pos] == 0;}
    inline bool isNotEmpty(const FigurePos _pos) const {return figuresTypes[_pos] != 0;}
    inline bool isRival(const FigurePos pos1, const FigurePos pos2) const {return blackPoses[pos1] != blackPoses[pos2];}
    bool thisIsVictory(Storona winner);
};

#endif // MYBOARDLOGIC_H
