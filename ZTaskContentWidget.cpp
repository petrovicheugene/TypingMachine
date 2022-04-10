//===================================================
#include "ZTaskContentWidget.h"
#include "ZTask.h"

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
Q_DECLARE_METATYPE(SettingsMap);
//===================================================
ZTaskContentWidget::ZTaskContentWidget(QWidget *parent)
    : QWidget{parent}
{
    qRegisterMetaType<SettingsMap>();
    zh_createComponents();
    zh_createConnections();

    zh_setFontPointSize(zv_fontSizeSlider->value());
    zh_restoreSettings();
}
//===================================================
ZTaskContentWidget::~ZTaskContentWidget()
{
    zh_saveSettings();
}
//===================================================
void ZTaskContentWidget::zh_restoreSettings()
{
    QSettings settings;
    QVariant vData = settings.value("TaskContentWidget");
    if(vData.canConvert<SettingsMap>())
    {
        zp_applySettings(vData.value<SettingsMap>());
    }
}
//===================================================
void ZTaskContentWidget::zh_saveSettings() const
{
    QSettings settings;
    settings.setValue("TaskContentWidget", QVariant::fromValue(zp_settings()));
}
//===================================================
void ZTaskContentWidget::zh_createComponents()
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

    zv_taskNameLabel = new QLabel;
    labelLayout->addWidget(zv_taskNameLabel, 999999);

    zv_taskTextEdit = new QPlainTextEdit;
    taskMainLayout->addWidget(zv_taskTextEdit);

    QHBoxLayout* taskBasementLayout = new QHBoxLayout;
    taskBasementLayout->addStretch(999999);
    taskMainLayout->addLayout(taskBasementLayout);

    taskBasementLayout->addWidget(new QLabel("-"));
    zv_fontSizeSlider = new QSlider(Qt::Horizontal);
    zv_fontSizeSlider->setRange(8, 96);
    zv_fontSizeSlider->setToolTip(tr("Font size"));
    taskBasementLayout->addWidget(zv_fontSizeSlider);
    taskBasementLayout->addWidget(new QLabel("+"));

    // task Settings layout
    QVBoxLayout* taskSettingsLayout = new QVBoxLayout;
    widgetLayout->addLayout(taskSettingsLayout);

    taskSettingsLayout->addWidget(zh_createTaskSettingsWidget());

    QHBoxLayout* taskSettingsBasementLayout = new QHBoxLayout;
    taskSettingsBasementLayout->addStretch(999999);
    taskSettingsLayout->addLayout(taskSettingsBasementLayout);

    zv_runTaskButton = new QPushButton;
    zv_runTaskButton->setIcon(QIcon(":/images/run-256.png"));
    zv_runTaskButton->setToolTip(tr("Run task"));
    taskSettingsBasementLayout->addWidget(zv_runTaskButton);
}
//===================================================
QWidget* ZTaskContentWidget::zh_createTaskSettingsWidget()
{
    QWidget* w = new QGroupBox(tr("Task settings"));

    QFormLayout* layout = new QFormLayout;
    w->setLayout(layout);

    zv_outputLineComboBox = new QComboBox;
    foreach(auto key, outputLineStringMap.keys())
    {
        zv_outputLineComboBox->insertItem(zv_outputLineComboBox->count(),
                                          outputLineStringMap.value(key), key);
    }

    // zv_outputLineComboBox->insertItems(-1, QStringList({tr("Word"), tr("String")}));
    layout->addRow(tr("Output by:"), zv_outputLineComboBox);

    zv_outputOrderComboBox = new QComboBox;
    foreach(auto key, outputOrderStringMap.keys())
    {
        zv_outputOrderComboBox->insertItem(zv_outputOrderComboBox->count(),
                                           outputOrderStringMap.value(key), key);
    }
    layout->addRow(tr("Output order:"), zv_outputOrderComboBox);

    zv_lineEndKeyComboBox = new QComboBox;
    foreach(auto key, lineEndKeyStringMap.keys())
    {
        zv_lineEndKeyComboBox->insertItem(zv_lineEndKeyComboBox->count(),
                                          lineEndKeyStringMap.value(key), key);
    }
    layout->addRow(tr("Next line by:"), zv_lineEndKeyComboBox);

    zv_repeatTaskCheckBox = new QCheckBox;
    layout->addRow(tr("Repeat task:"), zv_repeatTaskCheckBox);

    return w;
}
//===================================================
void ZTaskContentWidget::zh_createConnections()
{
    connect(zv_fontSizeSlider, &QSlider::valueChanged,
            this, &ZTaskContentWidget::zh_setFontPointSize);
    connect(zv_runTaskButton, &QPushButton::clicked,
            this, &ZTaskContentWidget::zg_requestTrainingStart);
}
//===================================================
void ZTaskContentWidget::zp_applySettings(QMap<int, QVariant> settingsMap)
{
    if(settingsMap.contains(SN_FONT_SIZE))
    {
        zv_fontSizeSlider->setValue(settingsMap.value(SN_FONT_SIZE).toInt());
    }
}
//===================================================
QMap<int, QVariant> ZTaskContentWidget::zp_settings() const
{
    QMap<int, QVariant> settingsMap;
    settingsMap.insert(SN_FONT_SIZE, zv_fontSizeSlider->value());
    return settingsMap;
}
//===================================================
void ZTaskContentWidget::zp_setTaskModel(QAbstractItemModel* model)
{
    zv_mapper = new QDataWidgetMapper(this);
    zv_mapper->setModel(model);
    zv_mapper->addMapping(zv_taskNameLabel, 1, "text");
    zv_mapper->addMapping(zv_taskTextEdit, 2);
    zv_mapper->addMapping(zv_outputLineComboBox, 3);
    zv_mapper->addMapping(zv_outputOrderComboBox, 4);
    zv_mapper->addMapping(zv_lineEndKeyComboBox, 5);
    zv_mapper->addMapping(zv_repeatTaskCheckBox, 6);

    zv_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    connect(this, &ZTaskContentWidget::zg_currentIndexChanged,
            zv_mapper, &QDataWidgetMapper::setCurrentIndex);
    //    connect(zv_taskTextEdit->viewport(), &QWi,
    //            zv_mapper, &QDataWidgetMapper::submit);

}
//===================================================
void ZTaskContentWidget::zh_setFontPointSize(int val)
{
    QFont font = zv_taskTextEdit->font();
    font.setPointSize(val);
    zv_taskTextEdit->setFont(font);
}
//===================================================


