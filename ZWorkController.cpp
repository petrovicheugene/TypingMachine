//===================================================
#include "ZWorkController.h"
//===================================================

//===================================================
ZWorkController::ZWorkController(QObject *parent)
    : QObject{parent}
{
    zv_taskSource = nullptr;
}
//===================================================
void ZWorkController::zp_setTaskSource(ZAbstractTaskSource* taskSource)
{
    zv_taskSource = taskSource;
}
//===================================================
void ZWorkController::zp_initTaskStart(int row)
{
    if(!zv_taskSource)
    {
        return;
    }

    ZTask task = zv_taskSource->zp_taskForRow(row);
    emit zg_setStackedWidgetIndex(1);
    emit zg_requestTaskStart(task);
}
//===================================================
void ZWorkController::zp_initTaskFinish(bool statisticsReadiness)
{
    //emit zg_requestTaskFinish();
    if(statisticsReadiness)
    {
        emit zg_setStackedWidgetIndex(2);
    }
    else
    {
        emit zg_setStackedWidgetIndex(0);
    }
 }
//===================================================
void ZWorkController::zp_initStatisticsDisplayFinish()
{
    emit zg_setStackedWidgetIndex(0);
}
//===================================================

