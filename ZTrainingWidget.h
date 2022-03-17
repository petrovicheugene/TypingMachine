//===================================================
#ifndef ZTRAININGWIDGET_H
#define ZTRAININGWIDGET_H

#include <QWidget>
//===================================================
class QPushButton;

class ZTaskManager;
//===================================================
class ZTrainingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTrainingWidget(QWidget *parent = nullptr);

    void zp_connectToTaskManager(ZTaskManager* taskManager);

signals:
    void zs_stop();

private:

    // VARS
    QPushButton* zv_stopBtn;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();


};
//===================================================
#endif // ZTRAININGWIDGET_H
