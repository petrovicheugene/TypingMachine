//===================================================
#ifndef ZTASK_H
#define ZTASK_H
//===================================================
#include <tuple>
#include <string>
#include <QMap>
#include <QObject>
//===================================================
enum OUTPUT_CHUNK {WORD,
                   STRING};

enum CHUNK_END_KEY {AUTO = 0,
                    ENTER = Qt::Key_Enter,
                    SPACE = Qt::Key_Space};
//===================================================
extern QMap<OUTPUT_CHUNK, QString> outputChunkStringMap;
extern QMap<CHUNK_END_KEY, QString> chunkEndKeyStringMap;

typedef std::tuple<std::string,
std::string,
OUTPUT_CHUNK,
bool,
bool,
CHUNK_END_KEY> ZTask;

//===================================================
#endif // ZTASK_H
