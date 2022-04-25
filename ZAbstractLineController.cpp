//===================================================
#include "ZAbstractLineController.h"
#include <QDebug>
#include <QRegularExpression>
//===================================================
ZAbstractLineController::ZAbstractLineController(ZTask& task, QObject *parent)
    : QObject{parent}
{
    QString taskContent = std::get<1>(task).c_str();
    SPLIT_LINE_BY outputLineType = std::get<2>(task);

    switch(outputLineType)
    {
    case SPLIT_LINE_BY::WORD:
        static QRegularExpression reWord("[\\t\\s\\n]");
        zv_lineList = taskContent.split(reWord, Qt::SkipEmptyParts);
        break;
    case SPLIT_LINE_BY::STRING:
        static QRegularExpression reLine("[\\n]");
        zv_lineList = taskContent.split(reLine, Qt::SkipEmptyParts);

        // removing starting and ending spaces
        for(int i = 0; i < zv_lineList.count(); ++i)
        {
            zv_lineList[i] = zv_lineList.at(i).trimmed();
        }
    }

 }
//===================================================
