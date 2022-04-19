//===================================================
#ifndef ZTRAININGMANAGER_H
#define ZTRAININGMANAGER_H
//===================================================
#include <QObject>
#include <QSet>

#include "ZAbstractLineController.h"
#include "ZTask.h"

//===================================================
class QTimer;
//===================================================
class ZTrainingManager : public QObject
{
    Q_OBJECT
public:
    explicit ZTrainingManager(QObject *parent = nullptr);
    ~ZTrainingManager();

    enum WRONG_SYMBOL_DISPLAY_MODE {WSSM_DONT_DISPLAY = 0,
                                 WSSM_WHILE_PRESSED = 1,
                                 WSSM_FOR_TIME = 2};

    QString zp_currentLine() const;
    QString zp_completed() const;
    QString zp_currentSymbol() const;
    QString zp_incompleted() const;
    int zp_currentSymbolIndex() const;

    bool zp_isWrong() const;
    bool zp_isInProgress() const;

    int zp_wrongSymbolDisplayDuration() const;
    WRONG_SYMBOL_DISPLAY_MODE zp_wrongSymbolDisplayMode() const;

public slots:

    void zp_initTaskStart(ZTask task);
    void zp_finishTask();
    void zp_restartTask();

    void zp_setWrongSymbolDisplayDuration(int value);
    void zp_setWrongSymbolDisplayMode(WRONG_SYMBOL_DISPLAY_MODE mode);

protected:

    bool eventFilter(QObject* object, QEvent* event) override;

signals:

    void zg_stateChanged();
    void zg_durationChanged(int duration);


private slots:

    void zh_resetSymbol();
    void zh_changeDuration();

private:

    // VARS
    const QSet<int> zv_serviceSymbols = {Qt::Key_Control,
                                         Qt::Key_Alt,
                                         Qt::Key_Shift,
                                         Qt::Key_CapsLock,
                                         Qt::Key_Meta,
                                         Qt::Key_Menu
                                        };

    QString zv_taskName;
    QString zv_line;
    ZAbstractLineController* zv_LineController;
    LINE_END_KEY zv_lineEndKey;

    bool zv_lineCompleted;
    bool zv_taskCompleted;
    // bool zv_paused;
    int zv_currentSymbolIndex;
    bool zv_wrongSymbolFlag;
    QString zv_currentSymbol;

    QTimer* zv_taskDurationTimer;
    int zv_taskDurationSec;


    const int zv_maxWrongSymbolDuration = 3000;
    int zv_wrongSymbolDisplayDuration;
    WRONG_SYMBOL_DISPLAY_MODE zv_wrongSymbolDisplayMode;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    void zh_restoreSettings();
    void zh_saveSettings() const;
    void zh_startTask();

    void zh_prepareTask(ZTask task);
    void zh_handleKeyPress(QString key);
    void zh_prepareNextLine();

};
//===================================================
#endif // ZTRAININGMANAGER_H
