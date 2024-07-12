/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName("StartWindow");
        StartWindow->resize(578, 437);
        pushButton = new QPushButton(StartWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 270, 251, 29));
        pushButton_2 = new QPushButton(StartWindow);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(312, 270, 251, 29));
        label = new QLabel(StartWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 160, 311, 41));

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QWidget *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("StartWindow", "Easy", nullptr));
        pushButton_2->setText(QCoreApplication::translate("StartWindow", "Hard", nullptr));
        label->setText(QCoreApplication::translate("StartWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700; color:#55007f;\">Choose level difficulty</span></p><p><br/></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
