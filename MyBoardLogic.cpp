#include "MyBoardLogic.h"
#include <QDebug>

const char LADIA = 1;
const char KON = 2;
const char SLON = 3;
const char FERZ = 4;
const char KOROL = 5;
const char PESHKA = 6;

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

char MyBoardLogic::kingPos(const char kingColor) const {
    for(int i = 0; i < 64; i++) {
        if ((figuresTypes[i] == KOROL) && (whitePoses[i] == kingColor)) {
            return i;
        }
    }
}

MyBoardLogic::MyBoardLogic() {
    memcpy(figuresTypes, startMas, 64);
    memcpy(whitePoses, startSto, 64);
    memcpy(figuresTypesBuf, startMas, 64);
    memcpy(whitePosesBuf, startSto, 64);
}

void MyBoardLogic::backStep() {
    Step st = history.pop();
    figuresTypes[st._posOld] = figuresTypes[st._posNew];
    if(st._eaten) {
        figuresTypes[st._posNew] = st._eaten;
        whitePoses[st._posOld] = st._storona;
        whitePoses[st._posNew] = 1 - st._storona;
    }
    else {
        figuresTypes[st._posNew] = 0;
    }

}


StepEnum MyBoardLogic::moveFig(FigurePos posOne, FigurePos posTwo, bool b) {
    if (target != 64  || (whitePoses[posOne] != curColor)) {
        return StepEnum::WRONG_STEP;
    }
    if ((figuresTypes[posOne] == 0)) return StepEnum::NOT_TARGETED_USER_OR_FREE_FIELD;
    MyVec<char> avaliable = steps(posOne);
    if (avaliable.pos(posTwo) == -1) { return StepEnum::WRONG_STEP;}
    history.push(Step(posOne, posTwo, whitePoses[posOne], figuresTypes[posOne], figuresTypes[posTwo]));
    if ((figuresTypes[posOne] == PESHKA) && (figuresTypes[posTwo] == 0) && (posTwo - posOne != 8) && (posOne - posTwo !=8) && (posTwo - posOne != 16) && (posOne - posTwo !=16)) {
        int len;
        if (whitePoses[posOne]) len = + 8; else len = - 8;
        if (figuresTypes[posTwo + len] == PESHKA) {
            figuresTypes[posTwo + len] = 0;
            whitePoses[posTwo + len] = 0;
        }

    }
    if ((figuresTypes[posOne] == PESHKA) && (((posTwo / 8 == 0) &&  (curColor))|| ((posTwo / 8 == 7) && (!curColor)))) {
    }
    if ((figuresTypes[posOne] == KOROL) && ((posTwo - posOne) == 2)) {

        hodil[posOne + 3] = true;
        figuresTypes[posTwo] = figuresTypes[posOne];
        figuresTypes[posOne] = 0;
        figuresTypes[posOne + 1] = figuresTypes[posOne + 3];
        figuresTypes[posOne + 3] = 0;
    }
    else {
        if ((figuresTypes[posOne] == KOROL) && ((posOne - posTwo) == 2)) {
            hodil[posOne - 4] = true;
            figuresTypes[posTwo] = figuresTypes[posOne];
            figuresTypes[posOne] = 0;
            figuresTypes[posOne - 1] = figuresTypes[posOne - 4];
            figuresTypes[posOne - 4] = 0;
        }
        else {
            figuresTypes[posTwo] = figuresTypes[posOne];
            whitePoses[posTwo] = whitePoses[posOne];
        }
        hodil[posOne] = true;
        hodil[posTwo] = true;
        figuresTypes[posOne] = 0;
    }
    if (podUdarom(kingPos(curColor))) {
        backStep();
        return StepEnum::KING_UNDER_ATTACK;
    }

    if (b && (figuresTypes[posTwo] == PESHKA) && (((posTwo / 8) == 0) || ((posTwo / 8) == 7))) {
        target = posTwo;
        return StepEnum::PROMOTION;
    }
    if (thisIsVictory(kingPos(1 - curColor))) {
        return StepEnum::VICTORY_STEP;
    }
    curColor = 1 - curColor;
    return StepEnum::SIMPLE_STEP;
}

