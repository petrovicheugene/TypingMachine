//===================================================
#ifndef ZTRAININGWIDGET_H
#define ZTRAININGWIDGET_H

#include <QWidget>
#include <QColor>
//===================================================
class QLabel;
class QPushButton;
class QSlider;

class ZClickableLabel;
class ZTrainingManager;
//===================================================
class ZTrainingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTrainingWidget(QWidget *parent = nullptr);
    ~ZTrainingWidget();

    void zp_connectToTrainingManager(ZTrainingManager* manager);

    QColor zp_completedColor() const;
    QColor zp_currentSymbolColor() const;
    QColor zp_wrongSymbolColor() const;
    QColor zp_incompletedColor() const;

    bool zp_isSymbolUnderlined() const;

    QColor zp_infoColor() const;
    bool zp_isTaskDurationDisplayed() const;
    int zp_infoFontSize() const;

public slots:

    void zp_update();
    void zp_updateDuration(int duration);

    void zp_setFontSize(int size);

    void zp_setCompletedColor(QColor color);
    void zp_setCurrentSymbolColor(QColor color);
    void zp_setWrongSymbolColor(QColor color);
    void zp_setIncompletedColor(QColor color);
    void zp_setCurrentSymbolUnderlined(bool underlined);

    void zp_setInfoColor(QColor color);
    void zp_setTaskDurationDisplayFlag(bool displayFlag);
    void zp_setInfoFontSize(int size);
    void zp_setInfoFontSizeString(QString size);

signals:

    void zg_requestTaskFinish();
    void zg_requestTaskRestart();
    void zg_requestTaskPauseToggle(bool paused);

private slots:

    void zh_setFontSize(int size);
    void zh_changeFontSizeSliderValue();
    void zp_onTaskPauseToggle(bool checked);

private:

    // VARS
    ZTrainingManager* zv_trainingManager;
    QLabel* zv_lineLabel;
    QLabel* zv_taskDurationLabel;

    ZClickableLabel* zv_minusLabel;
    ZClickableLabel* zv_plusLabel;

    QSlider* zv_fontSizeSlider;
    QPushButton* zv_restartButton;
    QPushButton* zv_pauseButton;
    QPushButton* zv_finishButton;

    int zv_fontSize;
    QColor zv_completedColor;
    QColor zv_currentSymbolColor;
    QColor zv_wrongSymbolColor;
    QColor zv_incompletedColor;
    bool zv_symbolUnderlinedFlag;

    QColor zv_infoColor;
    bool zv_taskDurationDisplayFlag;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    void zh_restoreSettings();
    void zh_saveSettings() const;
    void zh_pauseButtonControl(bool paused, bool enabled = true);

};
//===================================================
#endif // ZTRAININGWIDGET_H
