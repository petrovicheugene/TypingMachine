//===================================================
#include "X_SettingsDialog.h"
#include "X_ColorButton.h"

#include <QApplication>
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
X_SettingsDialog::X_SettingsDialog(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle(tr("Settings"));
    xh_createComponents();
    xh_createConnections();

    xh_restoreSettings();
}
//===================================================
X_SettingsDialog::~X_SettingsDialog()
{
    xh_saveSettings();
}
//===================================================
void X_SettingsDialog::xh_createComponents()
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

    xv_completeColorButton = new X_ColorButton(this);
    trainingWidgetGridLayout->addWidget(xv_completeColorButton, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    QLabel* label = new QLabel(tr("Complete text color"));
    trainingWidgetGridLayout->addWidget(label, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);

    xv_incompleteColorButton = new X_ColorButton(this);
    trainingWidgetGridLayout->addWidget(xv_incompleteColorButton, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Incomplete text color"));
    trainingWidgetGridLayout->addWidget(label, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    xv_currentColorButton = new X_ColorButton(this);
    trainingWidgetGridLayout->addWidget(xv_currentColorButton, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Current symbol color"));
    trainingWidgetGridLayout->addWidget(label, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

    xv_wrongColorButton = new X_ColorButton(this);
    trainingWidgetGridLayout->addWidget(xv_wrongColorButton, 3, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Wrong symbol color"));
    trainingWidgetGridLayout->addWidget(label, 3, 1, Qt::AlignLeft | Qt::AlignVCenter);

    xv_underlinedCheckBox = new QCheckBox;
    trainingWidgetGridLayout->addWidget(xv_underlinedCheckBox, 4, 0, Qt::AlignLeft | Qt::AlignVCenter);
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


    xv_dontDisplay = new QRadioButton(tr("Don't display"));
    wrongSymbolGridLayout->addWidget(xv_dontDisplay, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    xv_displayWhilePressed  = new QRadioButton(tr("Display while pressed"));
    wrongSymbolGridLayout->addWidget(xv_displayWhilePressed, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    xv_displayForTime  = new QRadioButton(tr("Display for"));
    wrongSymbolGridLayout->addWidget(xv_displayForTime, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);

    xv_wrongSymbolDisplayDurationSpinBox = new QSpinBox;
    xv_wrongSymbolDisplayDurationSpinBox->setRange(0, 3000);
    wrongSymbolGridLayout->addWidget(xv_wrongSymbolDisplayDurationSpinBox, 2, 1, Qt::AlignRight | Qt::AlignVCenter);
    label = new QLabel(tr("ms."));
    wrongSymbolGridLayout->addWidget(label, 2, 2, Qt::AlignLeft | Qt::AlignVCenter);

    xv_radioButtonGroup = new QButtonGroup;
    xv_radioButtonGroup->addButton(xv_dontDisplay, int(X_TrainingManager::WSSM_DONT_DISPLAY));
    xv_radioButtonGroup->addButton(xv_displayWhilePressed, int(X_TrainingManager::WSSM_WHILE_PRESSED));
    xv_radioButtonGroup->addButton(xv_displayForTime, int(X_TrainingManager::WSSM_FOR_TIME));

    // INFO
    QGroupBox* infoGroupBox = new QGroupBox(tr("Info messages"));
    mainLayout->addWidget(infoGroupBox);

    stretchLayout = new QHBoxLayout;
    infoGroupBox->setLayout(stretchLayout);

    QGridLayout* infoGridLayout = new QGridLayout;
    stretchLayout->addLayout(infoGridLayout);
    stretchLayout->addStretch(999999);

    xv_infoColorButton = new X_ColorButton(this);
    infoGridLayout->addWidget(xv_infoColorButton, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Info text color"));
    infoGridLayout->addWidget(label, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);

    xv_infoFontSizeComboBox = new QComboBox(this);
    xv_infoFontSizeComboBox->addItems(xh_sizesStringList());
    infoGridLayout->addWidget(xv_infoFontSizeComboBox, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Info text font size"));
    infoGridLayout->addWidget(label, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    xv_taskDurationDisplayCheckBox = new QCheckBox;
    infoGridLayout->addWidget(xv_taskDurationDisplayCheckBox, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);
    label = new QLabel(tr("Display task duration"));
    infoGridLayout->addWidget(label, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // basement
    mainLayout->addStretch();

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);

    xv_closeButton = new QPushButton(tr("Close"));
    buttonBox->addButton(xv_closeButton, QDialogButtonBox::ActionRole);
}
//===================================================
QStringList X_SettingsDialog::xh_sizesStringList()
{
    return QStringList({"8","9","10","11","12","14","16","18","20","22",
                        "24","26","28","32","36","48","72"});
}
//===================================================
void X_SettingsDialog::xh_createConnections()
{
    connect(xv_closeButton, &QPushButton::clicked,
            this, &X_SettingsDialog::close);
}
//===================================================
void X_SettingsDialog::xp_setTrainingWidget(X_TrainingWidget* trainingWidget)
{
    connect(xv_completeColorButton, &X_ColorButton::xg_colorChanged,
            trainingWidget, &X_TrainingWidget::xp_setCompletedColor);
    connect(xv_incompleteColorButton, &X_ColorButton::xg_colorChanged,
            trainingWidget, &X_TrainingWidget::xp_setIncompletedColor);
    connect(xv_currentColorButton, &X_ColorButton::xg_colorChanged,
            trainingWidget, &X_TrainingWidget::xp_setCurrentSymbolColor);
    connect(xv_wrongColorButton, &X_ColorButton::xg_colorChanged,
            trainingWidget, &X_TrainingWidget::xp_setWrongSymbolColor);
    connect(xv_underlinedCheckBox, &QCheckBox::clicked,
            trainingWidget, &X_TrainingWidget::xp_setCurrentSymbolUnderlined);

    connect(xv_infoColorButton, &X_ColorButton::xg_colorChanged,
            trainingWidget, &X_TrainingWidget::xp_setInfoColor);
    connect(xv_taskDurationDisplayCheckBox, &QCheckBox::clicked,
            trainingWidget, &X_TrainingWidget::xp_setTaskDurationDisplayFlag);
    connect(xv_infoFontSizeComboBox, &QComboBox::currentTextChanged,
            trainingWidget, &X_TrainingWidget::xp_setInfoFontSizeString);

    xv_completeColorButton->xp_setColor(trainingWidget->xp_completedColor());
    xv_incompleteColorButton->xp_setColor(trainingWidget->xp_incompletedColor());
    xv_currentColorButton->xp_setColor(trainingWidget->xp_currentSymbolColor());
    xv_wrongColorButton->xp_setColor(trainingWidget->xp_wrongSymbolColor());
    xv_underlinedCheckBox->setChecked(trainingWidget->xp_isSymbolUnderlined());

    xv_infoColorButton->xp_setColor(trainingWidget->xp_infoColor());
    xv_taskDurationDisplayCheckBox->setChecked(trainingWidget->xp_isTaskDurationDisplayed());
    xv_infoFontSizeComboBox->setCurrentText(QString::number(trainingWidget->xp_infoFontSize()));
}
//===================================================
void X_SettingsDialog::xp_setTrainingManager(X_TrainingManager* trainingManager)
{
    connect(xv_wrongSymbolDisplayDurationSpinBox, &QSpinBox::valueChanged,
            trainingManager, &X_TrainingManager::xp_setWrongSymbolDisplayDuration);
    connect(xv_radioButtonGroup, &QButtonGroup::idClicked,
            this, &X_SettingsDialog::xh_onWrongSymbolDisplayModeChange);
    connect(this, &X_SettingsDialog::xg_wrongSymbolDisplayModeChanged,
            trainingManager, &X_TrainingManager::xp_setWrongSymbolDisplayMode);

    int buttonId = trainingManager->xp_wrongSymbolDisplayMode();
    xv_radioButtonGroup->button(buttonId)->setChecked(true);
    xv_wrongSymbolDisplayDurationSpinBox->setEnabled(buttonId == 2);

    xv_wrongSymbolDisplayDurationSpinBox->setValue(trainingManager->xp_wrongSymbolDisplayDuration());
}
//===================================================
void X_SettingsDialog::xh_restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("SettingsDialogGeometry").toByteArray());

    //QVariant vData = settings.value("Training");
}
//===================================================
void X_SettingsDialog::xh_saveSettings() const
{
    QSettings settings;
    settings.setValue("SettingsDialogGeometry", saveGeometry());
}
//===================================================
void X_SettingsDialog::xh_onWrongSymbolDisplayModeChange(int radioButtonIndex)
{
    xv_wrongSymbolDisplayDurationSpinBox->setEnabled(radioButtonIndex == 2);
    emit xg_wrongSymbolDisplayModeChanged(X_TrainingManager::WRONG_SYMBOL_DISPLAY_MODE(radioButtonIndex));
}
//===================================================
