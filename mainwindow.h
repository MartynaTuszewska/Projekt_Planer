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
    void on_Dodaj_clicked();
    void wczytajZadaniaZPliku(const QString &sciezka);
    void zapiszWszystkieZadaniaDoPliku(const QString &sciezka);


    void on_Edytuj_clicked();
    void on_Usun_clicked();

private:
    Ui::MainWindow *ui;
};
#endif
