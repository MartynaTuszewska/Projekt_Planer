/********************************************************************************
** Form generated from reading UI file 'oknodailogowe_dodajzadanie.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNODAILOGOWE_DODAJZADANIE_H
#define UI_OKNODAILOGOWE_DODAJZADANIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_OknoDailogowe_DodajZadanie
{
public:
    QDialogButtonBox *approvedDialog;
    QLineEdit *tytulDialog;
    QComboBox *dzienDialog;
    QSpinBox *priorytetDialog;
    QTextEdit *notatkaDialog;

    void setupUi(QDialog *OknoDailogowe_DodajZadanie)
    {
        if (OknoDailogowe_DodajZadanie->objectName().isEmpty())
            OknoDailogowe_DodajZadanie->setObjectName("OknoDailogowe_DodajZadanie");
        OknoDailogowe_DodajZadanie->resize(400, 300);
        approvedDialog = new QDialogButtonBox(OknoDailogowe_DodajZadanie);
        approvedDialog->setObjectName("approvedDialog");
        approvedDialog->setGeometry(QRect(120, 230, 171, 32));
        approvedDialog->setOrientation(Qt::Orientation::Horizontal);
        approvedDialog->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        tytulDialog = new QLineEdit(OknoDailogowe_DodajZadanie);
        tytulDialog->setObjectName("tytulDialog");
        tytulDialog->setGeometry(QRect(140, 30, 113, 20));
        dzienDialog = new QComboBox(OknoDailogowe_DodajZadanie);
        dzienDialog->setObjectName("dzienDialog");
        dzienDialog->setGeometry(QRect(150, 70, 101, 22));
        priorytetDialog = new QSpinBox(OknoDailogowe_DodajZadanie);
        priorytetDialog->setObjectName("priorytetDialog");
        priorytetDialog->setGeometry(QRect(160, 110, 71, 31));
        notatkaDialog = new QTextEdit(OknoDailogowe_DodajZadanie);
        notatkaDialog->setObjectName("notatkaDialog");
        notatkaDialog->setGeometry(QRect(140, 150, 104, 64));

        retranslateUi(OknoDailogowe_DodajZadanie);
        QObject::connect(approvedDialog, &QDialogButtonBox::accepted, OknoDailogowe_DodajZadanie, qOverload<>(&QDialog::accept));
        QObject::connect(approvedDialog, &QDialogButtonBox::rejected, OknoDailogowe_DodajZadanie, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(OknoDailogowe_DodajZadanie);
    } // setupUi

    void retranslateUi(QDialog *OknoDailogowe_DodajZadanie)
    {
        OknoDailogowe_DodajZadanie->setWindowTitle(QCoreApplication::translate("OknoDailogowe_DodajZadanie", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OknoDailogowe_DodajZadanie: public Ui_OknoDailogowe_DodajZadanie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNODAILOGOWE_DODAJZADANIE_H
