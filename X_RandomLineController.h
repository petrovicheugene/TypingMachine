//===================================================
#ifndef X_RANDOMLINECONTROLLER_H
#define X_RANDOMLINECONTROLLER_H
//===================================================
#include "X_AbstractLineController.h"
//===================================================
class X_RandomLineController : public X_AbstractLineController
{
    Q_OBJECT
public:
    explicit X_RandomLineController(ZTask& task, QObject* parent = nullptr);

    QString xp_nextLine(bool* completed = nullptr) override;
    void xp_reset() override;

private:

    // VARS
    bool xv_repeat;
    int xv_index;
    QVector<int> xv_lineIndices;

    // FUNCS
    void xh_initIndices();
    void xh_suffleIndices();

};
//===================================================
#endif // X_RANDOMLINECONTROLLER_H
