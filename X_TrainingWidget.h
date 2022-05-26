//===================================================
#ifndef X_TRAININGWIDGET_H
#define X_TRAININGWIDGET_H

#include "X_TrainingManager.h"

#include <QWidget>
#include <QColor>
//===================================================
class QLabel;
class QPushButton;
class QSlider;

class X_ClickableLabel;
//===================================================
class X_TrainingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit X_TrainingWidget(QWidget *parent = nullptr);
    ~X_TrainingWidget();

    void xp_connectToTrainingManager(X_TrainingManager* manager);

    QColor xp_completedColor() const;
    QColor xp_currentSymbolColor() const;
    QColor xp_wrongSymbolColor() const;
    QColor xp_incompletedColor() const;

    bool xp_isSymbolUnderlined() const;

    QColor xp_infoColor() const;
    bool xp_isTaskDurationDisplayed() const;
    int xp_infoFontSize() const;

public slots:

    void xp_updateLine();
    void xp_updateDuration(int duration);

    void xp_setFontSize(int size);

    void xp_setCompletedColor(QColor color);
    void xp_setCurrentSymbolColor(QColor color);
    void xp_setWrongSymbolColor(QColor color);
    void xp_setIncompletedColor(QColor color);
    void xp_setCurrentSymbolUnderlined(bool underlined);

    void xp_setInfoColor(QColor color);
    void xp_setTaskDurationDisplayFlag(bool displayFlag);
    void xp_setInfoFontSize(int size);
    void xp_setInfoFontSizeString(QString size);

    void xp_onTaskStateChange(X_TrainingManager::TASK_STATE previous,
                                               X_TrainingManager::TASK_STATE current);

signals:

    void xg_requestTaskFinish();
    void xg_requestTaskRestart();
    void xg_requestTaskPauseToggle(bool paused);

private slots:

    void xh_setFontSize(int size);
    void xh_changeFontSizeSliderValue();
    void xp_onTaskPauseToggle(bool checked);

private:

    // VARS
    X_TrainingManager* xv_trainingManager;
    QLabel* xv_lineLabel;
    QLabel* xv_taskDurationLabel;

    X_ClickableLabel* xv_minusLabel;
    X_ClickableLabel* xv_plusLabel;

    QSlider* xv_fontSizeSlider;
    QPushButton* xv_restartButton;
    QPushButton* xv_pauseButton;
    QPushButton* xv_finishButton;

    int xv_fontSize;
    QColor xv_completedColor;
    QColor xv_currentSymbolColor;
    QColor xv_wrongSymbolColor;
    QColor xv_incompletedColor;
    bool xv_symbolUnderlinedFlag;

    QColor xv_infoColor;
    bool xv_taskDurationDisplayFlag;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();
    void xh_restoreSettings();
    void xh_saveSettings() const;
    void xh_pauseButtonControl(bool paused, bool enabled = true);

};
//===================================================
#endif // X_TRAININGWIDGET_H
