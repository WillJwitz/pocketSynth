#ifndef PROGRAM_H
#define PROGRAM_H

#include <U8g2lib.h>

class Program {
public:

    Program(){}
    ~Program() {}

    virtual void onEncoderLeft() = 0;
    virtual void onEncoderRight() = 0;
    virtual void onClick() = 0;
    virtual void load() = 0;

};

#endif
