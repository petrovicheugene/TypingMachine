//===================================================
#ifndef ZSETTINGSDIALOG_H
#define ZSETTINGSDIALOG_H
//===================================================
#include <QDialog>

#include "ZTrainingManager.h"
#include "ZTrainingWidget.h"
// #include "ZAppSettings.h"
//===================================================
class ZColorButton;

class QCheckBox;
class QButtonGroup;
class QPushButton;
class QRadioButton;
class QSpinBox;
//===================================================
class ZSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ZSettingsDialog(QWidget *parent = nullptr);
    ~ZSettingsDialog();

    void zp_setTrainingWidget(ZTrainingWidget* trainingWidget);
    void zp_setTrainingManager(ZTrainingManager* trainingManager);


signals:

    void zg_wrongSymbolShowModeChanged( ZTrainingManager::WRONG_SYMBOL_SHOW_MODE);

private slots:

    void zh_onWrongSymbolShowModeChange(int radioButtonIndex);

private:

    // VARS
    ZColorButton* zv_completeColorButton;
    ZColorButton* zv_currentColorButton;
    ZColorButton* zv_incompleteColorButton;
    ZColorButton* zv_wrongColorButton;
    QCheckBox* zv_underlinedCheckBox;

    // show wrong button radiobuttons
    QButtonGroup* zv_radioButtonGroup;
    QRadioButton* zv_dontShow;
    QRadioButton* zv_showWhilePressed;
    QRadioButton* zv_showForTime;
    QSpinBox* zv_showDurationSpinBox;

    QPushButton* zv_closeButton;

    // ZAppSettings zv_appSettings;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

    void zh_restoreSettings();
    void zh_saveSettings() const;
    //void zh_applySettingsValues(ZAppSettings appSettings);

};
//===================================================
#endif // ZSETTINGSDIALOG_H