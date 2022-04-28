//===================================================
#ifndef ZWORDSTATISTICS_H
#define ZWORDSTATISTICS_H
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
#endif // ZWORDSTATISTICS_H
