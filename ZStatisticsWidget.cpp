//===================================================
#include "ZStatisticsWidget.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
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

    // Header
    QLabel* label = new QLabel;

    QFont font = label->font();
    font.setPointSize(28);
    font.setBold(true);
    label->setFont(font);

    label->setText(QString("<font color=%1>%2</font>").arg("red", tr("Statistics")));
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    // Scroll area
    QScrollArea* scrollArea = new QScrollArea;
    mainLayout->addWidget(scrollArea);

    QWidget* w = new QWidget;
    QFormLayout* tabLayout = new QFormLayout;

    for(int i = 1; i < 30; i++)
    {
        tabLayout->addRow(new QLabel(QString("Bambarbia Cirgudu Arum kusak - %1").arg(QString::number(i))),
                          new QLabel(QString("Vechor ty pomnish vuga zlilas - %1").arg(QString::number(i))));
    }

    w->setLayout(tabLayout);
    scrollArea->setWidget(w);

    // basement
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
