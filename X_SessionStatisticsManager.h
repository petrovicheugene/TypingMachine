//===================================================
#ifndef X_SESSIONSTATISTICSMANAGER_H
#define X_SESSIONSTATISTICSMANAGER_H
//===================================================
#include "X_TrainingManager.h"
#include "X_AbstractStatisticsSource.h"
#include "X_TrainingManager.h"

#include <QObject>
#include <QMap>
//===================================================

//===================================================
class X_SessionStatisticsManager : public QObject
{
    Q_OBJECT
public:
    explicit X_SessionStatisticsManager(QObject *parent = nullptr);

    void xp_setTrainingManager(X_TrainingManager* manager);
    void xp_setStatisticsSource(X_AbstractStatisticsSource* statisticsSource);
    QMap<QString, WordStatistics>xp_statistics() const;

public slots:

    void xp_updateStatistics(QString pressedSymbol);
    void xp_onTaskStateChange(X_TrainingManager::TASK_STATE previous,
                              X_TrainingManager::TASK_STATE current);
signals:

    void xg_taskStatisticsReadiness(bool ready);

private:

    // VARS
    X_TrainingManager* xv_trainingManager;
    X_AbstractStatisticsSource* xv_statisticsSource;

    QString xv_currentWord;
    qint64 xv_wordStartTimeMark;
    qint64 xv_taskStartTimeMark;
    qint64 xv_pauseStartTimeMark;

    int xv_errorCount;

    QMap<QString, WordStatistics>xv_statistics;

    // FUNCS
    void xh_registerCurrentWordStatistics();
    void xh_resetCurrentWordStatistics();

};
//===================================================
#endif // X_SESSIONSTATISTICSMANAGER_H
