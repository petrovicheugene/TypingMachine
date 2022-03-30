//===================================================
#include "ZTrainingWidget.h"

#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

//===================================================
ZTrainingWidget::ZTrainingWidget(QWidget *parent)
    : QWidget{parent}
{
    zh_createComponents();
    zh_createConnections();
}
//===================================================
void ZTrainingWidget::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // basement
    QDialogButtonBox* buttonBox = new QDialogButtonBox;

    zv_stopBtn = new QPushButton(tr("Stop"));
    buttonBox->addButton(zv_stopBtn, QDialogButtonBox::ActionRole);
    mainLayout->addWidget(buttonBox);

}
//===================================================
void ZTrainingWidget::zh_createConnections()
{
    connect(zv_stopBtn, &QPushButton::clicked,
            this, &ZTrainingWidget::zg_requestTaskStop);
}
//===================================================
void ZTrainingWidget::zp_connectToTrainingManager(ZTrainingManager* taskManager)
{

}
//===================================================

