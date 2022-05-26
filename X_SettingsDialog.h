//===================================================
#ifndef X_SETTINGSDIALOG_H
#define X_SETTINGSDIALOG_H
//===================================================
#include <QDialog>

#include "X_TrainingManager.h"
#include "X_TrainingWidget.h"
//===================================================
class X_ColorButton;

class QCheckBox;
class QComboBox;
class QButtonGroup;
class QPushButton;
class QRadioButton;
class QSpinBox;
//===================================================
class X_SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit X_SettingsDialog(QWidget *parent = nullptr);
    ~X_SettingsDialog();

    void xp_setTrainingWidget(X_TrainingWidget* trainingWidget);
    void xp_setTrainingManager(X_TrainingManager* trainingManager);


signals:

    void xg_wrongSymbolDisplayModeChanged( X_TrainingManager::WRONG_SYMBOL_DISPLAY_MODE);

private slots:

    void xh_onWrongSymbolDisplayModeChange(int radioButtonIndex);

private:

    // VARS
    X_ColorButton* xv_completeColorButton;
    X_ColorButton* xv_currentColorButton;
    X_ColorButton* xv_incompleteColorButton;
    X_ColorButton* xv_wrongColorButton;
    X_ColorButton* xv_infoColorButton;
    QComboBox* xv_infoFontSizeComboBox;

    QCheckBox* xv_underlinedCheckBox;
    QCheckBox* xv_taskDurationDisplayCheckBox;

    // display wrong button radiobuttons
    QButtonGroup* xv_radioButtonGroup;
    QRadioButton* xv_dontDisplay;
    QRadioButton* xv_displayWhilePressed;
    QRadioButton* xv_displayForTime;
    QSpinBox* xv_wrongSymbolDisplayDurationSpinBox;

    QPushButton* xv_closeButton;

    // ZAppSettings xv_appSettings;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();

    void xh_restoreSettings();
    void xh_saveSettings() const;
    //void xh_applySettingsValues(ZAppSettings appSettings);
    QStringList xh_sizesStringList();
};
//===================================================
#endif // X_SETTINGSDIALOG_H
