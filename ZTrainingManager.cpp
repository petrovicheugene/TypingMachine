//===================================================
#include "ZTrainingManager.h"
#include "ZLineControllerCreator.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QSettings>
#include <QTimer>
//===================================================
ZTrainingManager::ZTrainingManager(QObject *parent)
    : QObject{parent}
{
    zv_LineController = nullptr;
    zv_currentSymbolIndex = 0;
    zv_wrongSymbolDisplayDuration = 100;
    zv_wrongSymbolDisplayMode = WSSM_WHILE_PRESSED;
    zv_taskState = TS_INACTIVE;

    zh_createComponents();
    zh_createConnections();
    zh_restoreSettings();
}
//===================================================
ZTrainingManager::~ZTrainingManager()
{
    zh_saveSettings();
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

        // PAUSE
        if(keyEvent->key() == Qt::Key_Pause)
        {
            zh_toggleTaskPause();
            return true;
        }

        if(zv_taskState == TS_PAUSED)
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
        if(zv_wrongSymbolDisplayMode != WSSM_WHILE_PRESSED)
        {
            return true;
        }

        zh_resetSymbol();
        return true;
    }

    return false;
}
//===================================================
void ZTrainingManager::zh_createComponents()
{
    zv_taskDurationTimer = new QTimer(this);
    zv_taskDurationTimer->setTimerType(Qt::PreciseTimer);
    zv_taskDurationTimer->setInterval(1000);
}
//===================================================
void ZTrainingManager::zh_createConnections()
{
    connect(zv_taskDurationTimer, &QTimer::timeout,
            this, &ZTrainingManager::zh_changeDuration);
}
//===================================================
void ZTrainingManager::zh_restoreSettings()
{
    QSettings settings;
    settings.beginGroup("TrainingManager");
    QVariant vData = settings.value("wrongSymbolDisplayDuration");
    if(vData.isValid() && vData.canConvert<int>())
    {
        zv_wrongSymbolDisplayDuration = vData.toInt();
    }

    vData = settings.value("wrongSymbolDisplayMode");
    if(vData.isValid() && vData.canConvert<WRONG_SYMBOL_DISPLAY_MODE>())
    {
        zv_wrongSymbolDisplayMode = vData.value<WRONG_SYMBOL_DISPLAY_MODE>();
    }

    settings.endGroup();
}
//===================================================
void ZTrainingManager::zh_saveSettings() const
{
    QSettings settings;
    settings.beginGroup("TrainingManager");
    settings.setValue("wrongSymbolDisplayDuration", zv_wrongSymbolDisplayDuration);
    settings.setValue("wrongSymbolDisplayMode", zv_wrongSymbolDisplayMode);
    settings.endGroup();

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
    qApp->installEventFilter(this);
    zv_taskState = TS_ACTIVE;
    zh_prepareNextLine();
    zv_taskDurationSec = 0;
    emit zg_durationChanged(++zv_taskDurationSec);
    zv_taskDurationTimer->start();
}
//===================================================
void ZTrainingManager::zh_toggleTaskPause()
{
    if(zv_taskState == TS_PAUSED)
    {
        zv_taskState = TS_ACTIVE;
        zv_taskDurationTimer->start();
    }
    else if(zv_taskState == TS_ACTIVE)
    {
        zv_taskState = TS_PAUSED;
        zv_taskDurationTimer->stop();
    }

    qDebug() << "TASK STATE" << zv_taskState;
    emit zg_stateChanged();
}
//===================================================
void ZTrainingManager::zp_finishTask()
{
    qApp->removeEventFilter(this);
    zv_taskState = TS_COMPLETED;
    zv_taskDurationTimer->stop();
    emit zg_stateChanged();
}
//===================================================
void ZTrainingManager::zp_restartTask()
{
    zv_LineController->zp_reset();
    zh_startTask();
}
//===================================================
void ZTrainingManager::zp_setTaskPaused(bool paused)
{
    if(zv_taskState == TS_ACTIVE && paused)
    {
        zv_taskState = TS_PAUSED;
        zv_taskDurationTimer->stop();
    }
    else if(zv_taskState == TS_PAUSED && !paused)
    {
        zv_taskState = TS_ACTIVE;
        zv_taskDurationTimer->start();
    }

    qDebug() << "TASK STATE" << zv_taskState;
    emit zg_stateChanged();
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
QString ZTrainingManager::zp_completedLine() const
{
    if(zv_taskState == TS_COMPLETED)
    {
        return tr("TASK COMPLETED");
    }

    if(zv_taskState == TS_PAUSED)
    {
        return QString();
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
    if(zv_taskState == TS_ACTIVE)
    {
        return zv_currentSymbol;
    }

    return QString();
}
//===================================================
QString ZTrainingManager::zp_incompletedLine() const
{
    if(zv_taskState == TS_PAUSED)
    {
        return tr("TASK PAUSED");
    }

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
ZTrainingManager::TASK_STATE ZTrainingManager::zp_taskState() const
{
    return zv_taskState;
}
//===================================================
void ZTrainingManager::zh_handleKeyPress(QString symbol)
{
    // if(zv_line.at(zv_currentSymbolIndex) != symbol)
    if(zv_line.at(zv_currentSymbolIndex) != symbol)
    {
        if(!zv_wrongSymbolFlag)
        {
            zv_wrongSymbolFlag = true;
        }

        // for displaying while the key is pressed
        if(zv_wrongSymbolDisplayMode == WSSM_WHILE_PRESSED)
        {
            zv_currentSymbol = symbol;
        }
        else if(zv_wrongSymbolDisplayMode == WSSM_FOR_TIME)
        {
            zv_currentSymbol = symbol;
            QTimer::singleShot(zv_wrongSymbolDisplayDuration, this, &ZTrainingManager::zh_resetSymbol);
        }

        emit zg_wrongSymbolPressed();
        emit zg_stateChanged();
        return;
    }

    // right symbol
    if(zv_wrongSymbolFlag)
    {
        zh_resetSymbol();
        zv_wrongSymbolFlag = false;
    }

    ++zv_currentSymbolIndex;
    if(zv_currentSymbolIndex == zv_line.count())
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
void ZTrainingManager::zh_resetSymbol()
{
    if(!zv_wrongSymbolFlag)
    {
        return;
    }

    zv_currentSymbol = zv_line.at(zv_currentSymbolIndex);
    emit zg_stateChanged();
}
//===================================================
void ZTrainingManager::zh_changeDuration()
{
    emit zg_durationChanged(++zv_taskDurationSec);
}
//===================================================
void ZTrainingManager::zh_prepareNextLine()
{
    zv_wrongSymbolFlag = false;
    zv_lineCompleted = false;
    zv_currentSymbolIndex = 0;

    bool taskCompleted = false;
    zv_line = zv_LineController->zp_nextLine(&taskCompleted);

    if(taskCompleted)
    {
        zp_finishTask();
        return;
    }

    zv_currentSymbol = zv_line.at(zv_currentSymbolIndex);
    emit zg_stateChanged();
}
//===================================================
int ZTrainingManager::zp_wrongSymbolDisplayDuration() const
{
    return zv_wrongSymbolDisplayDuration;
}
//===================================================
ZTrainingManager::WRONG_SYMBOL_DISPLAY_MODE ZTrainingManager::zp_wrongSymbolDisplayMode() const
{
    return zv_wrongSymbolDisplayMode;
}
//===================================================
void ZTrainingManager::zp_setWrongSymbolDisplayDuration(int value)
{
    if(value < 0 || value > zv_maxWrongSymbolDuration)
    {
        return;
    }

    zv_wrongSymbolDisplayDuration = value;
}
//================================================
void ZTrainingManager::zp_setWrongSymbolDisplayMode(WRONG_SYMBOL_DISPLAY_MODE mode)
{
    zv_wrongSymbolDisplayMode = mode;
}
//================================================




