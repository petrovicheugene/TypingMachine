//===================================================
#include "ZTaskManager.h"

//#include <Q>
//===================================================
ZTaskManager::ZTaskManager(QObject *parent)
    : QObject{parent}
{
    zh_createComponents();
    zh_createConnections();
}
//===================================================
QAbstractItemModel* ZTaskManager::zp_taskModel() const
{
    return nullptr;
}
//===================================================
void ZTaskManager::zh_createComponents()
{
    //zv_model = new QTab
}
//===================================================
void ZTaskManager::zh_createConnections()
{

}
//===================================================

