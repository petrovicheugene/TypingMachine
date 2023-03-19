//===================================================
#ifndef X_TRAININGWIDGET_H
#define X_TRAININGWIDGET_H

#include "X_TrainingManager.h"

#include <QWidget>
#include <QColor>
//===================================================
class QHBoxLayout;
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
    void xp_updateInfo(const QString& infoMsg);

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

    void xp_onTaskStatusChange(X_TrainingManager::TASK_STATUS previous,
                               X_TrainingManager::TASK_STATUS current);

signals:

    void xg_requestTaskFinish();
    void xg_requestTaskRestart();
    void xg_requestTaskPauseSwitch(bool paused);

private slots:

    void xh_setFontSize(int size);
    void xh_changeFontSizeSliderValue();
    void xp_onTaskPauseToggle(bool checked);

protected:

    bool eventFilter(QObject* object, QEvent* event) override;

private:

    // VARS
    X_TrainingManager* xv_trainingManager = nullptr;

    QLabel* xv_lineLabel  = nullptr;

    QLabel* xv_taskDurationLabel  = nullptr;
    QLabel* xv_infoMessageLabel  = nullptr;
    QWidget* xv_alignWidget = nullptr;

    X_ClickableLabel* xv_minusLabel  = nullptr;
    X_ClickableLabel* xv_plusLabel  = nullptr;

    QSlider* xv_fontSizeSlider = nullptr;
    QPushButton* xv_restartButton = nullptr;
    QPushButton* xv_startPauseButton = nullptr;
    QPushButton* xv_finishButton = nullptr;

    int xv_fontSize;
    QColor xv_completedColor;
    QColor xv_currentSymbolColor;
    QColor xv_wrongSymbolColor;
    QColor xv_incompletedColor;
    bool xv_symbolUnderlinedFlag;

    QColor xv_infoColor;
    // bool xv_taskDurationDisplayFlag;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();
    void xh_restoreSettings();
    void xh_saveSettings() const;
    void xh_startPauseButtonControl(bool paused, bool enabled = true);

};
//===================================================
#endif // X_TRAININGWIDGET_H
