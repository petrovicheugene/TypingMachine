//===================================================
#ifndef ZSESSIONSTATISTICSMANAGER_H
#define ZSESSIONSTATISTICSMANAGER_H
//===================================================
#include "ZTrainingManager.h"
#include "ZAbstractStatisticsSource.h"
#include "ZTrainingManager.h"

#include <QObject>
#include <QMap>
//===================================================

//===================================================
class ZSessionStatisticsManager : public QObject
{
    Q_OBJECT
public:
    explicit ZSessionStatisticsManager(QObject *parent = nullptr);

    void zp_setTrainingManager(ZTrainingManager* manager);
    void zp_setStatisticsSource(ZAbstractStatisticsSource* statisticsSource);
    QMap<QString, WordStatistics>zp_statistics() const;

public slots:

    void zp_updateStatistics(QString pressedSymbol);
    void zp_onTaskStateChange(ZTrainingManager::TASK_STATE previous,
                              ZTrainingManager::TASK_STATE current);
signals:

    void zg_taskStatisticsReadiness(bool ready);

private:

    // VARS
    ZTrainingManager* zv_trainingManager;
    ZAbstractStatisticsSource* zv_statisticsSource;

    QString zv_currentWord;
    qint64 zv_wordStartTimeMark;
    qint64 zv_taskStartTimeMark;
    qint64 zv_pauseStartTimeMark;

    int zv_errorCount;

    QMap<QString, WordStatistics>zv_statistics;

    // FUNCS
    void zh_registerCurrentWordStatistics();
    void zh_resetCurrentWordStatistics();

};
//===================================================
#endif // ZSESSIONSTATISTICSMANAGER_H
