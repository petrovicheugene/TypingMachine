//===================================================
#ifndef X_STATISTICSWIDGET_H
#define X_STATISTICSWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QPushButton;
class QTableView;
//===================================================
class X_StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit X_StatisticsWidget(QWidget *parent = nullptr);

    void xp_setStatisticsModel(QAbstractItemModel* model);

signals:

    void xg_requestStatisticsDisplayFinish();

private slots:

    void xh_onFinish();

private:

    // VARS
    QPushButton* xv_finishButton;
    QTableView* xv_tableView;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();
    QWidget* xh_createInfoWidget();
};
//===================================================
#endif // X_STATISTICSWIDGET_H
