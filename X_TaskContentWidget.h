//===================================================
#ifndef X_TASKCONTENTWIDGET_H
#define X_TASKCONTENTWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QCheckBox;
class QComboBox;
class QDataWidgetMapper;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QSplitter;
class QPlainTextEdit;

class X_ClickableLabel;
class X_TrainingManager;
//===================================================
//===================================================
class X_TaskContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit X_TaskContentWidget(QWidget *parent = nullptr);
    ~X_TaskContentWidget();

    void xp_setTaskModel(QAbstractItemModel* model);
    void xp_applySettings(QMap<int, QVariant> settingsMap);
    QMap<int, QVariant> xp_settings() const;

signals:

    void xg_currentIndexChanged(int index);
    void xg_requestTrainingStart();

private slots:

    void xh_setFontPointSize(int val);
    void xh_changeFontSizeSliderValue();

private:

    enum SETTING_NAMES {SN_FONT_SIZE=0};

    // VARS
    QDataWidgetMapper* xv_mapper;

    QLabel* xv_taskNameLabel;
    QPlainTextEdit* xv_taskTextEdit;

    X_ClickableLabel* xv_minusLabel;
    X_ClickableLabel* xv_plusLabel;
    QSlider* xv_fontSizeSlider;

    QComboBox* xv_splitByComboBox;
    QComboBox* xv_outputOrderComboBox;
    QComboBox* xv_lineEndKeyComboBox;
    QCheckBox* xv_repeatTaskCheckBox;

    QPushButton* xv_runTaskButton;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();
    void xh_restoreSettings();
    void xh_saveSettings() const;


    QWidget* xh_createTaskSettingsWidget();

};
//===================================================
#endif // X_TASKCONTENTWIDGET_H
