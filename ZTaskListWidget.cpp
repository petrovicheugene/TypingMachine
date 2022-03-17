//===================================================
#include "ZTaskListWidget.h"


#include <QDialogButtonBox>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>

//===================================================
ZTaskListWidget::ZTaskListWidget(QWidget *parent)
    : QWidget{parent}
{
    zh_createComponents();
    zh_createConnections();

}
//===================================================
void ZTaskListWidget::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    zv_taskListView = new QTableView;
    mainLayout->addWidget(zv_taskListView);


    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);

    zv_newTaskButton = new QPushButton(tr("New"));
    buttonBox->addButton(zv_newTaskButton, QDialogButtonBox::ActionRole);
    zv_deleteTasklButton = new QPushButton(tr("Delete"));
    buttonBox->addButton(zv_deleteTasklButton, QDialogButtonBox::ActionRole);
    zv_runTaskButton = new QPushButton(tr("Run"));
    buttonBox->addButton(zv_runTaskButton, QDialogButtonBox::ActionRole);

}
//===================================================
void ZTaskListWidget::zh_createConnections()
{

}
//===================================================
void ZTaskListWidget::zp_setModelToView(QAbstractItemModel* model)
{
    zv_taskListView->setModel(model);
}
//===================================================
