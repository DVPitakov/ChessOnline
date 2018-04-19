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

char MyBoardLogic::kingPos(char kingColor) {
    for(int i = 0; i < 64; i++) {
        if ((mas[i] == KOROL) && (sto[i] == kingColor)) {
            return i;
        }
    }
}

MyBoardLogic::MyBoardLogic() {
    memcpy(mas, startMas, 64);
    memcpy(sto, startSto, 64);
    memcpy(masBuf, startMas, 64);
    memcpy(stoBuf, startSto, 64);
}

void MyBoardLogic::backStep() {
    Step st = history.pop();
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

//0-правильный ход
//1-не тот пользователь или пустая ячейка
//2-король под атакой
//3-недоступный ход
//4-превращение пешки
//25-победа

int MyBoardLogic::moveFig(char pos1, char pos2, bool b) {
    if (target != 64  || (sto[pos1] != curColor)) {
        return 3;
    }
    if ((mas[pos1] == 0)) return 1;
    MyVec<char> avaliable = steps(pos1);
    if (avaliable.pos(pos2) == -1) { return 3;}
    history.push(Step(pos1, pos2, sto[pos1], mas[pos1], mas[pos2]));
    if ((mas[pos1] == PESHKA) && (mas[pos2] == 0) && (pos2 - pos1 != 8) && (pos1 - pos2 !=8) && (pos2 - pos1 != 16) && (pos1 - pos2 !=16)) {
        int len;
        if (sto[pos1]) len = + 8; else len = - 8;
        if (mas[pos2 + len] == PESHKA) {
            mas[pos2 + len] = 0;
            sto[pos2 + len] = 0;
        }

    }
    if ((mas[pos1] == PESHKA) && (((pos2 / 8 == 0) &&  (curColor))|| ((pos2 / 8 == 7) && (!curColor)))) {
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
    if (podUdarom(kingPos(curColor))) {
        backStep();
        return 2;
    }

    if (b && (mas[pos2] == PESHKA) && (((pos2 / 8) == 0) || ((pos2 / 8) == 7))) {
        target = pos2;
        return 4;
    }
    if (thisIsVictory(kingPos(1 - curColor))) {
        return 25;
    }
    curColor = 1 - curColor;
    return 0;
}

bool MyBoardLogic::podUdarom(char pos1) {
    int x0 = pos1 % 8;
    int y0 = pos1 / 8;
    int x1 = x0;
    int y1 = y0 << 3;
    char pos = pos1;
    char cend = pos - 9 * ((x0 > y0)?y0:x0);
    char cbuf;

    for (cbuf = pos - 9; cbuf >= cend && mas[cbuf] == 0; cbuf -= 9);
    if (cbuf >= cend && ((mas[cbuf]) == SLON || (mas[cbuf]) == FERZ) && isRival(pos,cbuf)) return true;

    cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
    for (cbuf = pos + 9; cbuf <= cend && mas[cbuf] == 0; cbuf += 9);
    if (cbuf <= cend && (((mas[cbuf]) == SLON) || (mas[cbuf]) == FERZ) && isRival(pos,cbuf)) return true;

    cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
    for (cbuf = pos + 7; cbuf <= cend && mas[cbuf] == 0; cbuf += 7);
    if (cbuf <= cend && (((mas[cbuf]) == SLON) || (mas[cbuf]) == FERZ) && isRival(pos,cbuf)) return true;

    cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
    for (cbuf = pos - 7; cbuf >= cend && mas[cbuf] == 0; cbuf -= 7);
    if (cbuf >= cend && ((mas[cbuf] == SLON) || (mas[cbuf]) == FERZ) &&  isRival(pos,cbuf)) return true;
    x1 = x0;
    y1 = y0 << 3;
    x1--;
    while(x1 >= 0 && (mas[x1 + y1] == 0)) x1--;
    if (x1 >= 0 && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    x1 = x0 + 1;
    while(x1 < 8 && (mas[x1 + y1] == 0)) x1++;
    if (x1 < 8 && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    x1 = x0;
    y1 -= 8;
    while(y1 >= 0 && (mas[x1 + y1] == 0)) y1 -= 8;
    if (y1 >= 0  && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    y1 = y0 << 3;
    y1 += 8;
    while(y1 < 64 && (mas[x1 + y1] == 0))
        y1 += 8;
    if (y1 < 64 && ((mas[x1 + y1]) == LADIA || (mas[x1 + y1]) == FERZ) && isRival(pos,x1 + y1)) return true;

    x1 = x0;
    y1 = y0 << 3;
    if (x1 < 7 && y1 >= 16 && ((mas[x1 + y1 - 15]) == 2) && isRival(pos,x1 + y1 - 15)) return true;
    if (x1 > 0 && y1 >= 16 && ((mas[x1 + y1 - 17]) == 2) && isRival(pos,x1 + y1 - 17)) return true;
    if (x1 < 6 && y1 >= 8 &&  ((mas[x1 + y1 - 6]) == 2) && isRival(pos,x1 + y1 - 6)) return true;
    if (x1 > 1 && y1 >= 8 &&  ((mas[x1 + y1 - 10]) == 2) && isRival(pos,x1 + y1 - 10)) return true;

    if (x1 < 7 && y1 < 48 && (((mas[x1 + y1 + 17]) == 2) && isRival(pos,x1 + y1 + 17))) return true;
    if (x1 > 0 && y1 < 48 && (((mas[x1 + y1 + 15]) == 2) && isRival(pos,x1 + y1 + 15))) return true;
    if (x1 < 6 && y1 < 56 && (((mas[x1 + y1 + 10]) == 2) && isRival(pos,x1 + y1 + 10))) return true;
    if (x1 > 1 && y1 < 56 && (((mas[x1 + y1 + 6]) == 2) && isRival(pos,x1 + y1 + 6))) return true;

    if (sto[pos]) {
        if ((y1 > 8) && (x1 > 0) && ((mas[pos - 9]) == PESHKA) && isRival(pos, pos - 9)) return true;
        if ((y1 > 8) && (x1 < 7) && ((mas[pos - 7]) == PESHKA) && isRival(pos, pos - 7)) return true;
        if (mas[pos] == PESHKA) {
            if (y1 == 32 && history.lastNum() != -1) {
                Step st = history.getLast();

                if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == -16 && st._posNew == pos))
                {
                    if (x0 > 0 && mas[pos - 1] == PESHKA && isRival(pos,pos - 1)) return true;
                    if (x0 < 7 && mas[pos + 1] == PESHKA && isRival(pos,pos + 1)) return true;

                }
            }
        }
    }
    else {
        if ((y1 < 48) && (x1 > 0) && (( mas[x1 + y1 + 7])) == PESHKA && isRival(pos,x1 + y1 + 7)) return true;
        if ((y1 < 48) && (x1 < 7) && (( mas[x1 + y1 + 9])) == PESHKA && isRival(pos,x1 + y1 + 9)) return true;
        if (mas[pos] == PESHKA) {
            if (y1 == 24 && history.lastNum() != -1) {
                Step st = history.getLast();
                if ((st._figura == PESHKA) && ( st._posNew - st._posOld  == 16 && st._posNew == pos))
                {
                    if (x0 > 0 && mas[pos - 1] == PESHKA && isRival(pos,pos - 1)) {return true;}
                    if (x0 < 7 && mas[pos + 1] == PESHKA && isRival(pos,pos + 1)) {return true;}

                }
            }
        }
    }


    if (x1 > 0) {
        if (( mas[pos - 1] == 5) && isRival(pos,pos - 1)) return true;
        if (y1 > 0 && (( mas[pos - 9]) == 5) && isRival(pos,pos - 9)) return true;
        if (y1 < 56 && (( mas[pos + 7]) == 5) &&  isRival(pos,pos + 7))return true;
    }
    if (x1 < 7) {
        if (( mas[pos + 1] == 5) && isRival(pos,pos + 1)) return true;
        if (y1 > 0 && (( mas[pos - 7]) == 5) && isRival(pos,pos - 7)) return true;
        if (y1 < 56 && (( mas[pos + 9]) == 5) && isRival(pos,pos + 9)) return true;
    }
    if (y1 > 0 && ((( mas[pos - 8]) == 5) && isRival(pos,pos - 8))) return true;
    if (y1 < 56 && ((( mas[pos + 8]) == 5) &&isRival(pos,pos + 8))) return true;

    return false;
}

MyVec<char> MyBoardLogic::steps(char pos) {
    MyVec<char> out;
    char x1, y1;
    char x0 = pos % 8;
    char y0 = pos / 8;
    x1 = x0;
    y1 = y0 << 3;
    switch (mas[pos])
    {
    case LADIA:
        x1--;
        while(x1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1--;}
        if (x1 >= 0 && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) { out.push(x1 + y1);}

        x1 = x0 + 1;
        while(x1 < 8 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1++;}
        if (x1 < 8 && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        x1 = x0;
        y1 -= 8;
        while(y1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 -= 8;}
        if (y1 >= 0  && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        y1 = y0 << 3;
        y1 += 8;
        while(y1 < 64 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 += 8;}
        if (y1 < 64 && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) out.push(x1 + y1);
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

        for (cbuf = pos - 9; cbuf >= cend && mas[cbuf] == 0; cbuf -= 9) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && isRival(pos,cbuf)) out.push(cbuf);

        cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
        for (cbuf = pos + 9; cbuf <= cend && mas[cbuf] == 0; cbuf += 9) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
        for (cbuf = pos + 7; cbuf <= cend && mas[cbuf] == 0; cbuf += 7) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
        for (cbuf = pos - 7; cbuf >= cend && mas[cbuf] == 0; cbuf -= 7) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        break;}
    case FERZ:
    {char cend = pos - 9 * ((x0 > y0)?y0:x0);
        char cbuf;

        for (cbuf = pos - 9; cbuf >= cend && mas[cbuf] == 0; cbuf -= 9) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos + 9 * ((x0 > y0)?(7-x0):(7-y0));
        for (cbuf = pos + 9; cbuf <= cend && mas[cbuf] == 0; cbuf += 9) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos + 7 * ((x0 < (7 - y0))?x0:(7 - y0));
        for (cbuf = pos + 7; cbuf <= cend && mas[cbuf] == 0; cbuf += 7) out.push(cbuf);
        if (cbuf <= cend && mas[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);

        cend = pos - 7 * ((7 - x0 < y0)?(7 - x0):y0);
        for (cbuf = pos - 7; cbuf >= cend && mas[cbuf] == 0; cbuf -= 7) out.push(cbuf);
        if (cbuf >= cend && mas[cbuf] != 0 && (isRival(pos,cbuf))) out.push(cbuf);
        x1--;
        while(x1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1--;}
        if (x1 >= 0 && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        x1 = x0 + 1;
        while(x1 < 8 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); x1++;}
        if (x1 < 8 && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        x1 = x0;
        y1 -= 8;
        while(y1 >= 0 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 -= 8;}
        if (y1 >= 0  && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}

        y1 = y0 << 3;
        y1 += 8;
        while(y1 < 64 && (mas[x1 + y1] == 0)) {out.push(x1 + y1); y1 += 8;}
        if (y1 < 64 && (mas[x1 + y1] != 0) && isRival(pos, x1 + y1)) {out.push(x1 + y1);}
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
            if ((mas[pos - 1] == 0) || isRival(pos,pos - 1)) out.push(pos - 1);
            if (y1 > 0 && ((mas[pos - 9] == 0) || (isRival(pos,pos - 9)))) out.push(pos - 9);
            if (y1 < 56 && ((mas[pos + 7] == 0) || (isRival(pos,pos + 7)))) out.push(pos + 7);
        }
        if (x1 < 7) {
            if (((mas[pos + 1] == 0) || isRival(pos,pos + 1))) out.push(pos + 1);
            if (y1 > 0 && ((mas[pos - 7] == 0) || isRival(pos,pos - 7))) out.push(pos - 7);
            if (y1 < 56 && ( (mas[pos + 9] == 0) || isRival(pos,pos + 9))) out.push(pos + 9);
        }
        if (y1 > 0 && (mas[pos - 8] == 0 ||  isRival(pos,pos - 8))) out.push(pos - 8);
        if (y1 < 56 && (mas[pos + 8] == 0 ||isRival(pos,pos + 8))) out.push(pos + 8);

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
    return out;
}

bool MyBoardLogic::thisIsVictory(char pos)
{
    qDebug() << "this is victory called";
    if (!podUdarom(pos)) {

        for(int i = 0; i < 64; i++) {
            if ((sto[i] == sto[pos]) && mas[i]) {
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
                int res = moveFig(pos, posa, false);
                if ((res == 0) || (res == 4)) {
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
        for(int i = 0; i < 64; i++) {
            if ((sto[i] == sto[pos]) && mas[i] && (i != pos)) {
                MyVec<char> vec = steps(i);
                while(vec.lastNum() >= 0) {
                    char posa = vec.pop();
                    int res = moveFig(i, posa, false);
                    if ((res == 0) || (res == 4)) {
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
    qDebug() << "this is victory true";
    return true;
}
