//===================================================
#include "ZTaskWidget.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QVBoxLayout>

#include "ZTrainingManager.h"
#include "ZTaskListWidget.h"
#include "ZTaskContentWidget.h"
//===================================================
ZTaskWidget::ZTaskWidget(QWidget *parent)
    : QWidget{parent}
{
    zh_createComponents();
    zh_createConnections();
    zh_restoreSettings();
}
//===================================================
ZTaskWidget::~ZTaskWidget()
{
    zh_saveSettings();

}
//===================================================
void ZTaskWidget::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);


    zv_splitter = new QSplitter(Qt::Horizontal);

    mainLayout->addWidget(zv_splitter);

    zv_taskListWidget = new ZTaskListWidget;
    zv_splitter->addWidget(zv_taskListWidget);

    zv_taskContentWidget = new ZTaskContentWidget;
    zv_splitter->addWidget(zv_taskContentWidget);

}
//===================================================
void ZTaskWidget::zh_createConnections()
{
    connect(zv_taskListWidget, &ZTaskListWidget::zg_requestNewTaskCreation,
            this, &ZTaskWidget::zg_requestNewTaskCreation);
    connect(zv_taskListWidget, &ZTaskListWidget::zg_requestTasksRemoving,
            this, &ZTaskWidget::zg_requestTasksRemoving);

    connect(zv_taskListWidget, &ZTaskListWidget::zg_currentTaskChanged,
            zv_taskContentWidget, &ZTaskContentWidget::zg_currentIndexChanged);
    connect(zv_taskContentWidget, &ZTaskContentWidget::zg_requestTrainingStart,
            this, &ZTaskWidget::zh_initTaskRun);

}
//===================================================
void ZTaskWidget::zh_saveSettings()
{
    QSettings settings;
    settings.setValue("TaskWidgetSplitter", zv_splitter->saveState());

}
//===================================================
void ZTaskWidget::zh_restoreSettings()
{
    QSettings settings;
    zv_splitter->restoreState(settings.value("TaskWidgetSplitter").toByteArray());
}
//===================================================
void ZTaskWidget::zp_setTaskModel(QAbstractItemModel* model)
{
    zv_taskListWidget->zp_setTaskModel(model);
    zv_taskContentWidget->zp_setTaskModel(model);
}
//===================================================
void ZTaskWidget::zh_initTaskRun()
{
    int taskRow =  zv_taskListWidget->zp_currentTaskRow();
    emit zg_requestTaskRun(taskRow);
}
//===================================================





