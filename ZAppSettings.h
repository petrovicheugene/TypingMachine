//===================================================
#ifndef ZAPPSETTINGS_H
#define ZAPPSETTINGS_H
//===================================================
#include <QMap>
#include <QMetaType>
#include <QString>

enum SETTING_NAMES {SN_COMPLETED_COLOR=0,
                   SN_CURRENT_COLOR=1,
                   SN_INCOMPLETED_COLOR=2,
                   SN_WRONG_COLOR=3};

typedef QMap<int, QVariant> ZAppSettings;

//Q_DECLARE_METATYPE(ZAppSettings);
#endif // ZAPPSETTINGS_H
//===================================================
