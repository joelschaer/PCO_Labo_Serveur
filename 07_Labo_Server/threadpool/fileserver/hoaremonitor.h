#ifndef HOAREMONITOR_H
#define HOAREMONITOR_H


#include <QSemaphore>

/**
 * This class allows to easily create a monitor as defined by Hoare in 1974.
 * It offers functions that allow to define the entry point of the monitor
 * as well as condition variables and the functions needed to use them.
 * It is meant to be a superclass of an actual implementation, as presented
 * in the example.
 */
class HoareMonitor
{
protected:

    HoareMonitor();

    /**
     * @brief The Condition class is a class implementing a waiting condition.
     * Multiple threads can be waiting on it. It keep a fifo list of the waiting threads
     * by using a semaphore and a counter to keep the number of waiting threads.
     */
    class Condition
    {
        friend HoareMonitor;

    public:
        Condition();
    private:
        QSemaphore waitingSem;
        int nbWaiting;
    };

    /**
     * This function has to be called at the beginning of each function being
     * an entry point to the monitor.
     */
    void monitorIn();

    /**
     * This function has to be called at the end of each function being
     * an entry point to the monitor.
     */
    void monitorOut();

    /**
     * This function implements the waiting on a condition, as defined by Hoare.
     * When the thread is waken by a signal, it continues with the mutual
     * exclusion.
     * @ param cond Condition on which the monitor will wait on
     */
    void wait(Condition &cond);

    /**
     * This function implements the signaling of a condition, as defined by
     * Hoare. If no thread is waiting for the condition, then nothing happens,
     * but if there is one the thread calling signal is suspended, waiting for
     * the other one to finish.
     * @ param cond Condition that will be signal to wake up a waiting thread.
     */
    void signal(Condition &cond);

private:

    //! Mutex for the protecting the entire monitor
    QSemaphore monitorMutex;
    //! Blocking semaphore for the thread doing a signal(condition)
    QSemaphore monitorSignale;
    //! Number of threads waiting on the semaphore monitorSignale
    int monitorNbSignale;
};


#endif // HOAREMONITOR_H
