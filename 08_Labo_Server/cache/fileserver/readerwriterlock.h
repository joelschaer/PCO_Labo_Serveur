/*******************************
** ReaderWriterLock
** ReaderWriterLock.h/.cpp
**
** Yann Lederrey and Joel Schär
**
** class to prevent concurrent acces to the resource,
** this class could lock for a reading acces or a writing access
**
** This class is based on a writer priority because,
** if the readers have the priority there will never be enough request to read.
**
**/

#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H
#include <QSemaphore>

class ReaderWriterLock
{

public:

    QSemaphore mutexReaders;    // mutual exclusion for the reader access
    QSemaphore mutexWriters;    // mutual exclusion for the writer access
    QSemaphore writer;          // writers waiting queue
    QSemaphore reader;          // readers witing queue
    QSemaphore mutex;           // global mutual exclusion
    int nbReaders, nbWriters;   // reader / writer counter

    /**
     * @brief constructor of the locker.
     */
    ReaderWriterLock();

    /**
     * @brief prevent the writers to read the resource while the reader is reading.
     */
    void lockReading();

    /**
     * @brief prevent the other writers or readers to access the resource while the writer is writing.
     */
    void lockWriting();

    /**
     * @brief release the resource access for all after a lockReading
     */
    void unlockReading();

    /**
     * @brief release the resource access for all after a lockWriting
     */
    void unlockWriting();
};

#endif // READERWRITERLOCK_H
