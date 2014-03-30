/********************************************************************************
** Form generated from reading UI file 'fenetrePrincipake.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETREPRINCIPAKE_H
#define UI_FENETREPRINCIPAKE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fenetrePrincipake
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *LEFichierAutomate;
    QPushButton *PBOuvrirFichierAutomate;
    QTextEdit *log;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *fenetrePrincipake)
    {
        if (fenetrePrincipake->objectName().isEmpty())
            fenetrePrincipake->setObjectName(QStringLiteral("fenetrePrincipake"));
        fenetrePrincipake->resize(400, 300);
        centralWidget = new QWidget(fenetrePrincipake);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        LEFichierAutomate = new QLineEdit(centralWidget);
        LEFichierAutomate->setObjectName(QStringLiteral("LEFichierAutomate"));

        gridLayout->addWidget(LEFichierAutomate, 0, 0, 1, 1);

        PBOuvrirFichierAutomate = new QPushButton(centralWidget);
        PBOuvrirFichierAutomate->setObjectName(QStringLiteral("PBOuvrirFichierAutomate"));

        gridLayout->addWidget(PBOuvrirFichierAutomate, 0, 1, 1, 1);

        log = new QTextEdit(centralWidget);
        log->setObjectName(QStringLiteral("log"));

        gridLayout->addWidget(log, 1, 0, 1, 2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 2, 0, 1, 2);

        fenetrePrincipake->setCentralWidget(centralWidget);

        retranslateUi(fenetrePrincipake);

        QMetaObject::connectSlotsByName(fenetrePrincipake);
    } // setupUi

    void retranslateUi(QMainWindow *fenetrePrincipake)
    {
        fenetrePrincipake->setWindowTitle(QApplication::translate("fenetrePrincipake", "fenetrePrincipake", 0));
        PBOuvrirFichierAutomate->setText(QApplication::translate("fenetrePrincipake", "Ouvrir fichier", 0));
        groupBox->setTitle(QApplication::translate("fenetrePrincipake", "Table de transition de l'automate :", 0));
    } // retranslateUi

};

namespace Ui {
    class fenetrePrincipake: public Ui_fenetrePrincipake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETREPRINCIPAKE_H
