//===================================================
#include "ZTaskContentWidget.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QTextEdit>
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

    zv_taskTextEdit = new QTextEdit;
    mainLayout->addWidget(zv_taskTextEdit);

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);

    zv_saveTaskButton = new QPushButton(tr("Save"));
    buttonBox->addButton(zv_saveTaskButton, QDialogButtonBox::ActionRole);


}
//===================================================
void ZTaskContentWidget::zh_createConnections()
{

}
//===================================================
void ZTaskContentWidget::zp_setContentManagment(ZTaskManager* taskManager)
{

}
//===================================================

