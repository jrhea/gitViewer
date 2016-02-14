#ifndef UTILS_H
#define UTILS_H
#include <QWaitCondition>
#include <QMutex>

class Sleep
{

public:

    // Causes the current thread to sleep for msecs milliseconds.
    static void msleep(unsigned long msecs)
    {
        QMutex mutex;
        mutex.lock();

        QWaitCondition waitCondition;
        waitCondition.wait(&mutex, msecs);

        mutex.unlock();
    }
};
#endif // UTILS_H
