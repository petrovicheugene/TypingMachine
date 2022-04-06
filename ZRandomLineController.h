//===================================================
#ifndef ZRANDOMLINECONTROLLER_H
#define ZRANDOMLINECONTROLLER_H
//===================================================
#include "ZAbstractLineController.h"
//===================================================
class ZRandomLineController : public ZAbstractLineController
{
    Q_OBJECT
public:
    explicit ZRandomLineController(ZTask& task, QObject* parent = nullptr);

    QString zp_nextLine() override;
    void zp_reset() override;

private:

    // VARS
    bool zv_repeat;
    int zv_index;
    QVector<int> zv_lineIndices;

    // FUNCS
    void zh_initIndices();
    void zh_suffleIndices();

};
//===================================================
#endif // ZRANDOMLINECONTROLLER_H
