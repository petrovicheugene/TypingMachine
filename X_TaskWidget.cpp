//===================================================
#include "X_TaskWidget.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QVBoxLayout>

#include "X_TrainingManager.h"
#include "X_TaskListWidget.h"
#include "X_TaskContentWidget.h"
//===================================================
X_TaskWidget::X_TaskWidget(QWidget *parent)
    : QWidget{parent}
{
    xh_createComponents();
    xh_createConnections();
    xh_restoreSettings();
}
//===================================================
X_TaskWidget::~X_TaskWidget()
{
    xh_saveSettings();

}
//===================================================
void X_TaskWidget::xh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);


    xv_splitter = new QSplitter(Qt::Horizontal);

    mainLayout->addWidget(xv_splitter);

    xv_taskListWidget = new X_TaskListWidget;
    xv_splitter->addWidget(xv_taskListWidget);

    xv_taskContentWidget = new X_TaskContentWidget;
    xv_splitter->addWidget(xv_taskContentWidget);

}
//===================================================
void X_TaskWidget::xh_createConnections()
{
    connect(xv_taskListWidget, &X_TaskListWidget::xg_requestNewTaskCreation,
            this, &X_TaskWidget::xg_requestNewTaskCreation);
    connect(xv_taskListWidget, &X_TaskListWidget::xg_requestTasksRemoving,
            this, &X_TaskWidget::xg_requestTasksRemoving);

    connect(xv_taskListWidget, &X_TaskListWidget::xg_currentTaskChanged,
            xv_taskContentWidget, &X_TaskContentWidget::xg_currentIndexChanged);
    connect(xv_taskContentWidget, &X_TaskContentWidget::xg_requestTrainingStart,
            this, &X_TaskWidget::xh_initTaskRun);

}
//===================================================
void X_TaskWidget::xh_saveSettings()
{
    QSettings settings;
    settings.setValue("TaskWidgetSplitter", xv_splitter->saveState());

}
//===================================================
void X_TaskWidget::xh_restoreSettings()
{
    QSettings settings;
    xv_splitter->restoreState(settings.value("TaskWidgetSplitter").toByteArray());
}
//===================================================
void X_TaskWidget::xp_setTaskModel(QAbstractItemModel* model)
{
    xv_taskListWidget->xp_setTaskModel(model);
    xv_taskContentWidget->xp_setTaskModel(model);
}
//===================================================
void X_TaskWidget::xh_initTaskRun()
{
    int taskRow =  xv_taskListWidget->xp_currentTaskRow();
    emit xg_requestTaskRun(taskRow);
}
//===================================================





