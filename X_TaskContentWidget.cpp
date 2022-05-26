//===================================================
#include "X_TaskContentWidget.h"
#include "X_ClickableLabel.h"
#include "X_Task.h"

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QPlainTextEdit>
#include <QSettings>
#include <QVBoxLayout>
//===================================================
//===================================================
X_TaskContentWidget::X_TaskContentWidget(QWidget *parent)
    : QWidget{parent}
{
    xh_createComponents();
    xh_createConnections();

    xh_setFontPointSize(xv_fontSizeSlider->value());
    xh_restoreSettings();
}
//===================================================
X_TaskContentWidget::~X_TaskContentWidget()
{
    xh_saveSettings();
}
//===================================================
void X_TaskContentWidget::xh_restoreSettings()
{
    QSettings settings;
    settings.beginGroup("TaskContentWidget");
    QVariant vData = settings.value("FontSize");
    if(vData.isValid() && vData.canConvert<int>())
    {
        xv_fontSizeSlider->setValue(vData.toInt());
    }
    settings.endGroup();
}
//===================================================
void X_TaskContentWidget::xh_saveSettings() const
{
    QSettings settings;
    settings.beginGroup("TaskContentWidget");
    settings.setValue("FontSize", QVariant(xv_fontSizeSlider->value()));
    settings.endGroup();
}
//===================================================
void X_TaskContentWidget::xh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // WIdget layout
    QHBoxLayout* widgetLayout = new QHBoxLayout;
    mainLayout->addLayout(widgetLayout);

    // Task Edit layout
    QVBoxLayout* taskMainLayout = new QVBoxLayout;
    widgetLayout->addLayout(taskMainLayout, 999999);

    QHBoxLayout* labelLayout = new QHBoxLayout;
    taskMainLayout->addLayout(labelLayout);

    xv_taskNameLabel = new QLabel;
    labelLayout->addWidget(xv_taskNameLabel, 999999);

    xv_taskTextEdit = new QPlainTextEdit;
    taskMainLayout->addWidget(xv_taskTextEdit);

    QHBoxLayout* taskBasementLayout = new QHBoxLayout;
    taskBasementLayout->addStretch(999999);
    taskMainLayout->addLayout(taskBasementLayout);

    xv_minusLabel = new X_ClickableLabel(this);
    xv_minusLabel->setText("-");
    xv_plusLabel = new X_ClickableLabel(this);
    xv_plusLabel->setText("+");

    taskBasementLayout->addWidget(xv_minusLabel);
    xv_fontSizeSlider = new QSlider(Qt::Horizontal);
    xv_fontSizeSlider->setRange(8, 96);
    xv_fontSizeSlider->setToolTip(tr("Font size"));
    taskBasementLayout->addWidget(xv_fontSizeSlider);
    taskBasementLayout->addWidget(xv_plusLabel);

    // task Settings layout
    QVBoxLayout* taskSettingsLayout = new QVBoxLayout;
    widgetLayout->addLayout(taskSettingsLayout);

    taskSettingsLayout->addWidget(xh_createTaskSettingsWidget());

    QHBoxLayout* taskSettingsBasementLayout = new QHBoxLayout;
    taskSettingsBasementLayout->addStretch(999999);
    taskSettingsLayout->addLayout(taskSettingsBasementLayout);

    xv_runTaskButton = new QPushButton;
    xv_runTaskButton->setIcon(QIcon(":/images/start-8.png"));
    xv_runTaskButton->setToolTip(tr("Run task"));
    taskSettingsBasementLayout->addWidget(xv_runTaskButton);
}
//===================================================
QWidget* X_TaskContentWidget::xh_createTaskSettingsWidget()
{
    QWidget* w = new QGroupBox(tr("Task settings"));

    QFormLayout* layout = new QFormLayout;
    w->setLayout(layout);

    xv_splitByComboBox = new QComboBox;
    foreach(auto key, splitByStringMap.keys())
    {
        xv_splitByComboBox->insertItem(xv_splitByComboBox->count(),
                                          splitByStringMap.value(key), key);
    }

    layout->addRow(tr("Split by:"), xv_splitByComboBox);

    xv_outputOrderComboBox = new QComboBox;
    foreach(auto key, outputOrderStringMap.keys())
    {
        xv_outputOrderComboBox->insertItem(xv_outputOrderComboBox->count(),
                                           outputOrderStringMap.value(key), key);
    }
    layout->addRow(tr("Output order:"), xv_outputOrderComboBox);

    xv_lineEndKeyComboBox = new QComboBox;
    foreach(auto key, lineEndKeyStringMap.keys())
    {
        xv_lineEndKeyComboBox->insertItem(xv_lineEndKeyComboBox->count(),
                                          lineEndKeyStringMap.value(key), key);
    }
    layout->addRow(tr("Next line by:"), xv_lineEndKeyComboBox);

    xv_repeatTaskCheckBox = new QCheckBox;
    layout->addRow(tr("Repeat task:"), xv_repeatTaskCheckBox);

    return w;
}
//===================================================
void X_TaskContentWidget::xh_createConnections()
{
    connect(xv_fontSizeSlider, &QSlider::valueChanged,
            this, &X_TaskContentWidget::xh_setFontPointSize);
    connect(xv_runTaskButton, &QPushButton::clicked,
            this, &X_TaskContentWidget::xg_requestTrainingStart);

    connect(xv_minusLabel, &X_ClickableLabel::clicked,
            this, &X_TaskContentWidget::xh_changeFontSizeSliderValue);
    connect(xv_plusLabel, &X_ClickableLabel::clicked,
            this, &X_TaskContentWidget::xh_changeFontSizeSliderValue);

}
//===================================================
void X_TaskContentWidget::xp_applySettings(QMap<int, QVariant> settingsMap)
{
    if(settingsMap.contains(SN_FONT_SIZE))
    {
        xv_fontSizeSlider->setValue(settingsMap.value(SN_FONT_SIZE).toInt());
    }
}
//===================================================
QMap<int, QVariant> X_TaskContentWidget::xp_settings() const
{
    QMap<int, QVariant> settingsMap;
    settingsMap.insert(SN_FONT_SIZE, xv_fontSizeSlider->value());
    return settingsMap;
}
//===================================================
void X_TaskContentWidget::xp_setTaskModel(QAbstractItemModel* model)
{
    xv_mapper = new QDataWidgetMapper(this);
    xv_mapper->setModel(model);
    xv_mapper->addMapping(xv_taskNameLabel, 1, "text");
    xv_mapper->addMapping(xv_taskTextEdit, 2);
    xv_mapper->addMapping(xv_splitByComboBox, 3);
    xv_mapper->addMapping(xv_outputOrderComboBox, 4);
    xv_mapper->addMapping(xv_lineEndKeyComboBox, 5);
    xv_mapper->addMapping(xv_repeatTaskCheckBox, 6);

    xv_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    connect(this, &X_TaskContentWidget::xg_currentIndexChanged,
            xv_mapper, &QDataWidgetMapper::setCurrentIndex);

}
//===================================================
void X_TaskContentWidget::xh_setFontPointSize(int val)
{
    QFont font = xv_taskTextEdit->font();
    font.setPointSize(val);
    xv_taskTextEdit->setFont(font);
}
//===================================================
void X_TaskContentWidget::xh_changeFontSizeSliderValue()
{
    int delta = qApp->keyboardModifiers() & Qt::ControlModifier ?
                xv_fontSizeSlider->singleStep() : xv_fontSizeSlider->pageStep();

    if(sender() == xv_plusLabel)
    {
        xv_fontSizeSlider->setValue(xv_fontSizeSlider->value() + delta);
    }
    else if(sender() == xv_minusLabel)
    {
        xv_fontSizeSlider->setValue(xv_fontSizeSlider->value() - delta);
    }
}
//===================================================



