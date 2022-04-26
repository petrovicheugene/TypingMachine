//===================================================
#include "ZTaskStatisticsManager.h"
#include "ZTrainingManager.h"

#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>
//===================================================
ZTaskStatisticsManager::ZTaskStatisticsManager(QObject *parent)
    : QObject{parent}
{

}
//===================================================
void ZTaskStatisticsManager::zp_connectToTrainingManager(ZTrainingManager* manager)
{
    zv_trainingManager = manager;
    connect(zv_trainingManager, &ZTrainingManager::zg_symbolPressed,
            this, &ZTaskStatisticsManager::zp_updateStatistics);
    connect(zv_trainingManager, &ZTrainingManager::zg_taskStateChanged,
            this, &ZTaskStatisticsManager::zp_onTaskStateChange);

}
//===================================================
void ZTaskStatisticsManager::zp_updateStatistics(QString pressedSymbol)
{
    if(zv_trainingManager->zp_isWrong())
    {
        zv_errorCount++;
        return;
    }

    static QRegularExpression re("[\\s\\t]");
    if(re.match(pressedSymbol).hasMatch())
    {
        zh_resetCurrentWordStatistics();
        return;
    }

    zv_currentWord.append(pressedSymbol);

    // if new line or current symbol is space
    if(zv_trainingManager->zp_currentSymbolIndex() == 0 )
    {
        zh_registerCurrentWordStatistics();
        zh_resetCurrentWordStatistics();
    }
    else if(zv_trainingManager->zp_currentSymbolIndex()
            == zv_trainingManager->zp_currentLine().count())
    {
        // end of line
        zh_registerCurrentWordStatistics();
    }
    else if(re.match(zv_trainingManager->zp_currentSymbol()).hasMatch())
    {
        zh_registerCurrentWordStatistics();
    }
}
//===================================================
void ZTaskStatisticsManager::zh_resetCurrentWordStatistics()
{
    zv_timeMark = QDateTime::currentMSecsSinceEpoch();
    zv_errorCount = 0;
    zv_currentWord = QString();

}
//===================================================
void ZTaskStatisticsManager::zh_registerCurrentWordStatistics()
{
    if(!zv_currentWord.isEmpty())
    {
        qint64 wordDuration =  QDateTime::currentMSecsSinceEpoch() - zv_timeMark;
        qDebug() << zv_currentWord << "dur:" << wordDuration << "sp:" << wordDuration / zv_currentWord.count() << "spm" << "err:" << zv_errorCount;
    }
}
//===================================================
void ZTaskStatisticsManager::zp_onTaskStateChange(ZTrainingManager::TASK_STATE previous,
                                                  ZTrainingManager::TASK_STATE current)
{
    if(current == ZTrainingManager::TS_PAUSED)
    {
        qDebug() << "TASK STATE PAUSED" << current;
        if(previous == ZTrainingManager::TS_ACTIVE)
        {
            zv_pauseStartMark = QDateTime::currentMSecsSinceEpoch();
        }
    }
    else if(current == ZTrainingManager::TS_ACTIVE)
    {
        qDebug() << "TASK STATE ACTIVE" << current;
        if(previous == ZTrainingManager::TS_PAUSED)
        {
            zv_timeMark = zv_timeMark + (QDateTime::currentMSecsSinceEpoch() - zv_pauseStartMark);
        }
        else if(previous == ZTrainingManager::TS_INACTIVE)
        {
            zh_resetCurrentWordStatistics();
        }
    }
    else if(current == ZTrainingManager::TS_COMPLETED)
    {
        qDebug() << "TASK STATE COMPLETED" << current;
        //zh_registerCurrentWordStatistics();
        //zh_resetCurrentWordStatistics();
    }
    else // TS_INACTIVE
    {
        zh_resetCurrentWordStatistics();
    }
}
//===================================================

