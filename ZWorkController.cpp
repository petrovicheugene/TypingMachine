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
void ZWorkController::zp_setTaskSource(ZTaskSource* taskSource)
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
void ZWorkController::zp_initTaskFinish()
{
    emit zg_requestTaskFinish();
    emit zg_setStackedWidgetIndex(2);
}
//===================================================
void ZWorkController::zp_initStatisticsDisplayFinish()
{
    emit zg_setStackedWidgetIndex(0);
}
//===================================================

