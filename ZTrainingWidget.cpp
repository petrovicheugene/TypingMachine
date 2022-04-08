//===================================================
#include "ZTrainingWidget.h"
#include "ZTrainingManager.h"

#include <QDebug>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

//===================================================
ZTrainingWidget::ZTrainingWidget(QWidget *parent)
    : QWidget{parent}
{
    zv_trainingManager = nullptr;

    zv_completedColor = QColor(Qt::green);
    zv_currentSymbolColor = QColor(Qt::white);
    zv_wrongSymbolColor = QColor(Qt::red);
    zv_incompletedColor = QColor(Qt::gray);;

    zh_createComponents();
    zh_createConnections();

    zh_setFontSize(zv_fontSizeSlider->value());
}
//===================================================
void ZTrainingWidget::zh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addStretch();
    zv_lineLabel = new QLabel;
    zv_lineLabel->setWordWrap(true);
    zv_lineLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(zv_lineLabel);
    mainLayout->addStretch();

    // basement
    QHBoxLayout* basementLayout = new QHBoxLayout;
    basementLayout->addStretch(999999);
    mainLayout->addLayout(basementLayout);

    basementLayout->addWidget(new QLabel("-"));
    zv_fontSizeSlider = new QSlider(Qt::Horizontal);
    zv_fontSizeSlider->setRange(10, 96);
    zv_fontSizeSlider->setToolTip(tr("Font size"));
    basementLayout->addWidget(zv_fontSizeSlider);
    basementLayout->addWidget(new QLabel("+"));

    zv_restartBtn = new QPushButton;
    zv_restartBtn->setIcon(QIcon(":/images/restart.png"));
    zv_restartBtn->setToolTip(tr("Restart task"));
    basementLayout->addWidget(zv_restartBtn);

    zv_finishBtn = new QPushButton;
    zv_finishBtn->setIcon(QIcon(":/images/exitDoor-256.png"));
    zv_finishBtn->setToolTip(tr("Finish task"));
    basementLayout->addWidget(zv_finishBtn);

}
//===================================================
void ZTrainingWidget::zh_createConnections()
{
    connect(zv_finishBtn, &QPushButton::clicked,
            this, &ZTrainingWidget::zg_requestTaskFinish);
    connect(zv_restartBtn, &QPushButton::clicked,
            this, &ZTrainingWidget::zg_requestTaskRestart);
    connect(zv_fontSizeSlider, &QSlider::valueChanged,
            this, &ZTrainingWidget::zh_setFontSize);

}
//===================================================
void ZTrainingWidget::zp_connectToTrainingManager(ZTrainingManager* manager)
{
    zv_trainingManager = manager;
    connect(zv_trainingManager, &ZTrainingManager::zg_stateChanged,
            this, &ZTrainingWidget::zp_update);
}
//===================================================
void ZTrainingWidget::zp_applySettings(QMap<int, QVariant> settings)
{
    if(settings.contains(SN_FONT_SIZE))
    {
        zv_fontSizeSlider->setValue(settings.value(SN_FONT_SIZE).toInt());
    }

    if(settings.contains(SN_COMPLETED_COLOR))
    {
        zv_fontSizeSlider->setValue(settings.value(SN_COMPLETED_COLOR).toInt());
    }
    if(settings.contains(SN_CURRENT_COLOR))
    {
        zv_fontSizeSlider->setValue(settings.value(SN_CURRENT_COLOR).toInt());
    }
    if(settings.contains(SN_INCOMPLETED_COLOR))
    {
        zv_fontSizeSlider->setValue(settings.value(SN_INCOMPLETED_COLOR).toInt());
    }
    if(settings.contains(SN_WRONG_COLOR))
    {
        zv_fontSizeSlider->setValue(settings.value(SN_WRONG_COLOR).toInt());
    }


}
//===================================================
void ZTrainingWidget::zp_setCompletedColor(QColor& color)
{
    zv_completedColor = color;
}
//===================================================
void ZTrainingWidget::zp_setCurrentSymbolColor(QColor& color)
{
    zv_currentSymbolColor = color;
}
//===================================================
void ZTrainingWidget::zp_setWrongSymbolColor(QColor& color)
{
    zv_wrongSymbolColor = color;
}
//===================================================
void ZTrainingWidget::zp_setIncompletedColor(QColor& color)
{
    zv_incompletedColor = color;
}
//===================================================
void ZTrainingWidget::zp_setFontSize(int size)
{
    if(zv_fontSizeSlider->minimum() <= size && size <=  zv_fontSizeSlider->maximum())
    {
        zv_fontSizeSlider->setValue(size);
    }
}
//===================================================
void ZTrainingWidget::zh_setFontSize(int size)
{
    zv_fontSize = size;
    QFont font = zv_lineLabel->font();
    font.setPointSize(size);
    zv_lineLabel->setFont(font);
}
//===================================================
//void ZTrainingWidget::zp_update1()
//{
//    int currentIndex = zv_trainingManager->zp_currentSymbolIndex();
//    bool wrong = zv_trainingManager->zp_isWrong();
//    bool taskActive = zv_trainingManager->zp_isActive();

//    QString line = zv_trainingManager->zp_currentLine();
//    QColor symbolColor = wrong? zv_wrongSymbolColor : zv_currentSymbolColor;
//    QString fontSize = QString::number(zv_fontSize);

//    qDebug() << "FONT SIZE" << fontSize;
//    QString displayLine;
//    if(currentIndex >= line.count() || !taskActive)
//    {
//        // end of line
//        displayLine = QString("<font size=%1 color=%2>%3</font>").arg(fontSize, zv_completedColor.name(), line);;
//    }
//    else
//    {
//        QString completedLine = line.first(currentIndex);
//        QString currentSymbol = line.at(currentIndex);
//        QString endLine = line.last(line.count() - currentIndex - 1);
//        completedLine = QString("<font size=%1 color=%2>%3</font>").arg(fontSize, zv_completedColor.name(), completedLine);
//        currentSymbol = QString("<font size=%1 color=%2><u>%3<u></font>").arg(fontSize, symbolColor.name(), currentSymbol);
//        endLine = QString("<font size=%1 color=%2>%3</font>").arg(fontSize, zv_incompletedColor.name(), endLine);
//        displayLine = completedLine + currentSymbol + endLine;
//    }

//    zv_lineLabel->setText(displayLine);
//}
//===================================================
void ZTrainingWidget::zp_update()
{
    QColor symbolColor = zv_trainingManager->zp_isWrong()? zv_wrongSymbolColor : zv_currentSymbolColor;

    QString completedLine = QString("<font color=%1>%2</font>").arg(zv_completedColor.name(),
                                                                    zv_trainingManager->zp_completed());
    QString currentSymbol = QString("<font color=%1><u>%2<u></font>").arg(symbolColor.name(),
                                                                          zv_trainingManager->zp_currentSymbol());
    QString endLine = QString("<font color=%1>%2</font>").arg(zv_incompletedColor.name(),
                                                              zv_trainingManager->zp_incompleted());
    QString displayLine = completedLine + currentSymbol + endLine;
    zv_lineLabel->setText(displayLine);
}
//===================================================

