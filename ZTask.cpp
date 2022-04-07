//===================================================
#include "ZTask.h"
//===================================================
QMap<OUTPUT_LINE_TYPE, QString> initOutputLineStringMap()
{
    QMap<OUTPUT_LINE_TYPE, QString> map;
    map.insert(WORD, QObject::tr("Word"));
    map.insert(STRING, QObject::tr("String"));
    return map;
}
//===================================================
QMap<OUTPUT_ORDER, QString> initOutputOrderStringMap()
{
    QMap<OUTPUT_ORDER, QString> map;
    map.insert(RANDOM, QObject::tr("Random"));
    map.insert(SUCCESSIVELY, QObject::tr("Successively"));
    // map.insert(TYPING_SPEED, QObject::tr("Typing speed"));
    return map;
}
//===================================================
QMap<LINE_END_KEY, QString> initLineEndKeyStringMap()
{
    QMap<LINE_END_KEY, QString> map;
    map.insert(AUTO, QObject::tr("Auto"));
    map.insert(RETURN, QObject::tr("Enter"));
    map.insert(SPACE, QObject::tr("Space"));
    return map;
}
//===================================================
QMap<OUTPUT_LINE_TYPE, QString> outputLineStringMap = initOutputLineStringMap();
QMap<OUTPUT_ORDER, QString> outputOrderStringMap = initOutputOrderStringMap();
QMap<LINE_END_KEY, QString> lineEndKeyStringMap = initLineEndKeyStringMap();
//===================================================
