#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_Add_clicked();
    void loadFilesFromFile(const QString &path);
    void saveAllTasksToFile(const QString &path);


    void on_Edit_clicked();
    void on_Delete_clicked();

private:
    Ui::MainWindow *ui;
};
#endif
