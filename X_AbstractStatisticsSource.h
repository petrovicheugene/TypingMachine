//===================================================
#ifndef X_ABSTRACTSTATISTICSSOURCE_H
#define X_ABSTRACTSTATISTICSSOURCE_H
//===================================================
#include "X_WordStatistics.h"
//===================================================
class QAbstractItemModel;
//===================================================
class X_AbstractStatisticsSource
{
public:
    X_AbstractStatisticsSource();

    virtual QAbstractItemModel* xp_statisticsModel() const = 0;
    virtual void xp_loadTaskStatistics(QMap<QString, WordStatistics>& taskStatistics) = 0;

};
//===================================================
#endif // X_ABSTRACTSTATISTICSSOURCE_H
