/********************************************************************************
** Form generated from reading UI file 'multtablefrm.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTTABLEFRM_H
#define UI_MULTTABLEFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_multTableFrm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer;
    QTableView *tbTableInfo;
    QLabel *label;

    void setupUi(QWidget *multTableFrm)
    {
        if (multTableFrm->objectName().isEmpty())
            multTableFrm->setObjectName(QStringLiteral("multTableFrm"));
        multTableFrm->resize(400, 300);
        gridLayout = new QGridLayout(multTableFrm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(multTableFrm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(multTableFrm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        label_2 = new QLabel(multTableFrm);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(multTableFrm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        label_3 = new QLabel(multTableFrm);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        pushButton_3 = new QPushButton(multTableFrm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tbTableInfo = new QTableView(multTableFrm);
        tbTableInfo->setObjectName(QStringLiteral("tbTableInfo"));
        tbTableInfo->setMinimumSize(QSize(0, 0));
        tbTableInfo->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(129, 131, 21, 255), stop:0.463277 rgba(129, 170, 80, 255), stop:1 rgba(255, 255, 255, 255));"));
        tbTableInfo->setSortingEnabled(true);

        gridLayout->addWidget(tbTableInfo, 1, 0, 1, 1);

        label = new QLabel(multTableFrm);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);


        retranslateUi(multTableFrm);

        QMetaObject::connectSlotsByName(multTableFrm);
    } // setupUi

    void retranslateUi(QWidget *multTableFrm)
    {
        multTableFrm->setWindowTitle(QApplication::translate("multTableFrm", "Form", 0));
        pushButton->setText(QApplication::translate("multTableFrm", "\345\211\215\344\270\200\351\241\265", 0));
        pushButton_2->setText(QApplication::translate("multTableFrm", "\345\220\216\344\270\200\351\241\265", 0));
        label_2->setText(QApplication::translate("multTableFrm", "\350\275\254\345\210\260\347\254\254", 0));
        label_3->setText(QApplication::translate("multTableFrm", "\351\241\265", 0));
        pushButton_3->setText(QApplication::translate("multTableFrm", "Go", 0));
        label->setText(QApplication::translate("multTableFrm", "\346\200\273\345\205\261XX\351\241\265\357\274\214\345\275\223\345\211\215\347\254\254XXXXXX\351\241\265", 0));
    } // retranslateUi

};

namespace Ui {
    class multTableFrm: public Ui_multTableFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTTABLEFRM_H
