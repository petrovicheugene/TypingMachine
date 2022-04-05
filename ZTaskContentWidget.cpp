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
#include <QVBoxLayout>
//===================================================

//===================================================

ZTaskContentWidget::ZTaskContentWidget(QWidget *parent)
    : QWidget{parent}
{
    zh_createComponents();
    zh_createConnections();
}
//===================================================
void ZTaskContentWidget::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

//    QHBoxLayout* labelLayout = new QHBoxLayout;
//    mainLayout->addLayout(labelLayout);

//    zv_taskNameLabel = new QLabel;
//    labelLayout->addWidget(zv_taskNameLabel, 999999);

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
    zv_fontSizeSlider->setRange(8, 72);
    zv_fontSizeSlider->setToolTip(tr("Font size"));
    taskBasementLayout->addWidget(zv_fontSizeSlider);
    taskBasementLayout->addWidget(new QLabel("+"));

    // task Settings layout
    QVBoxLayout* taskSettingsLayout = new QVBoxLayout;
    widgetLayout->addLayout(taskSettingsLayout);

//    labelLayout = new QHBoxLayout;
//    taskSettingsLayout->addLayout(labelLayout);

//    labelLayout->addWidget(new QLabel(tr("Task settings")), 999999);

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

//     zv_outputLineComboBox->insertItems(-1, QStringList({tr("Word"), tr("String")}));

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
void ZTaskContentWidget::zp_setContentManagment(ZTrainingManager* taskManager)
{

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

}
//===================================================
void ZTaskContentWidget::zh_setFontPointSize(int val)
{
    QFont font = zv_taskTextEdit->font();
    font.setPixelSize(val);
    zv_taskTextEdit->setFont(font);
}
//===================================================


