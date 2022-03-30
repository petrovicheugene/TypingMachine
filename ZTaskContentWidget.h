//===================================================
#ifndef ZTASKCONTENTWIDGET_H
#define ZTASKCONTENTWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QDataWidgetMapper;
class QLabel;
class QPushButton;
class QSlider;
class QSplitter;
class QPlainTextEdit;

class ZTrainingManager;
//===================================================
class ZTaskContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTaskContentWidget(QWidget *parent = nullptr);
    void zp_setContentManagment(ZTrainingManager* taskManager);

    void zp_setTaskModel(QAbstractItemModel* model);


signals:

    void zg_currentIndexChanged(int index);
    void zg_requestTrainingStart();

private slots:

    void zh_setFontPointSize(int val);

private:

    // VARS
    QDataWidgetMapper* zv_mapper;

    QLabel* zv_taskNameLabel;
    QPlainTextEdit* zv_taskTextEdit;
    QSlider* zv_fontSizeSlider;
    QPushButton* zv_runTaskButton;


    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

};
//===================================================
#endif // ZTASKCONTENTWIDGET_H
