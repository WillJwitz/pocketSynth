#ifndef PROGRAM_H
#define PROGRAM_H

class Program {
public:
    virtual ~Program() {}

    virtual void onEncoderLeft() = 0;
    virtual void onEncoderRight() = 0;
    virtual void onClick() = 0;
    virtual void onLongClick() = 0;
    virtual void onBack() = 0;

};

#endif
