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
    int zp_currentSymbolIndex() const;
    bool zp_isWrong() const;


public slots:

    void zp_initTaskStart(ZTask task);
    void zp_stopTask();

protected:

    bool eventFilter(QObject* object, QEvent* event) override;

signals:

    void zg_stateChanged();
    void zg_durationChanged();

private slots:

    void zh_onTaskFinish();

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
    int zv_currentSymbolIndex;
    bool zv_wrongSymbolFlag;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    void zh_startTask();

    void zh_prepareTask(ZTask task);
    void zh_handleKeyPress(QString key);
    void zh_nextLine();

};
//===================================================
#endif // ZTRAININGMANAGER_H
