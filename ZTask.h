//===================================================
#ifndef ZTASK_H
#define ZTASK_H
//===================================================
#include <tuple>
#include <string>
#include <QMap>
#include <QObject>
//===================================================
enum OUTPUT_LINE_TYPE {WORD,
                   STRING};

enum LINE_END_KEY {AUTO = 0,
                    RETURN = Qt::Key_Return,
                    SPACE = Qt::Key_Space};

enum OUTPUT_ORDER {RANDOM = 0,
                   SUCCESSIVELY = 1,
                   TYPING_SPEED = 2
                  };

//===================================================
extern QMap<OUTPUT_LINE_TYPE, QString> outputLineStringMap;
extern QMap<OUTPUT_ORDER, QString> outputOrderStringMap;
extern QMap<LINE_END_KEY, QString> lineEndKeyStringMap;

//===================================================
typedef std::tuple<std::string,
std::string,
OUTPUT_LINE_TYPE,
OUTPUT_ORDER,
LINE_END_KEY,
bool> ZTask;

//===================================================
#endif // ZTASK_H
