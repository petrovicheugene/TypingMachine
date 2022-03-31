//===================================================
#include "ZTaskListWidget.h"

#include <QDialogButtonBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QItemSelectionModel>
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

    zv_newTaskButton = new QPushButton();
    zv_newTaskButton->setIcon(QIcon(":/images/add-256.png"));
    zv_newTaskButton->setToolTip(tr("New task"));
    buttonBox->addButton(zv_newTaskButton, QDialogButtonBox::ActionRole);
    zv_deleteTasklButton = new QPushButton();
    zv_deleteTasklButton->setIcon(QIcon(":/images/remove-256.png"));
    zv_deleteTasklButton->setToolTip(tr("Remove selected tasks"));
    buttonBox->addButton(zv_deleteTasklButton, QDialogButtonBox::ActionRole);
}
//===================================================
void ZTaskListWidget::zh_createConnections()
{
    connect(zv_newTaskButton, &QPushButton::clicked,
            this, &ZTaskListWidget::zh_initNewTaskCreation);
    connect(zv_deleteTasklButton, &QPushButton::clicked,
            this, &ZTaskListWidget::zh_initTaskRemoving);

}
//===================================================
void ZTaskListWidget::zp_setTaskModel(QAbstractItemModel* model)
{
    zv_taskListView->setModel(model);
    zv_taskListView->setColumnHidden(0, true);
    zv_taskListView->setColumnHidden(2, true);
    zv_taskListView->setColumnHidden(3, true);
    zv_taskListView->setColumnHidden(4, true);
    zv_taskListView->setColumnHidden(5, true);
    zv_taskListView->setColumnHidden(6, true);

    zv_taskListView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    connect(model, &QAbstractItemModel::rowsInserted,
            this, &ZTaskListWidget::zh_onNewTaskInserting);
    connect(zv_taskListView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &ZTaskListWidget::zh_onCurrentRowChange);
}
//===================================================
void ZTaskListWidget::zh_initNewTaskCreation()
{
    emit zg_requestNewTaskCreation();
}
//===================================================
void ZTaskListWidget::zh_onNewTaskInserting(const QModelIndex& index, int first, int last)
{
    QModelIndex taskIndex = zv_taskListView->model()->index(last, 1);
    zv_taskListView->setCurrentIndex(taskIndex);
    zv_taskListView->edit(taskIndex);
}
//===================================================
void ZTaskListWidget::zh_initTaskRemoving()
{
    QModelIndexList currentIndices = zv_taskListView->selectionModel()->selectedIndexes();
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

    emit zg_requestTasksRemoving(rows);
}
//===================================================
int ZTaskListWidget::zp_currentTaskRow() const
{
    return zv_taskListView->currentIndex().row();
}
//===================================================
void ZTaskListWidget::zh_onCurrentRowChange(const QModelIndex &current,
                                            const QModelIndex & previous)
{
    emit zg_currentTaskChanged(current.row());
}
//===================================================




