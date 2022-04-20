//===================================================
#include "ZStatisticsWidget.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

//===================================================
ZStatisticsWidget::ZStatisticsWidget(QWidget *parent)
    : QWidget{parent}
{
    zh_createComponents();
    zh_createConnections();

}
//===================================================
void ZStatisticsWidget::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QFormLayout* tabLayout = new QFormLayout;
    mainLayout->addLayout(tabLayout);

    for(int i = 1; i < 30; i++)
    {
        tabLayout->addRow(new QLabel(QString("Bambarbia Cirgudu Arum kusak - %1").arg(QString::number(i))),
                          new QLabel(QString("Vechor ty pomnish vuga zlilas - %1").arg(QString::number(i))));
    }

    // basement
    mainLayout->addStretch();
    QHBoxLayout* basementLayout = new QHBoxLayout;
    basementLayout->addStretch(999999);
    mainLayout->addLayout(basementLayout);

    zv_finishButton = new QPushButton;
    zv_finishButton->setIcon(QIcon(":/images/stop-10.png"));
    zv_finishButton->setToolTip(tr("Finish task"));
    basementLayout->addWidget(zv_finishButton);

}
//===================================================
void ZStatisticsWidget::zh_createConnections()
{
    connect(zv_finishButton, &QPushButton::clicked,
            this, &ZStatisticsWidget::zg_requestStatisticsDisplayFinish);

}
//===================================================
