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
                    RETURN = Qt::Key_Return,
                    SPACE = Qt::Key_Space};

enum OUTPUT_ORDER {RANDOM = 0,
                    SUCCESSIVELY = 1,
                    };

//===================================================
extern QMap<OUTPUT_CHUNK, QString> outputChunkStringMap;
extern QMap<OUTPUT_ORDER, QString> outputOrderStringMap;
extern QMap<CHUNK_END_KEY, QString> chunkEndKeyStringMap;

//===================================================
typedef std::tuple<std::string,
std::string,
OUTPUT_CHUNK,
OUTPUT_ORDER,
CHUNK_END_KEY,
bool> ZTask;

//===================================================
#endif // ZTASK_H
