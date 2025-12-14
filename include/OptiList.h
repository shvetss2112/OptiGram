#ifndef UNTITLED2_OPTILIST_H
#define UNTITLED2_OPTILIST_H
#include <cstddef>
template<typename T,size_t N=16>//simplest stack in whole wild west
struct OptStack {
    T buf[N];
    size_t size;
    OptStack() {
        size = 0;
    }
    void push(T val) {
        if (size>=N)return;
        buf[size]=val;
        size++;
    }
    void pop() {
        if (size==0)return;
        size--;
    }
    T& top() {
        static T dummy{};
        if (!size) return dummy;
        return buf[size-1];
    }
};

template<typename T,size_t N=16>//simplest list
struct OptList: OptStack<T,N> {
    T& operator[](size_t i) {
        static T dummy{};
        if (i < this->size) {
            return this->buf[i];
        }
        return dummy;
    }
};

#endif //UNTITLED2_OPTILIST_H