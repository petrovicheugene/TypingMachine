//===================================================
#include "ZTrainingManager.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
//===================================================
ZTrainingManager::ZTrainingManager(QObject *parent)
    : QObject{parent}
{
    zh_createComponents();
    zh_createConnections();

}
//===================================================
bool ZTrainingManager::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(zv_serviceSymbols.contains( keyEvent->key() ))
        {
            return false;
        }

        qDebug() << keyEvent->text() << keyEvent->key();

        return true;
    }

    return false;
}
//===================================================
void ZTrainingManager::zh_createComponents()
{

}
//===================================================
void ZTrainingManager::zh_createConnections()
{

}
//===================================================
void ZTrainingManager::zp_startTask(ZTask task)
{
    qApp->installEventFilter(this);
}
//===================================================
void ZTrainingManager::zp_stopTask()
{
    qApp->removeEventFilter(this);
}
//===================================================