bool MyBoardLogic::podUdarom(const FigurePos pos1) {
    int x0 = pos1 % 8;
    int y0 = pos1 / 8;
    int x1 = x0;
    int y1 = y0 << 3;
    char pos = pos1;
    char cend = pos - 9 * ((x0 > y0)?y0:x0);
    char cbuf;

    for (cbuf = pos - 9; cbuf >= cend && figuresTypes[cbuf] == 0; cbuf -= 9);
    if (cbuf >= cend && ((figuresTypes[cbuf]) == SLON || (figuresTypes[cbuf]) == FERZ) && isRival(pos,cbuf)) return true;

    cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
    for (cbuf = pos + 9; cbuf <= cend && figuresTypes[cbuf] == 0; cbuf += 9);
    if (cbuf <= cend && (((figuresTypes[cbuf]) == SLON) || (figuresTypes[cbuf]) == FERZ) && isRival(pos,cbuf)) return true;

    cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
    for (cbuf = pos + 7; cbuf <= cend && figuresTypes[cbuf] == 0; cbuf += 7);
    if (cbuf <= cend && (((figuresTypes[cbuf]) == SLON) || (figuresTypes[cbuf]) == FERZ) && isRival(pos,cbuf)) return true;

    cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
    for (cbuf = pos - 7; cbuf >= cend && figuresTypes[cbuf] == 0; cbuf -= 7);
    if (cbuf >= cend && ((figuresTypes[cbuf] == SLON) || (figuresTypes[cbuf]) == FERZ) &&  isRival(pos,cbuf)) return true;
    x1 = x0;
    y1 = y0 << 3;
    x1--;
    while(x1 >= 0 && (figuresTypes[x1 + y1] == 0)) x1--;
    if (x1 >= 0 && ((figuresTypes[x1 + y1]) == LADIA || (figuresTypes[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    x1 = x0 + 1;
    while(x1 < 8 && (figuresTypes[x1 + y1] == 0)) x1++;
    if (x1 < 8 && ((figuresTypes[x1 + y1]) == LADIA || (figuresTypes[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    x1 = x0;
    y1 -= 8;
    while(y1 >= 0 && (figuresTypes[x1 + y1] == 0)) y1 -= 8;
    if (y1 >= 0  && ((figuresTypes[x1 + y1]) == LADIA || (figuresTypes[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    y1 = y0 << 3;
    y1 += 8;
    while(y1 < 64 && (figuresTypes[x1 + y1] == 0))
        y1 += 8;
    if (y1 < 64 && ((figuresTypes[x1 + y1]) == LADIA || (figuresTypes[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    x1 = x0;
    y1 = y0 << 3;
    if (x1 < 7 && y1 >= 16 && ((figuresTypes[x1 + y1 - 15]) == 2) && isRival(pos,x1 + y1 - 15)) return true;
    if (x1 > 0 && y1 >= 16 && ((figuresTypes[x1 + y1 - 17]) == 2) && isRival(pos,x1 + y1 - 17)) return true;
    if (x1 < 6 && y1 >= 8 &&  ((figuresTypes[x1 + y1 - 6]) == 2) && isRival(pos,x1 + y1 - 6)) return true;
    if (x1 > 1 && y1 >= 8 &&  ((figuresTypes[x1 + y1 - 10]) == 2) && isRival(pos,x1 + y1 - 10)) return true;

    if (x1 < 7 && y1 < 48 && (((figuresTypes[x1 + y1 + 17]) == 2) && isRival(pos,x1 + y1 + 17))) return true;
    if (x1 > 0 && y1 < 48 && (((figuresTypes[x1 + y1 + 15]) == 2) && isRival(pos,x1 + y1 + 15))) return true;
    if (x1 < 6 && y1 < 56 && (((figuresTypes[x1 + y1 + 10]) == 2) && isRival(pos,x1 + y1 + 10))) return true;
    if (x1 > 1 && y1 < 56 && (((figuresTypes[x1 + y1 + 6]) == 2) && isRival(pos,x1 + y1 + 6))) return true;

    if (whitePoses[pos]) {
        if ((y1 > 8) && (x1 > 0) && ((figuresTypes[pos - 9]) == PESHKA) && isRival(pos, pos - 9)) return true;
        if ((y1 > 8) && (x1 < 7) && ((figuresTypes[pos - 7]) == PESHKA) && isRival(pos, pos - 7)) return true;
        if (figuresTypes[pos] == PESHKA) {
            if (y1 == 32 && history.lastNum() != -1) {
                Step st = history.getLast();

                if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == -16 && st._posNew == pos))
                {
                    if (x0 > 0 && figuresTypes[pos - 1] == PESHKA && isRival(pos,pos - 1)) return true;
                    if (x0 < 7 && figuresTypes[pos + 1] == PESHKA && isRival(pos,pos + 1)) return true;

                }
            }
        }
    }
    else {
        if ((y1 < 48) && (x1 > 0) && (( figuresTypes[x1 + y1 + 7])) == PESHKA && isRival(pos,x1 + y1 + 7)) return true;
        if ((y1 < 48) && (x1 < 7) && (( figuresTypes[x1 + y1 + 9])) == PESHKA && isRival(pos,x1 + y1 + 9)) return true;
        if (figuresTypes[pos] == PESHKA) {
            if (y1 == 24 && history.lastNum() != -1) {
                Step st = history.getLast();
                if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == 16 && st._posNew == pos))
                {
                    if (x0 > 0 && figuresTypes[pos - 1] == PESHKA && isRival(pos,pos - 1)) {return true;}
                    if (x0 < 7 && figuresTypes[pos + 1] == PESHKA && isRival(pos,pos + 1)) {return true;}

                }
            }
        }
    }


    if (x1 > 0) {
        if (( figuresTypes[pos - 1] == 5) && isRival(pos,pos - 1)) return true;
        if (y1 > 0 && (( figuresTypes[pos - 9]) == 5) && isRival(pos,pos - 9)) return true;
        if (y1 < 56 && (( figuresTypes[pos + 7]) == 5) &&  isRival(pos,pos + 7))return true;
    }
    if (x1 < 7) {
        if (( figuresTypes[pos + 1] == 5) && isRival(pos,pos + 1)) return true;
        if (y1 > 0 && (( figuresTypes[pos - 7]) == 5) && isRival(pos,pos - 7)) return true;
        if (y1 < 56 && (( figuresTypes[pos + 9]) == 5) && isRival(pos,pos + 9)) return true;
    }
    if (y1 > 0 && ((( figuresTypes[pos - 8]) == 5) && isRival(pos,pos - 8))) return true;
    if (y1 < 56 && ((( figuresTypes[pos + 8]) == 5) &&isRival(pos,pos + 8))) return true;

    return false;
}

MyVec<char> MyBoardLogic::steps(char pos) {
    MyVec<char> out;
    char x1, y1;
    char x0 = pos % 8;
    char y0 = pos / 8;
    x1 = x0;
    y1 = y0 << 3;
    switch (figuresTypes[pos])
    {
    case LADIA:
        x1--;
        while(x1 >= 0 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); x1--;}
        if (x1 >= 0 && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) { out.push(x1 + y1);}

        x1 = x0 + 1;
        while(x1 < 8 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); x1++;}
        if (x1 < 8 && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        x1 = x0;
        y1 -= 8;
        while(y1 >= 0 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); y1 -= 8;}
        if (y1 >= 0  && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        y1 = y0 << 3;
        y1 += 8;
        while(y1 < 64 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); y1 += 8;}
        if (y1 < 64 && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) out.push(x1 + y1);
        break;
    case KON:
        if (x1 < 7 && y1 >= 16 && (isEmpty(x1 + y1 - 15) || isRival(pos,x1 + y1 - 15))) out.push(x1 + y1 - 15);
        if (x1 > 0 && y1 >= 16 && (isEmpty(x1 + y1 - 17) || isRival(pos,x1 + y1 - 17))) out.push(x1 + y1 - 17);
        if (x1 < 6 && y1 >= 8 && (isEmpty(x1 + y1 - 6) || isRival(pos,x1 + y1 - 6))) out.push(x1 + y1 - 6);
        if (x1 > 1 && y1 >= 8 && (isEmpty(x1 + y1 - 10) || isRival(pos,x1 + y1 - 10))) out.push(x1 + y1 - 10);

        if (x1 < 7 && y1 < 48 && (isEmpty(x1 + y1 + 17) || isRival(pos,x1 + y1 + 17))) out.push(x1 + y1 + 17);
        if (x1 > 0 && y1 < 48 && (isEmpty(x1 + y1 + 15) || isRival(pos,x1 + y1 + 15))) out.push(x1 + y1 + 15);
        if (x1 < 6 && y1 < 56 && (isEmpty(x1 + y1 + 10) || isRival(pos,x1 + y1 + 10))) out.push(x1 + y1 + 10);
        if (x1 > 1 && y1 < 56 && (isEmpty(x1 + y1 + 6) ||  isRival(pos,x1 + y1 + 6))) out.push(x1 + y1 + 6);
        break;
    case SLON: {
        char cend = pos - 9 * ((x0 > y0)?y0:x0);
        char cbuf;

        for (cbuf = pos - 9; cbuf >= cend && figuresTypes[cbuf] == 0; cbuf -= 9) out.push(cbuf);
        if (cbuf >= cend && figuresTypes[cbuf] != 0 && isRival(pos,cbuf)) out.push(cbuf);

        cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
        for (cbuf = pos + 9; cbuf <= cend && figuresTypes[cbuf] == 0; cbuf += 9) out.push(cbuf);
        if (cbuf <= cend && figuresTypes[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
        for (cbuf = pos + 7; cbuf <= cend && figuresTypes[cbuf] == 0; cbuf += 7) out.push(cbuf);
        if (cbuf <= cend && figuresTypes[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
        for (cbuf = pos - 7; cbuf >= cend && figuresTypes[cbuf] == 0; cbuf -= 7) out.push(cbuf);
        if (cbuf >= cend && figuresTypes[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        break;}
    case FERZ:
    {char cend = pos - 9 * ((x0 > y0)?y0:x0);
        char cbuf;

        for (cbuf = pos - 9; cbuf >= cend && figuresTypes[cbuf] == 0; cbuf -= 9) out.push(cbuf);
        if (cbuf >= cend && figuresTypes[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
        for (cbuf = pos + 9; cbuf <= cend && figuresTypes[cbuf] == 0; cbuf += 9) out.push(cbuf);
        if (cbuf <= cend && figuresTypes[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
        for (cbuf = pos + 7; cbuf <= cend && figuresTypes[cbuf] == 0; cbuf += 7) out.push(cbuf);
        if (cbuf <= cend && figuresTypes[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
        for (cbuf = pos - 7; cbuf >= cend && figuresTypes[cbuf] == 0; cbuf -= 7) out.push(cbuf);
        if (cbuf >= cend && figuresTypes[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);
        x1--;
        while(x1 >= 0 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); x1--;}
        if (x1 >= 0 && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        x1 = x0 + 1;
        while(x1 < 8 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); x1++;}
        if (x1 < 8 && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        x1 = x0;
        y1 -= 8;
        while(y1 >= 0 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); y1 -= 8;}
        if (y1 >= 0  && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        y1 = y0 << 3;
        y1 += 8;
        while(y1 < 64 && (figuresTypes[x1 + y1] == 0)) {out.push(x1 + y1); y1 += 8;}
        if (y1 < 64 && (figuresTypes[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}
        break;}
    case KOROL:
        if((!hodil[pos]) && !hodil[pos + 3]
                && figuresTypes[pos + 1] == 0 && figuresTypes[pos + 2] == 0
                && !podUdarom(pos) && !podUdarom(pos - 1) && !podUdarom(pos + 2)) {
            out.push(pos + 2);
        }
        if((!hodil[pos]) && !hodil[pos - 4]
                && figuresTypes[pos - 1] == 0 && figuresTypes[pos - 2] == 0 && figuresTypes[pos - 3] == 0
                && !podUdarom(pos) && !podUdarom(pos - 1) && !podUdarom(pos - 2))
            out.push(pos - 2);
        if (x1 > 0) {
            if ((figuresTypes[pos - 1] == 0) || isRival(pos,pos - 1)) out.push(pos - 1);
            if (y1 > 0 && ((figuresTypes[pos - 9] == 0) || (isRival(pos,pos - 9)))) out.push(pos - 9);
            if (y1 < 56 && ((figuresTypes[pos + 7] == 0) || (isRival(pos,pos + 7)))) out.push(pos + 7);
        }
        if (x1 < 7) {
            if (((figuresTypes[pos + 1] == 0) || isRival(pos,pos + 1))) out.push(pos + 1);
            if (y1 > 0 && ((figuresTypes[pos - 7] == 0) || isRival(pos,pos - 7))) out.push(pos - 7);
            if (y1 < 56 && ( (figuresTypes[pos + 9] == 0) || isRival(pos,pos + 9))) out.push(pos + 9);
        }
        if (y1 > 0 && (figuresTypes[pos - 8] == 0 ||  isRival(pos,pos - 8))) out.push(pos - 8);
        if (y1 < 56 && (figuresTypes[pos + 8] == 0 ||isRival(pos,pos + 8))) out.push(pos + 8);

        break;
    case PESHKA:

        if (whitePoses[x1 + y1] == 1) {
            if (y1 == 48 && figuresTypes[pos - 8] == 0 && figuresTypes[pos - 16] == 0) out.push(pos - 16);
            if ((y1 > 7) && figuresTypes[x1 + y1 - 8] == 0) out.push(x1 + y1 - 8);
            if ((y1 > 7) && (x1 < 7) && figuresTypes[x1 + y1 - 7] != 0 && !(whitePoses[x1 + y1 - 7])) out.push(x1 + y1 - 7);
            if ((y1 > 7) && (x1 > 0) && figuresTypes[x1 + y1 - 9] != 0 && !(whitePoses[x1 + y1 - 9])) out.push(x1 + y1 - 9);
            if (y1 == 24 && history.lastNum() != -1) {
                Step st = history.getLast();
                if ((st._figura == PESHKA) && (st._posNew - st._posOld  == 16)
                        && ((x0 < 7 && st._posNew - pos == 1) || (x0 > 0 && pos -st._posNew == 1))) {
                    out.push(st._posNew - 8);
                }
            }
        }
        else {
            if (y1 == 8 && figuresTypes[pos + 8] == 0
                    && figuresTypes[pos + 16] == 0) out.push(pos + 16);
            if ((y1 < 56) && figuresTypes[x1 + y1 + 8] == 0) out.push(x1 + y1 + 8);
            if ((y1 < 56) && (x1 < 7) && figuresTypes[x1 + y1 + 9] != 0 && (whitePoses[x1 + y1 + 9])) out.push(x1 + y1 + 9);
            if ((y1 < 56) && (x1 > 0) && figuresTypes[x1 + y1 + 7] != 0 && (whitePoses[x1 + y1 + 7])) out.push(x1 + y1 + 7);
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
    return out;
}

bool MyBoardLogic::thisIsVictory(char pos)
{
    if (!podUdarom(pos)) {

        for(int i = 0; i < BOARD_FIELDS_COUNT; i++) {
            if ((whitePoses[i] == whitePoses[pos]) && figuresTypes[i]) {
                MyVec<char> vec = steps(i);
                if (vec.lastNum() != -1) {
                    return false;
                }
            }
        }

    }
    else {
        MyVec<char> vecs = steps(pos);
        if (vecs.lastNum() != - 1) {
            while(vecs.lastNum() >= 0) {
                char posa = vecs.pop();
                StepEnum res = moveFig(pos, posa, false);
                if ((res == StepEnum::SIMPLE_STEP) || (res == StepEnum::PROMOTION)) {
                    if (!podUdarom(posa)) {
                        backStep();
                        curColor = 1 - curColor;
                        return false;
                    }
                    else {
                        backStep();
                        curColor = 1 - curColor;
                    }
                }
            }
        }
        for(int i = 0; i < BOARD_FIELDS_COUNT; i++) {
            if ((whitePoses[i] == whitePoses[pos]) && figuresTypes[i] && (i != pos)) {
                MyVec<char> vec = steps(i);
                while(vec.lastNum() >= 0) {
                    char posa = vec.pop();
                    StepEnum res = moveFig(i, posa, false);
                    if ((res == StepEnum::SIMPLE_STEP) || (res == StepEnum::PROMOTION)) {
                        if (!podUdarom(pos)) {
                            backStep();
                            curColor = 1 - curColor;
                            return false;
                        }
                        else {
                            backStep();
                            curColor = 1 - curColor;
                        }
                    }
                }
            }
        }
    }
    return true;
}

ChessPositions MyBoardLogic::getPositions() {
    ChessPositions positions;
    memcpy(positions.type, figuresTypes, BOARD_FIELDS_COUNT);
    memcpy(positions.color, whitePoses, BOARD_FIELDS_COUNT);
    return positions;
}

int MyBoardLogic::pawTrans(const char chosed) {
    figuresTypes[target] = chosed;
    target = BOARD_FIELDS_COUNT;
    curColor = 1 - curColor;
    return thisIsVictory(kingPos(curColor));
}

char MyBoardLogic::getCurColor() const {
    return curColor;
}
