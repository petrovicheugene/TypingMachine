//===================================================
#include "ZTaskWidget.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QVBoxLayout>

#include "ZTaskManager.h"
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
void ZTaskWidget::zp_connectToTaskManager(ZTaskManager* taskManager)
{
    zv_taskListWidget->zp_setModelToView(taskManager->zp_taskModel());
    zv_taskContentWidget->zp_setContentManagment(taskManager);
}
//===================================================



