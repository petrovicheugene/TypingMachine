//===================================================
#ifndef ZTRAININGWIDGET_H
#define ZTRAININGWIDGET_H

#include <QWidget>
//===================================================
class QLabel;
class QPushButton;
class QSlider;

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
    void zp_setCompletedColor(QColor& color);
    void zp_setCurrentSymbolColor(QColor& color);
    void zp_setWrongSymbolColor(QColor& color);
    void zp_setIncompletedColor(QColor& color);
    void zp_setFontSize(int size);

signals:

    void zg_requestTaskFinish();
    void zg_requestTaskRestart();

private:

    // VARS
    ZTrainingManager* zv_trainingManager;
    QLabel* zv_lineLabel;

    QSlider* zv_fontSizeSlider;
    QPushButton* zv_restartBtn;
    QPushButton* zv_finishBtn;

    int zv_fontSize;
    QColor zv_completedColor;
    QColor zv_currentSymbolColor;
    QColor zv_wrongSymbolColor;
    QColor zv_incompletedColor;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();


};
//===================================================
#endif // ZTRAININGWIDGET_H
