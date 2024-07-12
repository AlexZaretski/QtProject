/********************************************************************************
** Form generated from reading UI file 'widgethard.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETHARD_H
#define UI_WIDGETHARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgethard
{
public:

    void setupUi(QWidget *widgethard)
    {
        if (widgethard->objectName().isEmpty())
            widgethard->setObjectName("widgethard");
        widgethard->resize(400, 300);

        retranslateUi(widgethard);

        QMetaObject::connectSlotsByName(widgethard);
    } // setupUi

    void retranslateUi(QWidget *widgethard)
    {
        widgethard->setWindowTitle(QCoreApplication::translate("widgethard", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widgethard: public Ui_widgethard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETHARD_H
