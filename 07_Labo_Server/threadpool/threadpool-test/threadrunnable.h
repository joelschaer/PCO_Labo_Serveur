#ifndef THREADRUNNER_H
#define THREADRUNNER_H

#include <QString>
#include "runnable.h"

class ThreadRunnable: public Runnable
{
public:
    ThreadRunnable(){}
    ~ThreadRunnable(){}

    void run(){}
    QString id();

};

#endif // THREADRUNNER_H
