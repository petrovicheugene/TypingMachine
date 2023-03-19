//===================================================
#ifndef X_TASK_H
#define X_TASK_H
//===================================================
#include <tuple>
#include <string>
#include <QMap>
#include <QObject>
//===================================================
enum SPLIT_LINE_BY {WORD,
                     STRING};

enum LINE_END_KEY {AUTO = 0,
                    RETURN = Qt::Key_Return,
                    SPACE = Qt::Key_Space};

enum OUTPUT_ORDER {RANDOM = 0,
                    SUCCESSIVELY = 1,
                    TYPING_SPEED = 2
};

//===================================================
extern QMap<SPLIT_LINE_BY, QString> splitByStringMap;
extern QMap<OUTPUT_ORDER, QString> outputOrderStringMap;
extern QMap<LINE_END_KEY, QString> lineEndKeyStringMap;

//===================================================
typedef std::tuple<std::string,
                   std::string,
                   SPLIT_LINE_BY,
                   OUTPUT_ORDER,
                   LINE_END_KEY,
                   bool> X_Task;

//===================================================
#endif // X_TASK_H
