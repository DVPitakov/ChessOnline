#ifndef MYVEC_H
#define MYVEC_H
#include <malloc.h>

#include <stdio.h>
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

template <class T>
class MyVec {
public:
    MyVec():size(32),last(-1) {
        buf = (T*)malloc(size * (sizeof(T)));
    }

    ~MyVec() {
        free(buf);
    }

    void push(T el) {
        last++;
        if (size == last) {
            size << 1;
            T* res = (T*)malloc(size * (sizeof(T)));
            memcpy(res, buf, last * (sizeof(T)));
            free(buf);
            buf = res;
        }
        buf[last] = el;
    }

    T getLast() {
        return buf[last];
    }

    T pop() {
        T res = buf[last];
        last--;
        return res;
    }

    long lastNum() {
        return last;
    }

    long pos(T tg) {
        int i = 0;
        for(; i <= last && buf[i] != tg; i++);
        if (i > last) return -1;
        return i;
    }

    MyVec(const MyVec& vec) {
        this->last = vec.last;
        this->buf = (char*)malloc(vec.size * (sizeof(T)));
        this->size = vec.size;
        memcpy(this->buf, vec.buf, size * (sizeof(T)));
    }

private:
    long size;
    long last;
     T * buf;

};


#endif // MYVEC_H