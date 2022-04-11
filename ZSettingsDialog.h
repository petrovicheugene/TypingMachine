//===================================================
#ifndef ZSETTINGSDIALOG_H
#define ZSETTINGSDIALOG_H
//===================================================
#include <QDialog>
#include "ZAppSettings.h"
//===================================================
class ZColorButton;

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

signals:



private:

    // VARS
    ZColorButton* zv_completeColorButton;
    ZColorButton* zv_currentColorButton;
    ZColorButton* zv_incompleteColorButton;
    ZColorButton* zv_wrongColorButton;

    // show wrong button radiobuttons
    QRadioButton* zv_dontShow;
    QRadioButton* zv_showWhilePressed;
    QRadioButton* zv_showForTime;
    QSpinBox* zv_showDurationSpinBox;

    QPushButton* zv_okButton;
    QPushButton* zv_cancelButton;

    ZAppSettings zv_appSettings;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

    void zh_restoreSettings();
    void zh_saveSettings() const;
    void zh_applySettingsValues();

};
//===================================================
#endif // ZSETTINGSDIALOG_H
