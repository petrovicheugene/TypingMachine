//===================================================
#include "X_TrainingManager.h"
#include "X_LineControllerCreator.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QKeyEvent>
#include <QRegularExpression>
#include <QSettings>
#include <QTimer>
//===================================================
X_TrainingManager::X_TrainingManager(QObject *parent)
    : QObject{parent}
{
    xv_LineController = nullptr;
    xv_currentSymbolIndex = 0;
    xv_wrongSymbolDisplayDuration = 100;
    xv_wrongSymbolDisplayMode = WSSM_WHILE_PRESSED;
    xv_taskState = TS_INACTIVE;

    xh_createComponents();
    xh_createConnections();
    xh_restoreSettings();
}
//===================================================
X_TrainingManager::~X_TrainingManager()
{
    xh_saveSettings();
}
//===================================================
bool X_TrainingManager::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // filter by key value
        if(xv_serviceSymbols.contains( keyEvent->key() ))
        {
            return false;
        }

        // PAUSE
        if(keyEvent->key() == Qt::Key_Pause)
        {
            xh_toggleTaskPause();
            return true;
        }

        if(xv_taskState == TS_PAUSED)
        {
            return false;
        }

        // if(xv_lineCompleted)
        if(xv_currentSymbolIndex == xv_line.count())
        {
            if(keyEvent->key() == xv_lineEndKey)
            {
                xh_prepareNextLine();
                emit xg_lineChanged();
            }
        }
        else
        {
            xh_handleKeyPress(keyEvent->text());
        }

        //        emit xg_symbolPressed(keyEvent->text());

        return true;
    }
    else if(xv_wrongSymbolFlag && event->type() == QEvent::KeyRelease)
    {
        if(xv_wrongSymbolDisplayMode != WSSM_WHILE_PRESSED)
        {
            return true;
        }

        xh_resetSymbol();
        return true;
    }

    return false;
}
//===================================================
void X_TrainingManager::xh_createComponents()
{
    xv_taskDurationTimer = new QTimer(this);
    xv_taskDurationTimer->setTimerType(Qt::PreciseTimer);
    xv_taskDurationTimer->setInterval(1000);
}
//===================================================
void X_TrainingManager::xh_createConnections()
{
    connect(xv_taskDurationTimer, &QTimer::timeout,
            this, &X_TrainingManager::xh_changeDuration);
}
//===================================================
void X_TrainingManager::xh_restoreSettings()
{
    QSettings settings;
    settings.beginGroup("TrainingManager");
    QVariant vData = settings.value("wrongSymbolDisplayDuration");
    if(vData.isValid() && vData.canConvert<int>())
    {
        xv_wrongSymbolDisplayDuration = vData.toInt();
    }

    vData = settings.value("wrongSymbolDisplayMode");
    if(vData.isValid() && vData.canConvert<WRONG_SYMBOL_DISPLAY_MODE>())
    {
        xv_wrongSymbolDisplayMode = vData.value<WRONG_SYMBOL_DISPLAY_MODE>();
    }

    settings.endGroup();
}
//===================================================
void X_TrainingManager::xh_saveSettings() const
{
    QSettings settings;
    settings.beginGroup("TrainingManager");
    settings.setValue("wrongSymbolDisplayDuration", xv_wrongSymbolDisplayDuration);
    settings.setValue("wrongSymbolDisplayMode", xv_wrongSymbolDisplayMode);
    settings.endGroup();

}
//===================================================
void X_TrainingManager::xp_initTaskStart(ZTask task)
{
    xh_prepareTask(task);
    xh_startTask();
}
//===================================================
void X_TrainingManager::xh_startTask()
{
    qApp->installEventFilter(this);
    xh_setTaskState(TS_ACTIVE);
    xh_prepareNextLine();
    emit xg_lineChanged();

    //xv_taskStartTimeMark = QDateTime::currentMSecsSinceEpoch();
    xv_taskDurationSec = 0;
    emit xg_durationChanged(xv_taskDurationSec++);
    xv_taskDurationTimer->start();
}
//===================================================
void X_TrainingManager::xh_toggleTaskPause()
{
    if(xv_taskState == TS_PAUSED)
    {
        xh_setTaskState(TS_ACTIVE);
        xv_taskDurationTimer->start();
    }
    else if(xv_taskState == TS_ACTIVE)
    {
        xh_setTaskState(TS_PAUSED);
        xv_taskDurationTimer->stop();
    }
}
//===================================================
void X_TrainingManager::xp_stopTask()
{
    qDebug() << "FROM TRAINING MNG: TASK STOPPED" ;
    qApp->removeEventFilter(this);
    xh_setTaskState(TS_INACTIVE);
    xv_taskDurationTimer->stop();
}
//===================================================
void X_TrainingManager::xp_finishCompletedTask()
{
    qDebug() << "FROM TRAINING MNG: TASK COMPLETED" ;
    qApp->removeEventFilter(this);
    xh_setTaskState(TS_COMPLETED);
    xv_taskDurationTimer->stop();
}
//===================================================
void X_TrainingManager::xp_restartTask()
{
    xp_stopTask();
    xv_LineController->xp_reset();
    xh_startTask();
}
//===================================================
void X_TrainingManager::xp_setTaskPaused(bool paused)
{
    if(xv_taskState == TS_ACTIVE && paused)
    {
        xh_setTaskState(TS_PAUSED);
        xv_taskDurationTimer->stop();
        //xv_pauseStartTimeMark = QDateTime::currentMSecsSinceEpoch();
    }
    else if(xv_taskState == TS_PAUSED && !paused)
    {
        xh_setTaskState(TS_ACTIVE);
        xv_taskDurationTimer->start();
        //xv_taskStartTimeMark = xv_taskStartTimeMark + (QDateTime::currentMSecsSinceEpoch() - xv_pauseStartTimeMark);
    }
}
//===================================================
void X_TrainingManager::xh_prepareTask(ZTask task)
{
    xv_taskName =  std::get<0>(task).c_str();
    xv_lineEndKey = std::get<4>(task);

    // line controller
    if(xv_LineController)
    {
        delete xv_LineController;
    }

    xv_LineController = X_LineControllerCreator::xp_createLineController(task);
}
//===================================================
QString X_TrainingManager::xp_currentLine() const
{
    return xv_line;
}
//===================================================
int X_TrainingManager::xp_currentSymbolIndex() const
{
    return xv_currentSymbolIndex;
}
//===================================================
QString X_TrainingManager::xp_completedLine() const
{
    if(xv_taskState == TS_COMPLETED)
    {
        return tr("TASK COMPLETED");
    }

    if(xv_taskState == TS_PAUSED)
    {
        return QString();
    }

    if(xv_currentSymbolIndex <= xv_line.count())
    {
        return xv_line.first(xv_currentSymbolIndex);
    }
    else
    {
        return QString();
    }
}
//===================================================
QString X_TrainingManager::xp_currentSymbol() const
{
    if(xv_taskState == TS_ACTIVE)
    {
        return xv_currentSymbol;
    }

    return QString();
}
//===================================================
QString X_TrainingManager::xp_incompletedLine() const
{
    if(xv_taskState == TS_PAUSED)
    {
        return tr("TASK PAUSED");
    }

    if(xv_currentSymbolIndex < xv_line.count())
    {
        return xv_line.last(xv_line.count() - xv_currentSymbolIndex - 1);
    }
    else
    {
        return QString();
    }
}
//===================================================
bool X_TrainingManager::xp_isWrong() const
{
    return xv_wrongSymbolFlag;
}
//===================================================
X_TrainingManager::TASK_STATE X_TrainingManager::xp_taskState() const
{
    return xv_taskState;
}
//===================================================
void X_TrainingManager::xh_handleKeyPress(QString symbol)
{
    // if(xv_line.at(xv_currentSymbolIndex) != symbol)
    if(xv_line.at(xv_currentSymbolIndex) != symbol)
    {
        if(!xv_wrongSymbolFlag)
        {
            xv_wrongSymbolFlag = true;
        }
        emit xg_symbolPressed(symbol);

        // for displaying while the key is pressed
        if(xv_wrongSymbolDisplayMode == WSSM_WHILE_PRESSED)
        {
            xv_currentSymbol = symbol;
        }
        else if(xv_wrongSymbolDisplayMode == WSSM_FOR_TIME)
        {
            xv_currentSymbol = symbol;
            QTimer::singleShot(xv_wrongSymbolDisplayDuration, this, &X_TrainingManager::xh_resetSymbol);
        }
    }
    else
    {
        // right symbol
        if(xv_wrongSymbolFlag)
        {
            xh_resetSymbol();
            xv_wrongSymbolFlag = false;
        }

        // update line
        ++xv_currentSymbolIndex;
        if(xv_currentSymbolIndex == xv_line.count())
        {
            emit xg_symbolPressed(symbol);
            // line completed
            if(xv_lineEndKey == AUTO)
            {
                xh_prepareNextLine();
            }
            else
            {
                // not AUTO next line
                xv_currentSymbol = QString();
            }
        }
        else
        {
            xv_currentSymbol = xv_line.at(xv_currentSymbolIndex);
            emit xg_symbolPressed(symbol);
        }
    }

    emit xg_lineChanged();
}
//===================================================
void X_TrainingManager::xh_resetSymbol()
{
    if(!xv_wrongSymbolFlag)
    {
        return;
    }

    xv_currentSymbol = xv_line.at(xv_currentSymbolIndex);
    emit xg_lineChanged();
}
//===================================================
void X_TrainingManager::xh_changeDuration()
{
    emit xg_durationChanged(++xv_taskDurationSec);
}
//===================================================
void X_TrainingManager::xh_prepareNextLine()
{
    xv_wrongSymbolFlag = false;
    xv_currentSymbolIndex = 0;

    bool taskCompleted = false;
    xv_line = xv_LineController->xp_nextLine(&taskCompleted);

    if(taskCompleted)
    {
        xp_finishCompletedTask();
    }
    else
    {
        xv_currentSymbol = xv_line.at(xv_currentSymbolIndex);
    }
}
//===================================================
int X_TrainingManager::xp_wrongSymbolDisplayDuration() const
{
    return xv_wrongSymbolDisplayDuration;
}
//===================================================
X_TrainingManager::WRONG_SYMBOL_DISPLAY_MODE X_TrainingManager::xp_wrongSymbolDisplayMode() const
{
    return xv_wrongSymbolDisplayMode;
}
//===================================================
void X_TrainingManager::xp_setWrongSymbolDisplayDuration(int value)
{
    if(value < 0 || value > xv_maxWrongSymbolDisplayDuration)
    {
        return;
    }

    xv_wrongSymbolDisplayDuration = value;
}
//================================================
void X_TrainingManager::xp_setWrongSymbolDisplayMode(WRONG_SYMBOL_DISPLAY_MODE mode)
{
    xv_wrongSymbolDisplayMode = mode;
}
//================================================
void X_TrainingManager::xh_setTaskState(TASK_STATE taskState)
{
    auto previous = xv_taskState;
    xv_taskState = taskState;
    emit xg_taskStateChanged(previous, xv_taskState);
}
//================================================



