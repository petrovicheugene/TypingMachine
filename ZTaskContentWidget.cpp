//===================================================
#include "ZTaskContentWidget.h"

#include <QDataWidgetMapper>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QPlainTextEdit>
#include <QVBoxLayout>
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

    QHBoxLayout* labelLayout = new QHBoxLayout;
    mainLayout->addLayout(labelLayout);

    zv_taskNameLabel = new QLabel;
    labelLayout->addWidget(zv_taskNameLabel, 999999);

    // WIdget layout
    QHBoxLayout* widgetLayout = new QHBoxLayout;
    mainLayout->addLayout(widgetLayout);

    // Task Edit layout
    QVBoxLayout* taskMainLayout = new QVBoxLayout;
    widgetLayout->addLayout(taskMainLayout);

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

    taskSettingsLayout->addWidget(new QWidget);

    QHBoxLayout* taskSettingsBasementLayout = new QHBoxLayout;
    taskSettingsBasementLayout->addStretch(999999);
    taskSettingsLayout->addLayout(taskSettingsBasementLayout);

    zv_runTaskButton = new QPushButton;
    zv_runTaskButton->setIcon(QIcon(":/images/run-256.png"));
    zv_runTaskButton->setToolTip(tr("Run task"));
    taskSettingsBasementLayout->addWidget(zv_runTaskButton);

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
    zv_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    zv_mapper->addMapping(zv_taskTextEdit, 2);
    zv_mapper->addMapping(zv_taskNameLabel, 1, "text");
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


