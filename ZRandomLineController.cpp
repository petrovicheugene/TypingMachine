//===================================================
#include "ZRandomLineController.h"
#include <QDebug>
//===================================================
ZRandomLineController::ZRandomLineController(ZTask &task, QObject *parent) :
    ZAbstractLineController{task, parent}
{
    zv_index = 0;
    zv_repeat = std::get<5>(task);
    zh_initIndices();
    zh_suffleIndices();
}
//===================================================
QString ZRandomLineController::zp_nextLine()
{
    if(zv_lineList.isEmpty())
    {
        emit zg_taskCompleted();
        return QString();
    }

    if(zv_index == zv_lineList.count())
    {
        zv_index = 0;
        zh_suffleIndices();
        if(!zv_repeat)
        {
            emit zg_taskCompleted();
            return QString();
        }
    }

    return zv_lineList.at(zv_lineIndices.at(zv_index++));
}
//===================================================
void ZRandomLineController::zp_reset()
{
    zv_index = 0;
    zh_initIndices();

}
//===================================================
void ZRandomLineController::zh_initIndices()
{
    for(int i = 0; i < zv_lineList.count(); ++i)
    {
        zv_lineIndices.append(i);
    }
}
//===================================================
void ZRandomLineController::zh_suffleIndices()
{
    std::random_shuffle(zv_lineIndices.begin(), zv_lineIndices.end());
}
//===================================================


