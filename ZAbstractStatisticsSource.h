//===================================================
#ifndef ZABSTRACTSTATISTICSSOURCE_H
#define ZABSTRACTSTATISTICSSOURCE_H
//===================================================
#include "ZWordStatistics.h"
//===================================================
class QAbstractItemModel;
//===================================================
class ZAbstractStatisticsSource
{
public:
    ZAbstractStatisticsSource();

    virtual QAbstractItemModel* zp_statisticsModel() const = 0;
    virtual void zp_loadTaskStatistics(QMap<QString, WordStatistics>& taskStatistics) = 0;

};
//===================================================
#endif // ZABSTRACTSTATISTICSSOURCE_H
