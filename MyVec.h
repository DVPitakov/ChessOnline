#ifndef MYVEC_H
#define MYVEC_H
#include <malloc.h>
#include <stdio.h>

template <class T>
class MyVec {
public:
    MyVec():size(256),last(-1) {
        buf = (T*)malloc(size* (sizeof(T)));
    }

    ~MyVec() {
        free(buf);
    }

    bool isEmpty() {
        return last > -1;
    }


    void push(T el) {
        last++;
        if (size == last) {
            size *= 2;
            T* res = (T*)malloc(size * (sizeof(T)));
            memcpy(res, buf, last * (sizeof(T)));
            free(buf);
            buf = res;
        }
        buf[last] = el;
    }

    T getLast() const {
        return buf[last];
    }

    T pop() {
        T res = buf[last];
        last--;
        return res;
    }

    long lastNum() const{
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
        this->buf = (unsigned char*)malloc(vec.size * (sizeof(T)));
        this->size = vec.size;
        memcpy(this->buf, vec.buf, size * (sizeof(T)));
    }

private:
    long size;
    long last;
     T * buf;

};


#endif // MYVEC_H
