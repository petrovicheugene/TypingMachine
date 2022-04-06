//===================================================
#ifndef ZTRAININGWIDGET_H
#define ZTRAININGWIDGET_H

#include <QWidget>
//===================================================
class QPushButton;

class ZTrainingManager;
//===================================================
class ZTrainingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTrainingWidget(QWidget *parent = nullptr);

    void zp_connectToTrainingManager(ZTrainingManager* manager);

public slots:

    void zp_update();

signals:

    void zg_requestTaskStop();

private:

    // VARS
    ZTrainingManager* zv_trainingManager;
    QPushButton* zv_stopBtn;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();


};
//===================================================
#endif // ZTRAININGWIDGET_H
