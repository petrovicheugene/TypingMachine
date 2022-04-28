//===================================================
#ifndef ZWORKCONTROLLER_H
#define ZWORKCONTROLLER_H
//===================================================
#include <QObject>
#include "ZAbstractTaskSource.h"
//#include "ZTask.h"
//===================================================
class ZWorkController : public QObject
{
    Q_OBJECT
public:
    explicit ZWorkController(QObject *parent = nullptr);

    void zp_setTaskSource(ZAbstractTaskSource *taskSource);
    // void zp_connectToTaskSource(ZTaskSource* taskSource);


public slots:

    void zp_initTaskStart(int row);
    void zp_initTaskFinish(bool statisticsReadiness);
    void zp_initStatisticsDisplayFinish();

signals:

    void zg_setStackedWidgetIndex(int index);
    void zg_requestTaskStart(ZTask task);
    void zg_requestTaskFinish();

private:

    // VARS
    ZAbstractTaskSource* zv_taskSource;
    // FUNCS

};
//===================================================
#endif // ZWORKCONTROLLER_H
