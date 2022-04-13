//===================================================
#include "ZTask.h"
//===================================================
QMap<SPLIT_LINE_BY, QString> initOutputLineStringMap()
{
    QMap<SPLIT_LINE_BY, QString> map;
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
QMap<SPLIT_LINE_BY, QString> splitByStringMap = initOutputLineStringMap();
QMap<OUTPUT_ORDER, QString> outputOrderStringMap = initOutputOrderStringMap();
QMap<LINE_END_KEY, QString> lineEndKeyStringMap = initLineEndKeyStringMap();
//===================================================
