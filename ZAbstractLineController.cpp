//===================================================
#include "ZAbstractLineController.h"
#include <QDebug>
#include <QRegularExpression>
//===================================================
ZAbstractLineController::ZAbstractLineController(ZTask& task, QObject *parent)
    : QObject{parent}
{
    QString taskContent = std::get<1>(task).c_str();
    OUTPUT_LINE_TYPE outputLineType = std::get<2>(task);

    switch(outputLineType)
    {
    case OUTPUT_LINE_TYPE::WORD:
        zv_lineList = taskContent.split(QRegularExpression ("[\\s\\n]"), Qt::SkipEmptyParts);
        break;
    case OUTPUT_LINE_TYPE::STRING:
        zv_lineList = taskContent.split(QRegularExpression ("[\\n]"), Qt::SkipEmptyParts);
        break;
    }
 }
//===================================================
