//===================================================
#ifndef ZTRAININGWIDGET_H
#define ZTRAININGWIDGET_H

#include <QWidget>
#include <QColor>
//===================================================
class QLabel;
class QPushButton;
class QSlider;

class ZTrainingManager;
//===================================================
typedef  QMap<int, QVariant> SettingsMap;
//===================================================
class ZTrainingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTrainingWidget(QWidget *parent = nullptr);
    ~ZTrainingWidget();

    void zp_connectToTrainingManager(ZTrainingManager* manager);
    void zp_applySettings(QMap<int, QVariant> settings);
    QMap<int, QVariant> zp_settings() const;

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

private slots:

    void zh_setFontSize(int size);

private:

    enum SETTING_NAMES {SN_FONT_SIZE=0,
                       SN_COMPLETED_COLOR=1,
                       SN_CURRENT_COLOR=2,
                       SN_INCOMPLETED_COLOR=3,
                       SN_WRONG_COLOR=4};

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
    void zh_restoreSettings();
    void zh_saveSettings() const;


};
//===================================================
#endif // ZTRAININGWIDGET_H
