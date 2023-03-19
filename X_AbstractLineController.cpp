//===================================================
#include "X_AbstractLineController.h"
#include <QDebug>
#include <QRegularExpression>
//===================================================
X_AbstractLineController::X_AbstractLineController(X_Task& task, QObject *parent)
    : QObject{parent}
{
    QString taskContent = std::get<1>(task).c_str();
    SPLIT_LINE_BY outputLineType = std::get<2>(task);

    switch(outputLineType)
    {
    case SPLIT_LINE_BY::WORD:
        static QRegularExpression reWord("[\\t\\s\\n]");
        xv_lineList = taskContent.split(reWord, Qt::SkipEmptyParts);
        break;
    case SPLIT_LINE_BY::STRING:
        static QRegularExpression reLine("[\\n]");
        xv_lineList = taskContent.split(reLine, Qt::SkipEmptyParts);

        // removing starting and ending spaces
        for(int i = 0; i < xv_lineList.count(); ++i)
        {
            xv_lineList[i] = xv_lineList.at(i).trimmed();
        }
    }

 }
//===================================================
