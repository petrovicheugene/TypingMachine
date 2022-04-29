//===================================================
#ifndef ZSTATISTICSWIDGET_H
#define ZSTATISTICSWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QPushButton;
class QTableView;
//===================================================
class ZStatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZStatisticsWidget(QWidget *parent = nullptr);

    void zp_setStatisticsModel(QAbstractItemModel* model);

signals:

    void zg_requestStatisticsDisplayFinish();

private slots:

    void zh_onFinish();

private:

    // VARS
    QPushButton* zv_finishButton;
    QTableView* zv_tableView;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    QWidget* zh_createInfoWidget();
};
//===================================================
#endif // ZSTATISTICSWIDGET_H
