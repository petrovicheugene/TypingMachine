//===================================================
#ifndef ZTRAININGMANAGER_H
#define ZTRAININGMANAGER_H
//===================================================
#include <QObject>
#include <QSet>

#include "ZAbstractLineController.h"
#include "ZTask.h"

//===================================================
//===================================================
class ZTrainingManager : public QObject
{
    Q_OBJECT
public:
    explicit ZTrainingManager(QObject *parent = nullptr);

    QString zp_currentLine() const;
    QString zp_completed() const;
    QString zp_currentSymbol() const;
    QString zp_incompleted() const;
    int zp_currentSymbolIndex() const;

    bool zp_isWrong() const;
    bool zp_isActive() const;

public slots:

    void zp_initTaskStart(ZTask task);
    void zp_finishTask();
    void zp_restartTask();

protected:

    bool eventFilter(QObject* object, QEvent* event) override;

signals:

    void zg_stateChanged();
    void zg_durationChanged();

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
    bool zv_taskInProgress;
    int zv_currentSymbolIndex;
    bool zv_wrongSymbolFlag;
    QString zv_currentSymbol;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    void zh_startTask();

    void zh_prepareTask(ZTask task);
    void zh_handleKeyPress(QString key);
    void zh_prepareNextLine();

};
//===================================================
#endif // ZTRAININGMANAGER_H
