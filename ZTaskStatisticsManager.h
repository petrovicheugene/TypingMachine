//===================================================
#ifndef ZTASKSTATISTICSMANAGER_H
#define ZTASKSTATISTICSMANAGER_H
//===================================================
#include <QObject>
//===================================================
class ZTrainingManager;
//===================================================
class ZTaskStatisticsManager : public QObject
{
    Q_OBJECT
public:
    explicit ZTaskStatisticsManager(QObject *parent = nullptr);

    void zp_connectToTrainingManager(ZTrainingManager* manager);

public slots:

    void zp_updateStatistics();
    void zp_registerError();
    void zp_setPause(bool paused);

signals:


private:

    // VARS
    ZTrainingManager* zv_trainingManager;
    QString zv_currentWord;
    qint64 zv_timeMark;
    int zv_errorCount;

    // FUNCS
    void zh_registerWordAndStatistics();

};
//===================================================
#endif // ZTASKSTATISTICSMANAGER_H
