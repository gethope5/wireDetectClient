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
    QTableView *tbTableInfo;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbtnFront;
    QPushButton *pbtnNext;
    QLabel *label_2;
    QLineEdit *lneJump;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label;

    void setupUi(QWidget *multTableFrm)
    {
        if (multTableFrm->objectName().isEmpty())
            multTableFrm->setObjectName(QStringLiteral("multTableFrm"));
        multTableFrm->resize(628, 362);
        gridLayout = new QGridLayout(multTableFrm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tbTableInfo = new QTableView(multTableFrm);
        tbTableInfo->setObjectName(QStringLiteral("tbTableInfo"));
        tbTableInfo->setMinimumSize(QSize(0, 0));
        tbTableInfo->setStyleSheet(QStringLiteral(""));
        tbTableInfo->setSortingEnabled(true);

        gridLayout->addWidget(tbTableInfo, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pbtnFront = new QPushButton(multTableFrm);
        pbtnFront->setObjectName(QStringLiteral("pbtnFront"));

        horizontalLayout->addWidget(pbtnFront);

        pbtnNext = new QPushButton(multTableFrm);
        pbtnNext->setObjectName(QStringLiteral("pbtnNext"));

        horizontalLayout->addWidget(pbtnNext);

        label_2 = new QLabel(multTableFrm);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lneJump = new QLineEdit(multTableFrm);
        lneJump->setObjectName(QStringLiteral("lneJump"));
        lneJump->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(lneJump);

        label_3 = new QLabel(multTableFrm);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        pushButton_3 = new QPushButton(multTableFrm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(multTableFrm);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(multTableFrm);

        QMetaObject::connectSlotsByName(multTableFrm);
    } // setupUi

    void retranslateUi(QWidget *multTableFrm)
    {
        multTableFrm->setWindowTitle(QApplication::translate("multTableFrm", "Form", 0));
        pbtnFront->setText(QApplication::translate("multTableFrm", "\345\211\215\344\270\200\351\241\265", 0));
        pbtnNext->setText(QApplication::translate("multTableFrm", "\345\220\216\344\270\200\351\241\265", 0));
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
