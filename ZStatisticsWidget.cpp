//===================================================
#include "ZStatisticsWidget.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QTableView>
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
    font.setPointSize(18);
    //font.setBold(true);
    label->setFont(font);

    label->setText(QString("<font color=%1>%2</font>").arg("red", tr("Statistics")));
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    // Scroll area
    QScrollArea* scrollArea = new QScrollArea;
    mainLayout->addWidget(scrollArea);

    scrollArea->setWidget(zh_createInfoWidget());
    scrollArea->setWidgetResizable(true);

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
QWidget* ZStatisticsWidget::zh_createInfoWidget()
{
    QWidget* w = new QWidget;
    w->setPalette(QPalette(Qt::yellow));
    w->setAutoFillBackground(true);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    w->setLayout(mainLayout);

    zv_statsTableView = new QTableView;
    zv_statsTableView->setMinimumHeight(zv_statsTableView->sizeHint().height());
    mainLayout->addWidget(zv_statsTableView);

    QFormLayout* fLayout = new QFormLayout;

    for(int i = 0; i < 10; ++i)
    {
        QLabel* l1 = new QLabel;
        l1->setText(QString("Bambarbia Cirgudu azym kusak - %1").arg(QString::number(i)));

        QLabel* l2 = new QLabel;
        l2->setText(QString("Nag sedoi ravninoi mora  - %1").arg(QString::number(i)));

        fLayout->addRow(l1, l2);
    }

    mainLayout->addLayout(fLayout);

    return w;
}
//===================================================
void ZStatisticsWidget::zh_createConnections()
{
    connect(zv_finishButton, &QPushButton::clicked,
            this, &ZStatisticsWidget::zg_requestStatisticsDisplayFinish);

}
//===================================================
void ZStatisticsWidget::zp_setStatisticsModel(QAbstractItemModel* model)
{

}
//===================================================


