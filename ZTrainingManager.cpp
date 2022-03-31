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
void ZTrainingManager::zp_startTask(ZTask task)
{
    zh_prepareTask(task);
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
    bool random = std::get<3>(task);
    bool repeat = std::get<4>(task);
    CHUNK_END_KEY chunkEndKey = std::get<5>(task);

    QStringList taskChunks;
    switch(outputChunk)
    {
    case OUTPUT_CHUNK::WORD:
        taskChunks = taskText.split(QRegularExpression ("[\\s\\n]"), Qt::SkipEmptyParts);
        break;
    case OUTPUT_CHUNK::STRING:
        taskChunks = taskText.split(QRegularExpression ("[\\n]"));
        break;
    }

    qDebug() << taskName;
    qDebug() << taskChunks;
    qDebug() << outputChunk;
    qDebug() << random;
    qDebug() << repeat;
    qDebug() << chunkEndKey;
    qDebug() << "qqq";

    //    if(task.)
    //    {

    //    }
    // zv_chunkList
}
//===================================================


