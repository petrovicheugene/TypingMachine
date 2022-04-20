//===================================================
#include "ZSettingsDialog.h"
#include "ZColorButton.h"

#include <QComboBox>
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

    QGroupBox* colorGroupBox = new QGroupBox(tr("Text"));
    mainLayout->addWidget(colorGroupBox);

    QHBoxLayout* stretchLayout = new QHBoxLayout;
    colorGroupBox->setLayout(stretchLayout);

    QGridLayout* trainingWidgetGridLayout = new QGridLayout;
    stretchLayout->addLayout(trainingWidgetGridLayout);
    stretchLayout->addStretch(999999);

    zv_completeColorButton = new ZColorButton(this);
    trainingWidgetGridLayout->addWidget(zv_completeColorButton, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    QLabel* label = new QLabel(tr("Complete text color"));
    trainingWidgetGridLayout->addWidget(label, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_incompleteColorButton = new ZColorButton(this);
    trainingWidgetGridLayout->addWidget(zv_incompleteColorButton, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Incomplete text color"));
    trainingWidgetGridLayout->addWidget(label, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_currentColorButton = new ZColorButton(this);
    trainingWidgetGridLayout->addWidget(zv_currentColorButton, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Current symbol color"));
    trainingWidgetGridLayout->addWidget(label, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_wrongColorButton = new ZColorButton(this);
    trainingWidgetGridLayout->addWidget(zv_wrongColorButton, 3, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Wrong symbol color"));
    trainingWidgetGridLayout->addWidget(label, 3, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_underlinedCheckBox = new QCheckBox;
    trainingWidgetGridLayout->addWidget(zv_underlinedCheckBox, 4, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Underline current symbol"));
    trainingWidgetGridLayout->addWidget(label, 4, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // Display wrong symbol
    QGroupBox* wrongSymbolGroupBox = new QGroupBox(tr("Wrong symbol"));
    mainLayout->addWidget(wrongSymbolGroupBox);

    stretchLayout = new QHBoxLayout;
    wrongSymbolGroupBox->setLayout(stretchLayout);

    QGridLayout* wrongSymbolGridLayout = new QGridLayout;
    stretchLayout->addLayout(wrongSymbolGridLayout);
    stretchLayout->addStretch(999999);


    zv_dontDisplay = new QRadioButton(tr("Don't display"));
    wrongSymbolGridLayout->addWidget(zv_dontDisplay, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    zv_displayWhilePressed  = new QRadioButton(tr("Display while pressed"));
    wrongSymbolGridLayout->addWidget(zv_displayWhilePressed, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    zv_displayForTime  = new QRadioButton(tr("Display for"));
    wrongSymbolGridLayout->addWidget(zv_displayForTime, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);

    zv_wrongSymbolDisplayDurationSpinBox = new QSpinBox;
    zv_wrongSymbolDisplayDurationSpinBox->setRange(0, 3000);
    wrongSymbolGridLayout->addWidget(zv_wrongSymbolDisplayDurationSpinBox, 2, 1, Qt::AlignRight | Qt::AlignVCenter);
    label = new QLabel(tr("ms."));
    wrongSymbolGridLayout->addWidget(label, 2, 2, Qt::AlignLeft | Qt::AlignVCenter);

    zv_radioButtonGroup = new QButtonGroup;
    zv_radioButtonGroup->addButton(zv_dontDisplay, int(ZTrainingManager::WSSM_DONT_DISPLAY));
    zv_radioButtonGroup->addButton(zv_displayWhilePressed, int(ZTrainingManager::WSSM_WHILE_PRESSED));
    zv_radioButtonGroup->addButton(zv_displayForTime, int(ZTrainingManager::WSSM_FOR_TIME));

    // INFO
    QGroupBox* infoGroupBox = new QGroupBox(tr("Info messages"));
    mainLayout->addWidget(infoGroupBox);

    stretchLayout = new QHBoxLayout;
    infoGroupBox->setLayout(stretchLayout);

    QGridLayout* infoGridLayout = new QGridLayout;
    stretchLayout->addLayout(infoGridLayout);
    stretchLayout->addStretch(999999);

    zv_infoColorButton = new ZColorButton(this);
    infoGridLayout->addWidget(zv_infoColorButton, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Info text color"));
    infoGridLayout->addWidget(label, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_infoFontSizeComboBox = new QComboBox(this);
    zv_infoFontSizeComboBox->addItems(zh_sizesStringList());
    infoGridLayout->addWidget(zv_infoFontSizeComboBox, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Info text font size"));
    infoGridLayout->addWidget(label, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    zv_taskDurationDisplayCheckBox = new QCheckBox;
    infoGridLayout->addWidget(zv_taskDurationDisplayCheckBox, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Display task duration"));
    infoGridLayout->addWidget(label, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // basement
    mainLayout->addStretch();

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);

    zv_closeButton = new QPushButton(tr("Close"));
    buttonBox->addButton(zv_closeButton, QDialogButtonBox::ActionRole);
}
//===================================================
QStringList ZSettingsDialog::zh_sizesStringList()
{
    return QStringList({"8","9","10","11","12","14","16","18","20","22",
                        "24","26","28","32","36","48","72"});
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

    connect(zv_infoColorButton, &ZColorButton::zg_colorChanged,
            trainingWidget, &ZTrainingWidget::zp_setInfoColor);
    connect(zv_taskDurationDisplayCheckBox, &QCheckBox::clicked,
            trainingWidget, &ZTrainingWidget::zp_setTaskDurationDisplayFlag);
    connect(zv_infoFontSizeComboBox, &QComboBox::currentTextChanged,
            trainingWidget, &ZTrainingWidget::zp_setInfoFontSizeString);


    zv_completeColorButton->zp_setColor(trainingWidget->zp_completedColor());
    zv_incompleteColorButton->zp_setColor(trainingWidget->zp_incompletedColor());
    zv_currentColorButton->zp_setColor(trainingWidget->zp_currentSymbolColor());
    zv_wrongColorButton->zp_setColor(trainingWidget->zp_wrongSymbolColor());
    zv_underlinedCheckBox->setChecked(trainingWidget->zp_isSymbolUnderlined());

    zv_infoColorButton->zp_setColor(trainingWidget->zp_infoColor());
    zv_taskDurationDisplayCheckBox->setChecked(trainingWidget->zp_isTaskDurationDisplayed());
    zv_infoFontSizeComboBox->setCurrentText(QString::number(trainingWidget->zp_infoFontSize()));
}
//===================================================
void ZSettingsDialog::zp_setTrainingManager(ZTrainingManager* trainingManager)
{
    connect(zv_wrongSymbolDisplayDurationSpinBox, &QSpinBox::valueChanged,
            trainingManager, &ZTrainingManager::zp_setWrongSymbolDisplayDuration);
    connect(zv_radioButtonGroup, &QButtonGroup::idClicked,
            this, &ZSettingsDialog::zh_onWrongSymbolDisplayModeChange);
    connect(this, &ZSettingsDialog::zg_wrongSymbolDisplayModeChanged,
            trainingManager, &ZTrainingManager::zp_setWrongSymbolDisplayMode);

    int buttonId = trainingManager->zp_wrongSymbolDisplayMode();
    zv_radioButtonGroup->button(buttonId)->setChecked(true);
    zv_wrongSymbolDisplayDurationSpinBox->setEnabled(buttonId == 2);

    zv_wrongSymbolDisplayDurationSpinBox->setValue(trainingManager->zp_wrongSymbolDisplayDuration());
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
void ZSettingsDialog::zh_onWrongSymbolDisplayModeChange(int radioButtonIndex)
{
    zv_wrongSymbolDisplayDurationSpinBox->setEnabled(radioButtonIndex == 2);
    emit zg_wrongSymbolDisplayModeChanged(ZTrainingManager::WRONG_SYMBOL_DISPLAY_MODE(radioButtonIndex));
}
//===================================================
