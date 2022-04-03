//===================================================
#include "ZTrainingManager.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QRegularExpression>
//===================================================
ZTrainingManager::ZTrainingManager(QObject *parent)
    : QObject{parent}
{
    zh_createComponents();
    zh_createConnections();

}
//===================================================
bool ZTrainingManager::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(zv_serviceSymbols.contains( keyEvent->key() ))
        {
            return false;
        }

        if(zv_chunkCompleted)
        {
            if(keyEvent->key() == zv_chunkEndKey)
            {
                zh_nextChunk();
            }
            return true;
        }

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
    zv_currentChunkIndex = -1;
    zv_wrongSymbol = false;

    zh_nextChunk();
    qApp->installEventFilter(this);

}
//===================================================
void ZTrainingManager::zp_stopTask()
{
    qApp->removeEventFilter(this);
}
//===================================================
void ZTrainingManager::zh_prepareTask(ZTask task)
{
    //  qDebug() << std::get<>(task);
    QString taskName =  std::get<0>(task).c_str();
    QString taskText = std::get<1>(task).c_str();
    OUTPUT_CHUNK outputChunk = std::get<2>(task);
    zv_outputOrder = std::get<3>(task);
    zv_chunkEndKey = std::get<4>(task);
    zv_repeat = std::get<5>(task);

    switch(outputChunk)
    {
    case OUTPUT_CHUNK::WORD:
        zv_chunkList = taskText.split(QRegularExpression ("[\\s\\n]"), Qt::SkipEmptyParts);
        break;
    case OUTPUT_CHUNK::STRING:
        zv_chunkList = taskText.split(QRegularExpression ("[\\n]"));
        break;
    }
}
//===================================================
bool ZTrainingManager::zh_nextChunk()
{
    zv_chunkCompleted = false;
    zv_currentSymbolIndex = 0;
    if(!zh_nextChunkIndex())
    {
        // task completed
        qDebug() << "TASK COMPLETED";
        zp_stopTask();
        // NOTE: END TASK NOTIFICATION
        return false;
    }

    qDebug() << "NEXT CHUNK" << zv_chunkList.at(zv_currentChunkIndex);


    return true;

    //zv_chunkCounter;
}
//===================================================
int ZTrainingManager::zh_nextChunkIndex()
{
    // successively output
    if(++zv_currentChunkIndex == zv_chunkList.count())
    {
        zv_currentChunkIndex = 0;
        if(!zv_repeat)
        {
            return false;
        }
    }

    return true;
}
//===================================================
void ZTrainingManager::zh_handleKeyPress(QString symbol)
{
    if(zv_chunkList.at(zv_currentChunkIndex).at(zv_currentSymbolIndex) != symbol)
    {
        zv_wrongSymbol = true;
        qDebug() << "Wrong Symbol";
        return;
    }

    if(++zv_currentSymbolIndex == zv_chunkList.at(zv_currentChunkIndex).count())
    {
        // chunk completed
        if(zv_chunkEndKey == AUTO)
        {
            zh_nextChunk();
            return;
        }

        zv_chunkCompleted = true;
    }
}
//===================================================




