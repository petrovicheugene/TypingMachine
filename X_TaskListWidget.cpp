//===================================================
#include "X_TaskListWidget.h"

#include <QDialogButtonBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QItemSelectionModel>
#include <QTableView>
#include <QVBoxLayout>
//===================================================
X_TaskListWidget::X_TaskListWidget(QWidget *parent)
    : QWidget{parent}
{
    xh_createComponents();
    xh_createConnections();

}
//===================================================
void X_TaskListWidget::xh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    xv_taskListView = new QTableView;
    mainLayout->addWidget(xv_taskListView);

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);

    xv_newTaskButton = new QPushButton();
    xv_newTaskButton->setIcon(QIcon(":/images/add-6.png"));
    xv_newTaskButton->setToolTip(tr("New task"));
    buttonBox->addButton(xv_newTaskButton, QDialogButtonBox::ActionRole);
    xv_deleteTasklButton = new QPushButton();
    xv_deleteTasklButton->setIcon(QIcon(":/images/remove-6.png"));
    xv_deleteTasklButton->setToolTip(tr("Remove selected tasks"));
    buttonBox->addButton(xv_deleteTasklButton, QDialogButtonBox::ActionRole);
}
//===================================================
void X_TaskListWidget::xh_createConnections()
{
    connect(xv_newTaskButton, &QPushButton::clicked,
            this, &X_TaskListWidget::xh_initNewTaskCreation);
    connect(xv_deleteTasklButton, &QPushButton::clicked,
            this, &X_TaskListWidget::xh_initTaskRemoving);

}
//===================================================
void X_TaskListWidget::xp_setTaskModel(QAbstractItemModel* model)
{
    xv_taskListView->setModel(model);
    xv_taskListView->setColumnHidden(0, true);
    xv_taskListView->setColumnHidden(2, true);
    xv_taskListView->setColumnHidden(3, true);
    xv_taskListView->setColumnHidden(4, true);
    xv_taskListView->setColumnHidden(5, true);
    xv_taskListView->setColumnHidden(6, true);

    xv_taskListView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    connect(model, &QAbstractItemModel::rowsInserted,
            this, &X_TaskListWidget::xh_onNewTaskInserting);
    connect(xv_taskListView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &X_TaskListWidget::xh_onCurrentRowChange);
}
//===================================================
void X_TaskListWidget::xh_initNewTaskCreation()
{
    emit xg_requestNewTaskCreation();
}
//===================================================
void X_TaskListWidget::xh_onNewTaskInserting(const QModelIndex& index, int first, int last)
{
    QModelIndex taskIndex = xv_taskListView->model()->index(last, 1);
    xv_taskListView->setCurrentIndex(taskIndex);
    xv_taskListView->edit(taskIndex);
}
//===================================================
void X_TaskListWidget::xh_initTaskRemoving()
{
    QModelIndexList currentIndices = xv_taskListView->selectionModel()->selectedIndexes();
    if(currentIndices.isEmpty())
    {
        return;
    }

    QVector<int> rows;
    foreach(auto index, currentIndices)
    {
        if(!index.isValid())
        {
            continue;
        }

        rows.append(index.row());
    }

    QString msg = tr("Remove selected tasks?");
    if(QMessageBox::question(this, tr("Task removing"), msg,
                             QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
    {
        return;
    }

    emit xg_requestTasksRemoving(rows);
}
//===================================================
int X_TaskListWidget::xp_currentTaskRow() const
{
    return xv_taskListView->currentIndex().row();
}
//===================================================
void X_TaskListWidget::xh_onCurrentRowChange(const QModelIndex &current,
                                            const QModelIndex & previous)
{
    emit xg_currentTaskChanged(current.row());
}
//===================================================




