//===================================================
#ifndef X_TRAININGMANAGER_H
#define X_TRAININGMANAGER_H
//===================================================
#include <QObject>
#include <QSet>

#include "X_AbstractLineController.h"
#include "X_Task.h"

//===================================================
class QTimer;
//===================================================
class X_TrainingManager : public QObject
{
    Q_OBJECT
public:
    explicit X_TrainingManager(QObject *parent = nullptr);
    ~X_TrainingManager();

    enum WRONG_SYMBOL_DISPLAY_MODE {WSSM_DONT_DISPLAY = 0,
                                     WSSM_WHILE_PRESSED = 1,
                                     WSSM_FOR_TIME = 2};
    
    enum TASK_STATUS {TS_READY, // task is ready for competing all timings pending for first key
                      TS_INACTIVE, // initial state
                      TS_ACTIVE,  // task is being completed
                      TS_PAUSED, // task is being paused
                      TS_COMPLETED}; // task completed



    QString xp_currentLine() const;
    QString xp_completedLine() const;
    QString xp_currentSymbol() const;
    QString xp_incompletedLine() const;
    int xp_currentSymbolIndex() const;

    bool xp_isWrong() const;
    
    TASK_STATUS xp_currentTaskStatus() const;

    int xp_wrongSymbolDisplayDuration() const;
    WRONG_SYMBOL_DISPLAY_MODE xp_wrongSymbolDisplayMode() const;

public slots:

    void xp_initTaskStart(X_Task task);
    void xp_stopTask();
    void xp_finishCompletedTask();
    void xp_restartTask();
    void xp_switchTaskPaused(bool paused);

    void xp_setWrongSymbolDisplayDuration(int value);
    void xp_setWrongSymbolDisplayMode(X_TrainingManager::WRONG_SYMBOL_DISPLAY_MODE mode);

protected:

    bool eventFilter(QObject* object, QEvent* event) override;

signals:

    void xg_lineChanged();
    void xg_durationChanged(int duration);
    void xg_infoChanged(const QString& infoMsg);
    void xg_taskStatusChanged(X_TrainingManager::TASK_STATUS previous,
                             X_TrainingManager::TASK_STATUS current);
    void xg_symbolPressed(QString pressedSymbol);

private slots:

    void xh_resetSymbol();
    void xh_changeDuration();

private:

    // VARS
    const QSet<int> xv_serviceSymbols = {Qt::Key_Control,
        Qt::Key_Alt,
        Qt::Key_Shift,
        Qt::Key_CapsLock,
        Qt::Key_Meta,
        Qt::Key_Menu
    };

    QString xv_taskName;
    QString xv_line;
    X_AbstractLineController* xv_LineController;
    LINE_END_KEY xv_lineEndKey;
    
    TASK_STATUS xv_taskStatus;

    int xv_currentSymbolIndex;
    bool xv_wrongSymbolFlag;
    QString xv_currentSymbol;


    QTimer* xv_taskDurationTimer;
    int xv_taskDurationSec;
    //    qint64 xv_taskStartTimeMark;
    //    qint64 xv_pauseStartTimeMark;

    const int xv_maxWrongSymbolDisplayDuration = 3000;
    int xv_wrongSymbolDisplayDuration;
    WRONG_SYMBOL_DISPLAY_MODE xv_wrongSymbolDisplayMode;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();
    void xh_restoreSettings();
    void xh_saveSettings() const;
    void xh_startTask();
    void xh_toggleTaskPause();

    void xh_prepareTask(X_Task task);
    void xh_handleKeyPress(QString key);
    void xh_prepareNextLine();
    void xh_setTaskStatus(TASK_STATUS taskStatus);
};
//===================================================
#endif // X_TRAININGMANAGER_H
