#ifndef OKNODAILOGOWE_DODAJZADANIE_H
#define OKNODAILOGOWE_DODAJZADANIE_H

#include <QDialog>
#include "zadanie.h"

namespace Ui {
class OknoDailogowe_DodajZadanie;
}

class OknoDailogowe_DodajZadanie : public QDialog
{
    Q_OBJECT

public:
    explicit OknoDailogowe_DodajZadanie(QWidget *parent = nullptr);
    ~OknoDailogowe_DodajZadanie();

    Zadanie getZadanie() const;
    void ustawZadanie(const Zadanie &zadanie);


private:
    Ui::OknoDailogowe_DodajZadanie *ui;
};

#endif
