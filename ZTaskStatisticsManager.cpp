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
    connect(zv_trainingManager, &ZTrainingManager::zg_stateChanged,
            this, &ZTaskStatisticsManager::zp_updateStatistics);
    //    connect(zv_trainingManager, &ZTrainingManager::zg_durationChanged,
    //            this, &ZTaskStatisticsManager::zp_updateDuration);

}
//===================================================
void ZTaskStatisticsManager::zp_updateStatistics()
{
    qDebug() << "UPD STAT";
    if(zv_trainingManager->zp_isWrong())
    {
        qDebug() << "ERR"<< zv_errorCount++;

        return;
    }

    QRegularExpression re("[\\s\\t]");
    if(re.match(zv_trainingManager->zp_currentSymbol()).hasMatch())
    {
        // space or tab in line: end of the current word
        zh_registerWord();
        return;
    }

    if(zv_trainingManager->zp_currentSymbolIndex() == 0)
    {
        // new line started
        zh_registerWord();
    }

    // in the midle of the word
    zv_currentWord.append(zv_trainingManager->zp_currentSymbol());

}
//===================================================
void ZTaskStatisticsManager::zh_registerWord()
{
    if(!zv_currentWord.isEmpty())
    {
        qint64 wordDuration =  QDateTime::currentMSecsSinceEpoch() - zv_timeMark;
        qDebug() << zv_currentWord << "dur:" << wordDuration << "sp:" << wordDuration / zv_currentWord.count() << "spm" << "err:" << zv_errorCount;
    }

    zv_currentWord.clear();
    zv_errorCount = 0;
    zv_timeMark = QDateTime::currentMSecsSinceEpoch();

}
//===================================================


