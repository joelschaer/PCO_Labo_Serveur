/*******************************
** Runnable
** Runnable.h
**
** Yann Lederrey and Joel Schär
**
** Runnable interface, gives function needed by the thread pool to run it.
**
**/
#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QString>

class Runnable
{
public:
    virtual ~Runnable(){}
    virtual void run() = 0;
    virtual QString id() = 0;
};

#endif // RUNNABLE_H
