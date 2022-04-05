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
                zh_nextLine();
            }
            return true;
        }

        //
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
    //    zv_currentLineIndex = -1;
    //    zv_wrongSymbol = false;

    zh_nextLine();
    qApp->installEventFilter(this);
}
//===================================================
void ZTrainingManager::zp_stopTask()
{
    zv_LineController->zp_reset();
    qApp->removeEventFilter(this);
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
    connect(zv_LineController, &ZAbstractLineController::zg_taskFinished,
            this, &ZTrainingManager::zh_onTaskFinish);

}
//===================================================
void ZTrainingManager::zh_onTaskFinish()
{
    qDebug() << "TASK FINISHED";
}
//===================================================
//std::vector<int> ZTrainingManager::zh_createKeyVector() const
//{
//    std::vector<int> keyVector = zh_createKeyVector();

//    if(zv_outputOrder == SUCCESSIVELY)
//    {
//        for (int i = 0; i < lineList.count(); ++i)
//        {
//            keyVector.push_back(i);
//        }
//    }
//    else if (zv_outputOrder == RANDOM)
//    {
//        for (int i = 0; i < lineList.count(); ++i)
//        {
//            keyVector.push_back(i);
//        }

//        std::srand(unsigned(std::time(0)));
//        std::random_shuffle(keyVector.begin(), keyVector.end(), myrandom);
//    }

//}
//===================================================
void ZTrainingManager::zh_handleKeyPress(QString symbol)
{
    if(zv_line.at(zv_currentSymbolIndex) != symbol)
    {
        zv_wrongSymbol = true;
        qDebug() << "Wrong Symbol";
        return;
    }

    // right symbol
    zv_wrongSymbol = false;

    if(++zv_currentSymbolIndex == zv_line.count())
    {
        // line completed
        zv_lineCompleted = true;
        if(zv_lineEndKey == AUTO)
        {
            zh_nextLine();
        }
    }
}
//===================================================
void ZTrainingManager::zh_nextLine()
{
    zv_line = zv_LineController->zp_nextLine();
    zv_wrongSymbol = false;
    zv_lineCompleted = false;
    zv_currentSymbolIndex = 0;

    qDebug() << zv_line;
}
//===================================================




