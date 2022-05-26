//===================================================
#include "X_TrainingWidget.h"

#include "X_ClickableLabel.h"
#include "X_TaskContentWidget.h"

#include <QApplication>
#include <QDebug>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QTime>
#include <QVBoxLayout>
//===================================================
//Q_DECLARE_METATYPE(SettingsMap);
//===================================================
X_TrainingWidget::X_TrainingWidget(QWidget *parent)
    : QWidget{parent}
{
    xv_trainingManager = nullptr;

    xv_completedColor = QColor(Qt::green);
    xv_currentSymbolColor = QColor(Qt::white);
    xv_wrongSymbolColor = QColor(Qt::red);
    xv_incompletedColor = QColor(Qt::gray);
    xv_symbolUnderlinedFlag = true;

    xv_infoColor = QColor(Qt::gray);
    xv_taskDurationDisplayFlag = true;


    xh_createComponents();
    xh_createConnections();
    xh_restoreSettings();
}
//===================================================
X_TrainingWidget::~X_TrainingWidget()
{
    xh_saveSettings();
}
//===================================================
void X_TrainingWidget::xh_createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addStretch();
    xv_lineLabel = new QLabel;
    xv_lineLabel->setWordWrap(true);
    xv_lineLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(xv_lineLabel);
    mainLayout->addStretch();

    xv_taskDurationLabel = new QLabel;
    xv_taskDurationLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mainLayout->addWidget(xv_taskDurationLabel);

    // basement
    QHBoxLayout* basementLayout = new QHBoxLayout;
    basementLayout->addStretch(999999);
    mainLayout->addLayout(basementLayout);

    xv_minusLabel = new X_ClickableLabel(this);
    xv_minusLabel->setText("-");
    xv_plusLabel = new X_ClickableLabel(this);
    xv_plusLabel->setText("+");

    basementLayout->addWidget(xv_minusLabel);
    xv_fontSizeSlider = new QSlider(Qt::Horizontal);
    xv_fontSizeSlider->setRange(12, 144);
    xv_fontSizeSlider->setToolTip(tr("Font size"));
    basementLayout->addWidget(xv_fontSizeSlider);
    basementLayout->addWidget(xv_plusLabel);

    xv_restartButton = new QPushButton;
    xv_restartButton->setIcon(QIcon(":/images/restart.png"));
    xv_restartButton->setToolTip(tr("Restart task"));
    basementLayout->addWidget(xv_restartButton);

    xv_pauseButton = new QPushButton;
    xv_pauseButton->setCheckable(true);
    xv_pauseButton->setIcon(QIcon(":/images/pause-6.png"));
    xv_pauseButton->setToolTip(tr("Pause task"));
    basementLayout->addWidget(xv_pauseButton);

    xv_finishButton = new QPushButton;
    xv_finishButton->setIcon(QIcon(":/images/stop-10.png"));
    xv_finishButton->setToolTip(tr("Finish task"));
    basementLayout->addWidget(xv_finishButton);

}
//===================================================
void X_TrainingWidget::xh_createConnections()
{
    connect(xv_finishButton, &QPushButton::clicked,
            this, &X_TrainingWidget::xg_requestTaskFinish);
    connect(xv_pauseButton, &QPushButton::toggled,
            this, &X_TrainingWidget::xp_onTaskPauseToggle);
    connect(xv_restartButton, &QPushButton::clicked,
            this, &X_TrainingWidget::xg_requestTaskRestart);
    connect(xv_fontSizeSlider, &QSlider::valueChanged,
            this, &X_TrainingWidget::xh_setFontSize);

    connect(xv_minusLabel, &X_ClickableLabel::clicked,
            this, &X_TrainingWidget::xh_changeFontSizeSliderValue);
    connect(xv_plusLabel, &X_ClickableLabel::clicked,
            this, &X_TrainingWidget::xh_changeFontSizeSliderValue);

}
//===================================================
void X_TrainingWidget::xh_restoreSettings()
{
    QSettings settings;
    settings.beginGroup("TrainingWidget");
    QVariant vData = settings.value("FontSize");
    if(vData.isValid() && vData.canConvert<int>())
    {
        xv_fontSizeSlider->setValue(vData.toInt());
    }

    vData = settings.value("CompleteColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        xv_completedColor = vData.value<QColor>();
    }

    vData = settings.value("IncompleteColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        xv_incompletedColor = vData.value<QColor>();
    }

    vData = settings.value("CurrentSymbolColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        xv_currentSymbolColor = vData.value<QColor>();
    }

    vData = settings.value("WrongSymbolColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        xv_wrongSymbolColor = vData.value<QColor>();
    }

    vData = settings.value("SymbolUnderlined");
    if(vData.isValid() && vData.canConvert<bool>())
    {
        xv_symbolUnderlinedFlag = vData.toBool();
    }

    // INFO
    vData = settings.value("InfoFontSize");
    if(vData.isValid() && vData.canConvert<int>())
    {
        xp_setInfoFontSize(vData.toInt());
    }

    vData = settings.value("InfoColor");
    if(vData.isValid() && vData.canConvert<QColor>())
    {
        xv_infoColor = vData.value<QColor>();
    }

    vData = settings.value("DisplayTaskDuration");
    if(vData.isValid() && vData.canConvert<bool>())
    {
        xv_taskDurationDisplayFlag = vData.toBool();
    }

    settings.endGroup();
}
//===================================================
void X_TrainingWidget::xh_saveSettings() const
{
    QSettings settings;
    settings.beginGroup("TrainingWidget");
    settings.setValue("FontSize", QVariant(xv_fontSizeSlider->value()));

    settings.setValue("CompleteColor", QVariant::fromValue<QColor>(xv_completedColor));
    settings.setValue("IncompleteColor", QVariant::fromValue<QColor>(xv_incompletedColor));
    settings.setValue("CurrentSymbolColor", QVariant::fromValue<QColor>(xv_currentSymbolColor));
    settings.setValue("WrongSymbolColor", QVariant::fromValue<QColor>(xv_wrongSymbolColor));
    settings.setValue("SymbolUnderlined", xv_symbolUnderlinedFlag);

    settings.setValue("InfoFontSize", QVariant(xp_infoFontSize()));
    settings.setValue("InfoColor", QVariant::fromValue<QColor>(xv_infoColor));
    settings.setValue("DisplayTaskDuration", xv_taskDurationDisplayFlag);

    settings.endGroup();
}
//===================================================
void X_TrainingWidget::xp_connectToTrainingManager(X_TrainingManager* manager)
{
    xv_trainingManager = manager;
    connect(xv_trainingManager, &X_TrainingManager::xg_lineChanged,
            this, &X_TrainingWidget::xp_updateLine);
    connect(xv_trainingManager, &X_TrainingManager::xg_durationChanged,
            this, &X_TrainingWidget::xp_updateDuration);
    connect(this, &X_TrainingWidget::xg_requestTaskFinish,
            xv_trainingManager, &X_TrainingManager::xp_stopTask);
    connect(xv_trainingManager, &X_TrainingManager::xg_taskStateChanged,
            this, &X_TrainingWidget::xp_onTaskStateChange);
}
//===================================================
void X_TrainingWidget::xp_setCompletedColor(QColor color)
{
    xv_completedColor = color;
    xp_updateLine();
}
//===================================================
void X_TrainingWidget::xp_setCurrentSymbolColor(QColor color)
{
    xv_currentSymbolColor = color;
    xp_updateLine();
}
//===================================================
void X_TrainingWidget::xp_setWrongSymbolColor(QColor color)
{
    xv_wrongSymbolColor = color;
    xp_updateLine();
}
//===================================================
void X_TrainingWidget::xp_setIncompletedColor(QColor color)
{
    xv_incompletedColor = color;
    xp_updateLine();
}
//===================================================
void X_TrainingWidget::xp_setCurrentSymbolUnderlined(bool underlined)
{
    xv_symbolUnderlinedFlag = underlined;
    xp_updateLine();
}
//===================================================
void X_TrainingWidget::xp_setInfoColor(QColor color)
{
    xv_infoColor = color;
}
//===================================================
void X_TrainingWidget::xp_setTaskDurationDisplayFlag(bool displayFlag)
{
    xv_taskDurationDisplayFlag = displayFlag;
    if(!xv_taskDurationDisplayFlag)
    {
        xv_taskDurationLabel->clear();
    }
}
//===================================================
QColor X_TrainingWidget::xp_completedColor() const
{
    return xv_completedColor;
}
//===================================================
QColor X_TrainingWidget::xp_currentSymbolColor() const
{
    return xv_currentSymbolColor;
}
//===================================================
QColor X_TrainingWidget::xp_wrongSymbolColor() const
{
    return xv_wrongSymbolColor;
}
//===================================================
QColor X_TrainingWidget::xp_incompletedColor() const
{
    return xv_incompletedColor;
}
//===================================================
bool X_TrainingWidget::xp_isSymbolUnderlined() const
{
    return xv_symbolUnderlinedFlag;
}
//===================================================
QColor X_TrainingWidget::xp_infoColor() const
{
    return xv_infoColor;
}
//===================================================
bool X_TrainingWidget::xp_isTaskDurationDisplayed() const
{
    return xv_taskDurationDisplayFlag;
}
//===================================================
int X_TrainingWidget::xp_infoFontSize() const
{
    return xv_taskDurationLabel->font().pointSize();
}
//===================================================
void X_TrainingWidget::xp_setFontSize(int size)
{
    if(xv_fontSizeSlider->minimum() <= size && size <=  xv_fontSizeSlider->maximum())
    {
        xv_fontSizeSlider->setValue(size);
    }
}
//===================================================
void X_TrainingWidget::xh_setFontSize(int size)
{
    xv_fontSize = size;
    QFont font = xv_lineLabel->font();
    font.setPointSize(size);
    xv_lineLabel->setFont(font);
}
//===================================================
void X_TrainingWidget::xp_setInfoFontSize(int size)
{
    QFont font = xv_taskDurationLabel->font();
    font.setPointSize(size);
    xv_taskDurationLabel->setFont(font);
}
//===================================================
void X_TrainingWidget::xp_setInfoFontSizeString(QString sizeString)
{
    bool ok = false;
    int size = sizeString.toInt(&ok);
    if(ok)
    {
        xp_setInfoFontSize(size);
    }

}
//===================================================
void X_TrainingWidget::xh_changeFontSizeSliderValue()
{
    int delta = qApp->keyboardModifiers() & Qt::ControlModifier ?
                xv_fontSizeSlider->singleStep() : xv_fontSizeSlider->pageStep();

    if(sender() == xv_plusLabel)
    {
        xv_fontSizeSlider->setValue(xv_fontSizeSlider->value() + delta);
    }
    else if(sender() == xv_minusLabel)
    {
        xv_fontSizeSlider->setValue(xv_fontSizeSlider->value() - delta);
    }
}
//===================================================
void X_TrainingWidget::xp_onTaskPauseToggle(bool checked)
{
    xh_pauseButtonControl(checked);
    emit xg_requestTaskPauseToggle(checked);
}
//===================================================
void X_TrainingWidget::xh_pauseButtonControl(bool paused, bool enabled)
{
    if(paused)
    {
        xv_pauseButton->setToolTip(tr("Resume task"));
        xv_pauseButton->setIcon(QIcon(":/images/start-8.png"));
    }
    else
    {
        xv_pauseButton->setToolTip(tr("Pause task"));
        xv_pauseButton->setIcon(QIcon(":/images/pause-6.png"));
    }

    xv_pauseButton->setEnabled(enabled);
}
//===================================================
void X_TrainingWidget::xp_updateLine()
{
    QColor symbolColor = xv_trainingManager->xp_isWrong()? xv_wrongSymbolColor : xv_currentSymbolColor;

    QString completedLine = QString("<font color=%1>%2</font>").arg(xv_completedColor.name(),
                                                                    xv_trainingManager->xp_completedLine());
    QString currentSymbol = xv_symbolUnderlinedFlag?
                "<u>"+xv_trainingManager->xp_currentSymbol()+"</u>" : xv_trainingManager->xp_currentSymbol();
    QString currentSymbolLine = QString("<font color=%1>%2</font>").arg(symbolColor.name(),
                                                                        currentSymbol);
    QString endLine = QString("<font color=%1>%2</font>").arg(xv_incompletedColor.name(),
                                                              xv_trainingManager->xp_incompletedLine());
    QString displayLine = completedLine + currentSymbolLine + endLine;
    xv_lineLabel->setText(displayLine);

}
//===================================================
void X_TrainingWidget::xp_updateDuration(int duration)
{
    if(xv_taskDurationDisplayFlag)
    {
        int hours = duration / 3600;
        int minutes = (duration - hours * 3600) / 60;
        int seconds = duration - hours * 3600 - minutes * 60;

        QString durationText =  QString("<font color=%1><b>%2</b></font>").
                arg(xv_infoColor.name(), QTime(hours, minutes, seconds).toString("hh:mm:ss"));

        xv_taskDurationLabel->setText(durationText);

    }
}
//===================================================
void X_TrainingWidget::xp_onTaskStateChange(X_TrainingManager::TASK_STATE previous,
                                           X_TrainingManager::TASK_STATE current)
{
    bool paused = current == X_TrainingManager::TS_PAUSED;
    bool enabled = current != X_TrainingManager::TS_COMPLETED &&
            current != X_TrainingManager::TS_INACTIVE;

    xh_pauseButtonControl(paused, enabled);
    xp_updateLine();
}
//===================================================
