//===================================================
#ifndef ZTASKSTATISTICSMANAGER_H
#define ZTASKSTATISTICSMANAGER_H
//===================================================
#include "ZTrainingManager.h"

#include <QObject>
//===================================================
//===================================================
class ZTaskStatisticsManager : public QObject
{
    Q_OBJECT
public:
    explicit ZTaskStatisticsManager(QObject *parent = nullptr);

    void zp_connectToTrainingManager(ZTrainingManager* manager);

public slots:

    void zp_updateStatistics(QString pressedSymbol);
    void zp_onTaskStateChange(ZTrainingManager::TASK_STATE previous,
                              ZTrainingManager::TASK_STATE current);
signals:


private:

    // VARS
    ZTrainingManager* zv_trainingManager;
    QString zv_currentWord;
    qint64 zv_timeMark;
    qint64 zv_pauseStartMark;
    int zv_errorCount;

    // FUNCS
    void zh_registerCurrentWordStatistics();
    void zh_resetCurrentWordStatistics();

};
//===================================================
#endif // ZTASKSTATISTICSMANAGER_H
