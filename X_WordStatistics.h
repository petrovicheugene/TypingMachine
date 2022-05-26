//===================================================
#ifndef X_WORDSTATISTICS_H
#define X_WORDSTATISTICS_H
//===================================================
#include "qglobal.h"
//===================================================
struct WordStatistics
{
    WordStatistics() : typingCount(0), errorCount(0), durationMsec(0) {};
    int typingCount;
    int errorCount;
    qint64 durationMsec;
};
//===================================================
#endif // X_WORDSTATISTICS_H
