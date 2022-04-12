//===================================================
#include "ZTrainingWidget.h"

#include "ZClickableLabel.h"
#include "ZTaskContentWidget.h"
#include "ZTrainingManager.h"

#include <QApplication>
#include <QDebug>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QVBoxLayout>
//===================================================
//Q_DECLARE_METATYPE(SettingsMap);
//===================================================
ZTrainingWidget::ZTrainingWidget(QWidget *parent)
    : QWidget{parent}
{
    zv_trainingManager = nullptr;

    zv_completedColor = QColor(Qt::green);
    zv_currentSymbolColor = QColor(Qt::white);
    zv_wrongSymbolColor = QColor(Qt::red);
    zv_incompletedColor = QColor(Qt::gray);;
    zv_symbolUnderlinedFlag = true;

    zh_createComponents();
    zh_createConnections();

    zh_restoreSettings();
}
//===================================================
ZTrainingWidget::~ZTrainingWidget()
{
    zh_saveSettings();
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

    zv_minusLabel = new ZClickableLabel(this);
    zv_minusLabel->setText("-");
    zv_plusLabel = new ZClickableLabel(this);
    zv_plusLabel->setText("+");

    basementLayout->addWidget(zv_minusLabel);
    zv_fontSizeSlider = new QSlider(Qt::Horizontal);
<<<<<<< HEAD
    zv_fontSizeSlider->setRange(10, 144);
=======
    zv_fontSizeSlider->setRange(12, 144);
>>>>>>> b266f949e7ec9f16f32bc3ac3d2d7f2a95b23cca
    zv_fontSizeSlider->setToolTip(tr("Font size"));
    basementLayout->addWidget(zv_fontSizeSlider);
    basementLayout->addWidget(zv_plusLabel);

    zv_restartBtn = new QPushButton;
    zv_restartBtn->setIcon(QIcon(":/images/restart.png"));
    zv_restartBtn->setToolTip(tr("Restart task"));
    basementLayout->addWidget(zv_restartBtn);

    zv_finishBtn = new QPushButton;
    zv_finishBtn->setIcon(QIcon(":/images/stop-10.png"));
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

    connect(zv_minusLabel, &ZClickableLabel::clicked,
            this, &ZTrainingWidget::zh_changeFontSizeSliderValue);
    connect(zv_plusLabel, &ZClickableLabel::clicked,
            this, &ZTrainingWidget::zh_changeFontSizeSliderValue);

}
//===================================================
void ZTrainingWidget::zh_restoreSettings()
{
    QSettings settings;
    settings.beginGroup("TrainingWidget");
    QVariant vData = settings.value("FontSize");
    if(vData.isValid() && vData.canConvert<int>())
    {
        zv_fontSizeSlider->setValue(vData.toInt());
    }

    vData = settings.value("CompleteColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        zv_completedColor = vData.value<QColor>();
    }

    vData = settings.value("IncompleteColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        zv_incompletedColor = vData.value<QColor>();
    }

    vData = settings.value("CurrentSymbolColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        zv_currentSymbolColor = vData.value<QColor>();
    }

    vData = settings.value("WrongSymbolColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        zv_wrongSymbolColor = vData.value<QColor>();
    }

    vData = settings.value("SymbolUnderlined");
    if(vData.isValid() && vData.canConvert<bool>())
    {
        zv_symbolUnderlinedFlag = vData.toBool();
    }

    settings.endGroup();
}
//===================================================
void ZTrainingWidget::zh_saveSettings() const
{
    QSettings settings;
    settings.beginGroup("TrainingWidget");
    settings.setValue("FontSize", QVariant(zv_fontSizeSlider->value()));

    settings.setValue("CompleteColor", QVariant::fromValue<QColor>(zv_completedColor));
    settings.setValue("IncompleteColor", QVariant::fromValue<QColor>(zv_incompletedColor));
    settings.setValue("CurrentSymbolColor", QVariant::fromValue<QColor>(zv_currentSymbolColor));
    settings.setValue("WrongSymbolColor", QVariant::fromValue<QColor>(zv_wrongSymbolColor));
    settings.setValue("SymbolUnderlined", zv_symbolUnderlinedFlag);

    settings.endGroup();
}
//===================================================
void ZTrainingWidget::zp_connectToTrainingManager(ZTrainingManager* manager)
{
    zv_trainingManager = manager;
    connect(zv_trainingManager, &ZTrainingManager::zg_stateChanged,
            this, &ZTrainingWidget::zp_update);
}
//===================================================
void ZTrainingWidget::zp_setCompletedColor(QColor color)
{
    zv_completedColor = color;
    zp_update();
}
//===================================================
void ZTrainingWidget::zp_setCurrentSymbolColor(QColor color)
{
    zv_currentSymbolColor = color;
    zp_update();
}
//===================================================
void ZTrainingWidget::zp_setWrongSymbolColor(QColor color)
{
    zv_wrongSymbolColor = color;
    zp_update();
}
//===================================================
void ZTrainingWidget::zp_setIncompletedColor(QColor color)
{
    zv_incompletedColor = color;
    zp_update();
}
//===================================================
void ZTrainingWidget::zp_setCurrentSymbolUnderlined(bool underlined)
{
    zv_symbolUnderlinedFlag = underlined;
    zp_update();
}
//===================================================
QColor ZTrainingWidget::zp_completedColor() const
{
    return zv_completedColor;
}
//===================================================
QColor ZTrainingWidget::zp_currentSymbolColor() const
{
    return zv_currentSymbolColor;
}
//===================================================
QColor ZTrainingWidget::zp_wrongSymbolColor() const
{
    return zv_wrongSymbolColor;
}
//===================================================
QColor ZTrainingWidget::zp_incompletedColor() const
{
    return zv_incompletedColor;
}
//===================================================
bool ZTrainingWidget::zp_isSymbolUnderlined() const
{
    return zv_symbolUnderlinedFlag;
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
void ZTrainingWidget::zh_changeFontSizeSliderValue()
{
    int delta = qApp->keyboardModifiers() & Qt::ControlModifier ?
                zv_fontSizeSlider->singleStep() : zv_fontSizeSlider->pageStep();

    if(sender() == zv_plusLabel)
    {
        zv_fontSizeSlider->setValue(zv_fontSizeSlider->value() + delta);
    }
    else if(sender() == zv_minusLabel)
    {
        zv_fontSizeSlider->setValue(zv_fontSizeSlider->value() - delta);
    }
}
//===================================================
void ZTrainingWidget::zp_update()
{
    QColor symbolColor = zv_trainingManager->zp_isWrong()? zv_wrongSymbolColor : zv_currentSymbolColor;

    QString completedLine = QString("<font color=%1>%2</font>").arg(zv_completedColor.name(),
                                                                    zv_trainingManager->zp_completed());
    QString currentSymbol = zv_symbolUnderlinedFlag?
                "<u>"+zv_trainingManager->zp_currentSymbol()+"</u>" : zv_trainingManager->zp_currentSymbol();
    QString currentSymbolLine = QString("<font color=%1>%2</font>").arg(symbolColor.name(),
                                                                        currentSymbol);
    QString endLine = QString("<font color=%1>%2</font>").arg(zv_incompletedColor.name(),
                                                              zv_trainingManager->zp_incompleted());
    QString displayLine = completedLine + currentSymbolLine + endLine;
    zv_lineLabel->setText(displayLine);
}
//===================================================

