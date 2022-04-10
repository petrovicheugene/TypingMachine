//===================================================
#ifndef ZTASKCONTENTWIDGET_H
#define ZTASKCONTENTWIDGET_H
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

class ZTrainingManager;
//===================================================
typedef  QMap<int, QVariant> SettingsMap;
//===================================================
class ZTaskContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTaskContentWidget(QWidget *parent = nullptr);
    ~ZTaskContentWidget();

    void zp_setTaskModel(QAbstractItemModel* model);
    void zp_applySettings(QMap<int, QVariant> settingsMap);
    QMap<int, QVariant> zp_settings() const;

signals:

    void zg_currentIndexChanged(int index);
    void zg_requestTrainingStart();

private slots:

    void zh_setFontPointSize(int val);

private:

    enum SETTING_NAMES {SN_FONT_SIZE=0};

    // VARS
    QDataWidgetMapper* zv_mapper;

    QLabel* zv_taskNameLabel;
    QPlainTextEdit* zv_taskTextEdit;
    QSlider* zv_fontSizeSlider;

    QComboBox* zv_outputLineComboBox;
    QComboBox* zv_outputOrderComboBox;
    QComboBox* zv_lineEndKeyComboBox;
    QCheckBox* zv_repeatTaskCheckBox;

    QPushButton* zv_runTaskButton;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    void zh_restoreSettings();
    void zh_saveSettings() const;


    QWidget* zh_createTaskSettingsWidget();

};
//===================================================
#endif // ZTASKCONTENTWIDGET_H
