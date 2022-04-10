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
    zv_taskInProgress = false;
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
                zh_prepareNextLine();
            }
            return true;
        }

        zh_handleKeyPress(keyEvent->text());
        return true;
    }
    else if(zv_wrongSymbolFlag && event->type() == QEvent::KeyRelease)
    {
        zv_currentSymbol = zv_line.at(zv_currentSymbolIndex);
        emit zg_stateChanged();
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
    zv_taskInProgress = true;
    zh_prepareNextLine();
}
//===================================================
void ZTrainingManager::zp_finishTask()
{
    qApp->removeEventFilter(this);
    zv_taskInProgress = false;
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
QString ZTrainingManager::zp_completed() const
{
    if(!zv_taskInProgress)
    {
        return tr("TASK COMPLETED");
    }

    if(zv_currentSymbolIndex <= zv_line.count())
    {
        return zv_line.first(zv_currentSymbolIndex);
    }
    else
    {
        return QString();
    }
}
//===================================================
QString ZTrainingManager::zp_currentSymbol() const
{
    return zv_currentSymbol;
}
//===================================================
QString ZTrainingManager::zp_incompleted() const
{
    if(zv_currentSymbolIndex < zv_line.count())
    {
        return zv_line.last(zv_line.count() - zv_currentSymbolIndex - 1);
    }
    else
    {
        return QString();
    }
}
//===================================================
bool ZTrainingManager::zp_isWrong() const
{
    return zv_wrongSymbolFlag;
}
//===================================================
bool ZTrainingManager::zp_isActive() const
{
    return zv_taskInProgress;
}
//===================================================
void ZTrainingManager::zh_handleKeyPress(QString symbol)
{
    // if(zv_line.at(zv_currentSymbolIndex) != symbol)
    if(zv_currentSymbol != symbol)
    {
        if(!zv_wrongSymbolFlag)
        {
            zv_wrongSymbolFlag = true;
        }

        // for displaying while the key is pressed
        zv_currentSymbol = symbol;
        emit zg_stateChanged();
        return;
    }

    // right symbol
    if(zv_wrongSymbolFlag)
    {
        zv_wrongSymbolFlag = false;
    }

    if(++zv_currentSymbolIndex == zv_line.count())
    {
        // line completed
        if(zv_lineEndKey == AUTO)
        {
            zh_prepareNextLine();
            return;
        }
        // not AUTO next line
        zv_lineCompleted = true;
        zv_currentSymbol = QString();
    }
    else
    {
        zv_currentSymbol = zv_line.at(zv_currentSymbolIndex);
    }

    emit zg_stateChanged();
}
//===================================================
void ZTrainingManager::zh_prepareNextLine()
{
    zv_wrongSymbolFlag = false;
    zv_lineCompleted = false;
    zv_currentSymbolIndex = 0;

    zv_line = zv_LineController->zp_nextLine(&zv_taskInProgress);

    if(zv_taskInProgress)
    {
        zv_currentSymbol = zv_line.at(zv_currentSymbolIndex);
        qDebug() << zv_line;
    }
    else // END TASK
    {
        zv_currentSymbol = QString();
        qApp->removeEventFilter(this);
    }

    emit zg_stateChanged();
}
//===================================================




