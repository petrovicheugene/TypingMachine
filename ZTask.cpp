//===================================================
#include "ZTask.h"
//===================================================
QMap<OUTPUT_CHUNK, QString> initOutputChunkStringMap()
{
    QMap<OUTPUT_CHUNK, QString> map;
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
    return map;
}
//===================================================
QMap<CHUNK_END_KEY, QString> initChunkEndKeyStringMap()
{
    QMap<CHUNK_END_KEY, QString> map;
    map.insert(AUTO, QObject::tr("Auto"));
    map.insert(RETURN, QObject::tr("Enter"));
    map.insert(SPACE, QObject::tr("Space"));
    return map;
}
//===================================================
QMap<OUTPUT_CHUNK, QString> outputChunkStringMap = initOutputChunkStringMap();
QMap<OUTPUT_ORDER, QString> outputOrderStringMap = initOutputOrderStringMap();
QMap<CHUNK_END_KEY, QString> chunkEndKeyStringMap = initChunkEndKeyStringMap();
//===================================================
