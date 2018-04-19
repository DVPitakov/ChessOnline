#ifndef MODELS_H
#define MODELS_H

typedef unsigned char FigurePos;
typedef unsigned char FigureType;
typedef unsigned char Storona;

enum class EndCouse: char {
    YOUR_FAIL_ONE = 0,
    YOUR_WIN = 25,
    YOUR_FAIL_TWO = 45,
    RIVAL_SURENDED = 100
};

#endif // MODELS_H
