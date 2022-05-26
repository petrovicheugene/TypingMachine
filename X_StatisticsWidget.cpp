//===================================================
#include "X_StatisticsWidget.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QTableView>
#include <QVBoxLayout>

#include <QStandardItemModel>
//===================================================
X_StatisticsWidget::X_StatisticsWidget(QWidget *parent)
    : QWidget{parent}
{
    xh_createComponents();
    xh_createConnections();
}
//===================================================
void X_StatisticsWidget::xh_createComponents()
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

    scrollArea->setWidget(xh_createInfoWidget());
    scrollArea->setWidgetResizable(true);

    // basement
    QHBoxLayout* basementLayout = new QHBoxLayout;
    basementLayout->addStretch(999999);
    mainLayout->addLayout(basementLayout);

    xv_finishButton = new QPushButton;
    xv_finishButton->setIcon(QIcon(":/images/stop-10.png"));
    xv_finishButton->setToolTip(tr("Finish task"));
    basementLayout->addWidget(xv_finishButton);

}
//===================================================
QWidget* X_StatisticsWidget::xh_createInfoWidget()
{
    QWidget* w = new QWidget;
    w->setPalette(QPalette(Qt::yellow));
    w->setAutoFillBackground(true);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    w->setLayout(mainLayout);

    xv_tableView = new QTableView;
    xv_tableView->setMinimumHeight(xv_tableView->sizeHint().height());
    mainLayout->addWidget(xv_tableView);

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
void X_StatisticsWidget::xh_createConnections()
{
    connect(xv_finishButton, &QPushButton::clicked,
            this, &X_StatisticsWidget::xh_onFinish);
}
//===================================================
void X_StatisticsWidget::xp_setStatisticsModel(QAbstractItemModel* model)
{
    xv_tableView->setModel(model);
}
//===================================================
void X_StatisticsWidget::xh_onFinish()
{
    emit xg_requestStatisticsDisplayFinish();
}
//===================================================



