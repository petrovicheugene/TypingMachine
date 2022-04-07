//===================================================
#include "ZTrainingManager.h"
#include "ZLineControllerCreator.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QRandomGenerator64>
#include <QRegularExpression>

//===================================================
int myrandom (int i) { return std::rand()%i;}
//===================================================
ZTrainingManager::ZTrainingManager(QObject *parent)
    : QObject{parent}
{
    zv_LineController = nullptr;
    zv_taskActive = false;
    zh_createComponents();
    zh_createConnections();

}
//===================================================
bool ZTrainingManager::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // filter by key value
        if(zv_serviceSymbols.contains( keyEvent->key() ))
        {
            return false;
        }

        if(zv_lineCompleted)
        {
            if(keyEvent->key() == zv_lineEndKey)
            {
                zh_nextLine();
            }
            return true;
        }

        //
        zh_handleKeyPress(keyEvent->text());
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
void ZTrainingManager::zp_initTaskStart(ZTask task)
{
    zh_prepareTask(task);
    zh_startTask();
}
//===================================================
void ZTrainingManager::zh_startTask()
{
    //    zv_currentLineIndex = -1;
    //    zv_wrongSymbol = false;
    qApp->installEventFilter(this);
    zv_taskActive = true;
    zh_nextLine();
}
//===================================================
void ZTrainingManager::zp_finishTask()
{
    qApp->removeEventFilter(this);
    zv_taskActive = false;
}
//===================================================
void ZTrainingManager::zp_restartTask()
{
    zv_LineController->zp_reset();
    zh_startTask();
    qDebug() << "RESTART";
}
//===================================================
void ZTrainingManager::zh_prepareTask(ZTask task)
{
    zv_taskName =  std::get<0>(task).c_str();
    zv_lineEndKey = std::get<4>(task);

    // line controller
    if(zv_LineController)
    {
        delete zv_LineController;
    }

    zv_LineController = ZLineControllerCreator::zp_createLineController(task);
    connect(zv_LineController, &ZAbstractLineController::zg_taskCompleted,
            this, &ZTrainingManager::zh_onTaskCompleting);

}
//===================================================
void ZTrainingManager::zh_onTaskCompleting()
{
    qApp->removeEventFilter(this);
    zv_line = tr("TASK COMPLETED");
    zv_taskActive = false;
    emit zg_stateChanged();
}
//===================================================
QString ZTrainingManager::zp_currentLine() const
{
    return zv_line;
}
//===================================================
int ZTrainingManager::zp_currentSymbolIndex() const
{
    return zv_currentSymbolIndex;
}
//===================================================
bool ZTrainingManager::zp_isWrong() const
{
    return zv_wrongSymbolFlag;
}
//===================================================
bool ZTrainingManager::zp_isActive() const
{
    return zv_taskActive;
}
//===================================================
void ZTrainingManager::zh_handleKeyPress(QString symbol)
{
    if(zv_line.at(zv_currentSymbolIndex) != symbol)
    {
        if(!zv_wrongSymbolFlag)
        {
            zv_wrongSymbolFlag = true;
            emit zg_stateChanged();
        }
        return;
    }

    // right symbol
    if(++zv_currentSymbolIndex == zv_line.count())
    {
        // line completed
        zv_lineCompleted = true;
        if(zv_lineEndKey == AUTO)
        {
            zh_nextLine();
            return;
        }
    }

    if(zv_wrongSymbolFlag)
    {
        zv_wrongSymbolFlag = false;
    }

    emit zg_stateChanged();
}
//===================================================
void ZTrainingManager::zh_nextLine()
{
    zv_line = zv_LineController->zp_nextLine();
    zv_wrongSymbolFlag = false;
    zv_lineCompleted = false;
    zv_currentSymbolIndex = 0;

    if(zv_taskActive)
    {
        qDebug() << zv_line;
        emit zg_stateChanged();
    }
}
//===================================================




