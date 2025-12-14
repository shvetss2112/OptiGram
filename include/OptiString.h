#ifndef UNTITLED2_OPTISTRING_H
#define UNTITLED2_OPTISTRING_H
#include <cstddef>

template<size_t N=64>
struct OptiString {
    char buf[N];
    size_t len;
    OptiString():len(0) {this->setEnd();}
    OptiString(const char* str):len(0) {
        this->setEnd();
        this->append(str);
    }
    void setEnd() {
        buf[len]='\0';
    }
    const char* c_str() const {
        return buf;
    }
    void append(const char* string) {
        size_t i=0;
        while(len+i<N-1) {
            buf[len+i]=string[i];
            if (string[i]=='\0')break;
            i++;
        }
        len+=i;
        this->setEnd();
    }
    void append(const char c) {
        if (len<N-1) {
            buf[len]=c;
            len++;
            buf[len]='\0';
        }
    }

};

#endif //UNTITLED2_OPTISTRING_H