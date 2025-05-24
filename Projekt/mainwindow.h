#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zadanie.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();     // Dodaj
    void on_pushButton_2_clicked();   // Usuń
    void loadZadania();

private:
    Ui::MainWindow *ui;
    QVector<Zadanie> zadania;
    void saveZadaniaToFile();
    void refreshTable();
};
#endif // MAINWINDOW_H
