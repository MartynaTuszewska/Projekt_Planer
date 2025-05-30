#ifndef OKNODAILOGOWE_DODAJZADANIE_H
#define OKNODAILOGOWE_DODAJZADANIE_H

#include <QDialog>
#include "zadanie.h"

namespace Ui {
class DialogWindow_AddTask;
}

class DialogWindow_AddTask : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWindow_AddTask(QWidget *parent = nullptr);
    ~DialogWindow_AddTask();

    Task getTask() const;
    void setTask(const Task &task);


private:
    Ui::DialogWindow_AddTask *ui;
};

#endif
