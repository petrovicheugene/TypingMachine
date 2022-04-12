//===================================================
#include "ZSettingsDialog.h"
#include "ZColorButton.h"


#include <QCheckBox>
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
    setWindowTitle(tr("Settings"));
    zh_createComponents();
    zh_createConnections();

    zh_restoreSettings();
}
//===================================================
ZSettingsDialog::~ZSettingsDialog()
{
    zh_saveSettings();
}
//===================================================
void ZSettingsDialog::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QGroupBox* colorGroupBox = new QGroupBox(tr("Color"));
    mainLayout->addWidget(colorGroupBox);

    QGridLayout* trainingWidgetGridLayout = new QGridLayout;
    colorGroupBox->setLayout(trainingWidgetGridLayout);

    zv_completeColorButton = new ZColorButton(this);
    QLabel* label = new QLabel(tr("Complete text"));
    trainingWidgetGridLayout->addWidget(label, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    trainingWidgetGridLayout->addWidget(zv_completeColorButton, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_incompleteColorButton = new ZColorButton(this);
    label = new QLabel(tr("Incomplete text"));
    trainingWidgetGridLayout->addWidget(label, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    trainingWidgetGridLayout->addWidget(zv_incompleteColorButton, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_currentColorButton = new ZColorButton(this);
    label = new QLabel(tr("Current symbol"));
    trainingWidgetGridLayout->addWidget(label, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);
    trainingWidgetGridLayout->addWidget(zv_currentColorButton, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_wrongColorButton = new ZColorButton(this);
    label = new QLabel(tr("Wrong symbol"));
    trainingWidgetGridLayout->addWidget(label, 3, 0, Qt::AlignLeft | Qt::AlignVCenter);
    trainingWidgetGridLayout->addWidget(zv_wrongColorButton, 3, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_underlinedCheckBox = new QCheckBox(tr("Underline current symbol"));
    trainingWidgetGridLayout->addWidget(zv_underlinedCheckBox, 4, 0, Qt::AlignLeft | Qt::AlignVCenter);

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
    zv_showDurationSpinBox->setRange(0, 3000);
    wrongSymbolGridLayout->addWidget(zv_showDurationSpinBox, 2, 1, Qt::AlignRight | Qt::AlignVCenter);
    label = new QLabel(tr("ms."));
    wrongSymbolGridLayout->addWidget(label, 2, 2, Qt::AlignLeft | Qt::AlignVCenter);

    zv_radioButtonGroup = new QButtonGroup;
    zv_radioButtonGroup->addButton(zv_dontShow, int(ZTrainingManager::WSSM_DONT_SHOW));
    zv_radioButtonGroup->addButton(zv_showWhilePressed, int(ZTrainingManager::WSSM_WHILE_PRESSED));
    zv_radioButtonGroup->addButton(zv_showForTime, int(ZTrainingManager::WSSM_FOR_TIME));

    mainLayout->addStretch();

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);

    zv_closeButton = new QPushButton(tr("Close"));
    buttonBox->addButton(zv_closeButton, QDialogButtonBox::ActionRole);
}
//===================================================
void ZSettingsDialog::zh_createConnections()
{
    connect(zv_closeButton, &QPushButton::clicked,
            this, &ZSettingsDialog::close);
}
//===================================================
void ZSettingsDialog::zp_setTrainingWidget(ZTrainingWidget* trainingWidget)
{
    connect(zv_completeColorButton, &ZColorButton::zg_colorChanged,
           trainingWidget, &ZTrainingWidget::zp_setCompletedColor);
    connect(zv_incompleteColorButton, &ZColorButton::zg_colorChanged,
           trainingWidget, &ZTrainingWidget::zp_setIncompletedColor);
    connect(zv_currentColorButton, &ZColorButton::zg_colorChanged,
           trainingWidget, &ZTrainingWidget::zp_setCurrentSymbolColor);
    connect(zv_wrongColorButton, &ZColorButton::zg_colorChanged,
           trainingWidget, &ZTrainingWidget::zp_setWrongSymbolColor);
    connect(zv_underlinedCheckBox, &QCheckBox::clicked,
           trainingWidget, &ZTrainingWidget::zp_setCurrentSymbolUnderlined);

    zv_completeColorButton->zp_setColor(trainingWidget->zp_completedColor());
    zv_incompleteColorButton->zp_setColor(trainingWidget->zp_incompletedColor());
    zv_currentColorButton->zp_setColor(trainingWidget->zp_currentSymbolColor());
    zv_wrongColorButton->zp_setColor(trainingWidget->zp_wrongSymbolColor());
    zv_underlinedCheckBox->setChecked(trainingWidget->zp_isSymbolUnderlined());
}
//===================================================
void ZSettingsDialog::zp_setTrainingManager(ZTrainingManager* trainingManager)
{
    connect(zv_showDurationSpinBox, &QSpinBox::valueChanged,
            trainingManager, &ZTrainingManager::zp_setWrongSymbolShowDuration);
    connect(zv_radioButtonGroup, &QButtonGroup::idClicked,
            this, &ZSettingsDialog::zh_onWrongSymbolShowModeChange);
    connect(this, &ZSettingsDialog::zg_wrongSymbolShowModeChanged,
            trainingManager, &ZTrainingManager::zp_setWrongSymbolShowMode);

    int buttonId = trainingManager->zp_wrongSymbolShowMode();
    zv_radioButtonGroup->button(buttonId)->setChecked(true);
    zv_showDurationSpinBox->setEnabled(buttonId == 2);

    zv_showDurationSpinBox->setValue(trainingManager->zp_wrongSymbolShowDuration());
}
//===================================================
void ZSettingsDialog::zh_restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("SettingsDialogGeometry").toByteArray());

    //QVariant vData = settings.value("Training");
}
//===================================================
void ZSettingsDialog::zh_saveSettings() const
{
    QSettings settings;
    settings.setValue("SettingsDialogGeometry", saveGeometry());
}
//===================================================
void ZSettingsDialog::zh_onWrongSymbolShowModeChange(int radioButtonIndex)
{
    zv_showDurationSpinBox->setEnabled(radioButtonIndex == 2);
    emit zg_wrongSymbolShowModeChanged(ZTrainingManager::WRONG_SYMBOL_SHOW_MODE(radioButtonIndex));
}
//===================================================
