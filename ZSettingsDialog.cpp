//===================================================
#include "ZSettingsDialog.h"
#include "ZColorButton.h"

#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QSpinBox>
#include <QVBoxLayout>

//===================================================
ZSettingsDialog::ZSettingsDialog(QWidget *parent)
    : QDialog{parent}
{
    zh_createComponents();
    zh_createConnections();

    zh_restoreSettings();

}
//===================================================
ZSettingsDialog::~ZSettingsDialog()
{

}
//===================================================
void ZSettingsDialog::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QGroupBox* colorGroupBox = new QGroupBox(tr("Color"));
    mainLayout->addWidget(colorGroupBox);

    QGridLayout* colorGridLayout = new QGridLayout;
    colorGroupBox->setLayout(colorGridLayout);

    zv_completeColorButton = new ZColorButton(this);
    QLabel* label = new QLabel(tr("Complete text"));
    colorGridLayout->addWidget(label, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    colorGridLayout->addWidget(zv_completeColorButton, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_incompleteColorButton = new ZColorButton(this);
    label = new QLabel(tr("Incomplete text"));
    colorGridLayout->addWidget(label, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    colorGridLayout->addWidget(zv_incompleteColorButton, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_currentColorButton = new ZColorButton(this);
    label = new QLabel(tr("Current symbol"));
    colorGridLayout->addWidget(label, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);
    colorGridLayout->addWidget(zv_currentColorButton, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_wrongColorButton = new ZColorButton(this);
    label = new QLabel(tr("Wrong symbol"));
    colorGridLayout->addWidget(label, 3, 0, Qt::AlignLeft | Qt::AlignVCenter);
    colorGridLayout->addWidget(zv_wrongColorButton, 3, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // Show wrong symbol
    QGroupBox* wrongSymbolGroupBox = new QGroupBox(tr("Wrong symbol"));
    mainLayout->addWidget(wrongSymbolGroupBox);

    QGridLayout* wrongSymbolGridLayout = new QGridLayout;
    wrongSymbolGroupBox->setLayout(wrongSymbolGridLayout);

    zv_dontShow = new QRadioButton(tr("Don't show"));
    wrongSymbolGridLayout->addWidget(zv_dontShow, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    zv_showWhilePressed  = new QRadioButton(tr("Show while pressed"));
    wrongSymbolGridLayout->addWidget(zv_showWhilePressed, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    zv_showForTime  = new QRadioButton(tr("Show for"));
    wrongSymbolGridLayout->addWidget(zv_showForTime, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);

    zv_showDurationSpinBox = new QSpinBox;
    zv_showDurationSpinBox->setRange(100, 5000);
    wrongSymbolGridLayout->addWidget(zv_showDurationSpinBox, 2, 1, Qt::AlignRight | Qt::AlignVCenter);
    label = new QLabel(tr("ms."));
    wrongSymbolGridLayout->addWidget(label, 2, 2, Qt::AlignLeft | Qt::AlignVCenter);

    QButtonGroup* buttonGroup = new QButtonGroup;
    buttonGroup->addButton(zv_dontShow);
    buttonGroup->addButton(zv_showWhilePressed);
    buttonGroup->addButton(zv_showForTime);

    mainLayout->addStretch();

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);

    zv_okButton = new QPushButton(tr("Ok"));
    buttonBox->addButton(zv_okButton, QDialogButtonBox::ActionRole);

    zv_cancelButton = new QPushButton(tr("Cancel"));
    buttonBox->addButton(zv_cancelButton, QDialogButtonBox::ActionRole);

}
//===================================================
void ZSettingsDialog::zh_createConnections()
{

}
//===================================================
void ZSettingsDialog::zh_restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("SettingsDialogGeometry").toByteArray());

    QVariant vData = settings.value("Training");
//    if(vData.canConvert<SettingsMap>())
//    {
//        zv_settingsMap = (vData.value<SettingsMap>());
//    }

//    zh_applySettingsValues();

}
//===================================================
void ZSettingsDialog::zh_saveSettings() const
{
    QSettings settings;
    settings.setValue("SettingsDialogGeometry", saveGeometry());

    // settings.setValue("Training", QVariant::fromValue(zp_settings()));
}
//===================================================
//  zh_applySettingsValues()
//  {

//  }
//===================================================
