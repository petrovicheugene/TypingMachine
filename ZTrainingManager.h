//===================================================
#ifndef ZTRAININGMANAGER_H
#define ZTRAININGMANAGER_H
//===================================================
#include <QObject>
#include <QSet>

#include "ZTask.h"
//===================================================
//===================================================
class ZTrainingManager : public QObject
{
    Q_OBJECT
public:
    explicit ZTrainingManager(QObject *parent = nullptr);


public slots:

    void zp_initTaskStart(ZTask task);
    void zp_stopTask();

protected:

    bool eventFilter(QObject* object, QEvent* event) override;

signals:

private:

    // VARS
    const QSet<int> zv_serviceSymbols = {Qt::Key_Control,
                                         Qt::Key_Alt,
                                         Qt::Key_Shift,
                                         Qt::Key_CapsLock,
                                         Qt::Key_Meta,
                                         Qt::Key_Menu
                                        };

    QStringList zv_chunkList;
    OUTPUT_ORDER zv_outputOrder;
    CHUNK_END_KEY zv_chunkEndKey;
    bool zv_repeat;

    bool zv_chunkCompleted;
    // int zv_chunkCounter;
    int zv_currentSymbolIndex;
    int zv_currentChunkIndex;
    bool zv_wrongSymbol;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    void zh_startTask();

    void zh_prepareTask(ZTask task);
    void zh_handleKeyPress(QString key);


    bool zh_nextChunk();
    int zh_nextChunkIndex();

};
//===================================================
#endif // ZTRAININGMANAGER_H
