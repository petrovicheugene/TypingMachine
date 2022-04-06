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

    zh_nextLine();
    qApp->installEventFilter(this);
}
//===================================================
void ZTrainingManager::zp_stopTask()
{
    zv_LineController->zp_reset();
    qApp->removeEventFilter(this);
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
    connect(zv_LineController, &ZAbstractLineController::zg_taskFinished,
            this, &ZTrainingManager::zh_onTaskFinish);

}
//===================================================
void ZTrainingManager::zh_onTaskFinish()
{
    qDebug() << "TASK FINISHED";
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
    if(zv_wrongSymbolFlag)
    {
        zv_wrongSymbolFlag = false;
        emit zg_stateChanged();
    }

    if(++zv_currentSymbolIndex == zv_line.count())
    {
        // line completed
        zv_lineCompleted = true;
        if(zv_lineEndKey == AUTO)
        {
            zh_nextLine();
        }
    }

//    emit zg_stateChanged();
}
//===================================================
void ZTrainingManager::zh_nextLine()
{
    zv_line = zv_LineController->zp_nextLine();
    zv_wrongSymbolFlag = false;
    zv_lineCompleted = false;
    zv_currentSymbolIndex = 0;

    emit zg_stateChanged();

    // qDebug() << zv_line;
}
//===================================================




