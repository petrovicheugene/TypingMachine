//===================================================
#ifndef ZTASKCONTENTWIDGET_H
#define ZTASKCONTENTWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QPushButton;
class QTextEdit;

class ZTaskManager;
//===================================================
class ZTaskContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTaskContentWidget(QWidget *parent = nullptr);
    void zp_setContentManagment(ZTaskManager* taskManager);

signals:

private:

    // VARS
    QTextEdit* zv_taskTextEdit;
    QPushButton* zv_saveTaskButton;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

};
//===================================================
#endif // ZTASKCONTENTWIDGET_H
