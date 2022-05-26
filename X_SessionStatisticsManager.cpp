//===================================================
#include "X_SessionStatisticsManager.h"

#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>

//===================================================
X_SessionStatisticsManager::X_SessionStatisticsManager(QObject *parent)
    : QObject{parent}
{
    xv_trainingManager = nullptr;
    xv_statisticsSource = nullptr;
}
//===================================================
void X_SessionStatisticsManager::xp_setTrainingManager(X_TrainingManager* manager)
{
    xv_trainingManager = manager;
    connect(xv_trainingManager, &X_TrainingManager::xg_symbolPressed,
            this, &X_SessionStatisticsManager::xp_updateStatistics);
    connect(xv_trainingManager, &X_TrainingManager::xg_taskStateChanged,
            this, &X_SessionStatisticsManager::xp_onTaskStateChange);

}
//===================================================
void X_SessionStatisticsManager::xp_setStatisticsSource(X_AbstractStatisticsSource* statisticsSource)
{
    xv_statisticsSource = statisticsSource;
}
//===================================================
QMap<QString, WordStatistics> X_SessionStatisticsManager::xp_statistics() const
{
    return xv_statistics;
}
//===================================================
void X_SessionStatisticsManager::xp_updateStatistics(QString pressedSymbol)
{
    if(xv_trainingManager->xp_isWrong())
    {
        xv_errorCount++;
        return;
    }

    static QRegularExpression re("[\\s\\t]");
    if(re.match(pressedSymbol).hasMatch())
    {
        xh_resetCurrentWordStatistics();
        return;
    }

    xv_currentWord.append(pressedSymbol);

    // if new line or current symbol is space
    if(xv_trainingManager->xp_currentSymbolIndex() == 0  ||
            xv_trainingManager->xp_currentSymbolIndex() == xv_trainingManager->xp_currentLine().count())
    {
        xh_registerCurrentWordStatistics();
        xh_resetCurrentWordStatistics();
    }
    else if(re.match(xv_trainingManager->xp_currentSymbol()).hasMatch())
    {
        xh_registerCurrentWordStatistics();
    }
}
//===================================================
void X_SessionStatisticsManager::xh_resetCurrentWordStatistics()
{
    xv_wordStartTimeMark = QDateTime::currentMSecsSinceEpoch();
    xv_errorCount = 0;
    xv_currentWord = QString();
}
//===================================================
void X_SessionStatisticsManager::xh_registerCurrentWordStatistics()
{
    if(xv_currentWord.isEmpty())
    {
        return;
    }

    qint64 wordDurationMsec =  QDateTime::currentMSecsSinceEpoch() - xv_wordStartTimeMark;

    xv_statistics[xv_currentWord].typingCount = xv_statistics[xv_currentWord].typingCount + 1;
    xv_statistics[xv_currentWord].errorCount = xv_statistics[xv_currentWord].errorCount + xv_errorCount;
    xv_statistics[xv_currentWord].durationMsec = xv_statistics[xv_currentWord].durationMsec + wordDurationMsec;

    qDebug() << xv_currentWord
             << "DUR:" << xv_statistics[xv_currentWord].durationMsec/1000.0
             << "SP:" << 60000.0 * xv_currentWord.count() / (xv_statistics[xv_currentWord].durationMsec / xv_statistics[xv_currentWord].typingCount)
             << "spm" << "err:" << xv_statistics[xv_currentWord].errorCount;

}
//===================================================
void X_SessionStatisticsManager::xp_onTaskStateChange(X_TrainingManager::TASK_STATE previous,
                                                  X_TrainingManager::TASK_STATE current)
{
    if(current == X_TrainingManager::TS_PAUSED)
    {
        qDebug() << "TASK STATE PAUSED" << current;
        if(previous == X_TrainingManager::TS_ACTIVE)
        {
            xv_pauseStartTimeMark = QDateTime::currentMSecsSinceEpoch();
        }
    }
    else if(current == X_TrainingManager::TS_ACTIVE)
    {
        qDebug() << "TASK STATE ACTIVE" << current;
        if(previous == X_TrainingManager::TS_PAUSED)
        {
            qint64 pauseDuration = QDateTime::currentMSecsSinceEpoch() - xv_pauseStartTimeMark;
            xv_wordStartTimeMark = xv_wordStartTimeMark + pauseDuration;
            xv_taskStartTimeMark = xv_taskStartTimeMark + pauseDuration;
        }
        else
        {
            xh_resetCurrentWordStatistics();
            // xv_statistics.clear();
        }
    }
    else if(current == X_TrainingManager::TS_COMPLETED)
    {
        // TODO merge TS_COMPLETED & TS_INACTIVE
        qDebug() << "TASK STATE COMPLETED" << current;
        xh_resetCurrentWordStatistics();

        bool ready = !xv_statistics.isEmpty();
        if(ready)
        {
            // no statistics
            if(xv_statisticsSource)
            {
                xv_statisticsSource->xp_loadTaskStatistics(xv_statistics);
            }
        }
        emit xg_taskStatisticsReadiness(ready);
    }
    else // TS_INACTIVE
    {
        qDebug() << "TASK STATE INACTIVE" << current;
        xh_resetCurrentWordStatistics();

        bool ready = !xv_statistics.isEmpty();
        if(ready)
        {
            // no statistics
            if(xv_statisticsSource)
            {
                xv_statisticsSource->xp_loadTaskStatistics(xv_statistics);
            }
        }
        emit xg_taskStatisticsReadiness(ready);
    }
}
//===================================================

