//===================================================
#ifndef ZTASKSTATISTICSMANAGER_H
#define ZTASKSTATISTICSMANAGER_H
//===================================================
#include "ZTrainingManager.h"

#include <QObject>
#include <QMap>
//===================================================
struct WordStatistics
{
    WordStatistics() : typingCount(0), errorCount(0), durationMsec(0) {};
    int typingCount;
    int errorCount;
    qint64 durationMsec;
};
//===================================================
class ZTaskStatisticsManager : public QObject
{
    Q_OBJECT
public:
    explicit ZTaskStatisticsManager(QObject *parent = nullptr);

    void zp_connectToTrainingManager(ZTrainingManager* manager);
    QMap<QString, WordStatistics>zp_statistics() const;

public slots:

    void zp_updateStatistics(QString pressedSymbol);
    void zp_onTaskStateChange(ZTrainingManager::TASK_STATE previous,
                              ZTrainingManager::TASK_STATE current);
signals:


private:

    // VARS
    ZTrainingManager* zv_trainingManager;
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
#endif // ZTASKSTATISTICSMANAGER_H
