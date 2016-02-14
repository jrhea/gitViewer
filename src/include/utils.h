#ifndef UTILS_H
#define UTILS_H
#include <QWaitCondition>
#include <QMutex>

/**
 * @brief The Sleep class utility that helps test multithreaded code
 */
class Sleep
{

public:

    /**
     * @brief causes the current thread to sleep for msecs milliseconds.
     * @param msecs
     */
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
