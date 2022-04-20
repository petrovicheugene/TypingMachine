//===================================================
#ifndef ZSTATISTICSWIDGET_H
#define ZSTATISTICSWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QPushButton;
//===================================================
class ZStatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZStatisticsWidget(QWidget *parent = nullptr);

signals:

    void zg_requestStatisticsDisplayFinish();

private:

    // VARS
    QPushButton* zv_finishButton;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

};
//===================================================
#endif // ZSTATISTICSWIDGET_H
