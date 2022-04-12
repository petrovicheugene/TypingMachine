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
// typedef  QMap<int, QVariant> SettingsMap;
//===================================================
class ZTrainingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTrainingWidget(QWidget *parent = nullptr);
    ~ZTrainingWidget();

    void zp_connectToTrainingManager(ZTrainingManager* manager);
    // void zp_applySettings(const QMap<int, QVariant> &settings);
    // QMap<int, QVariant> zp_settings() const;

    QColor zp_completedColor() const;
    QColor zp_currentSymbolColor() const;
    QColor zp_wrongSymbolColor() const;
    QColor zp_incompletedColor() const;
    bool zp_isSymbolUnderlined() const;

public slots:

    void zp_update();
    void zp_setFontSize(int size);

    void zp_setCompletedColor(QColor color);
    void zp_setCurrentSymbolColor(QColor color);
    void zp_setWrongSymbolColor(QColor color);
    void zp_setIncompletedColor(QColor color);
    void zp_setCurrentSymbolUnderlined(bool underlined);

signals:

    void zg_requestTaskFinish();
    void zg_requestTaskRestart();

private slots:

    void zh_setFontSize(int size);
    void zh_changeFontSizeSliderValue();

private:

    // VARS
    ZTrainingManager* zv_trainingManager;
    QLabel* zv_lineLabel;

    ZClickableLabel* zv_minusLabel;
    ZClickableLabel* zv_plusLabel;

    QSlider* zv_fontSizeSlider;
    QPushButton* zv_restartBtn;
    QPushButton* zv_finishBtn;

    int zv_fontSize;
    QColor zv_completedColor;
    QColor zv_currentSymbolColor;
    QColor zv_wrongSymbolColor;
    QColor zv_incompletedColor;
    bool zv_symbolUnderlinedFlag;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    void zh_restoreSettings();
    void zh_saveSettings() const;


};
//===================================================
#endif // ZTRAININGWIDGET_H
