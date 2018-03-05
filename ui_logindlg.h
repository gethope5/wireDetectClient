/********************************************************************************
** Form generated from reading UI file 'logindlg.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDLG_H
#define UI_LOGINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_loginDlg
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pbtnOk;
    QPushButton *pbtnCancel;
    QCheckBox *chbModifyDeviceNo;

    void setupUi(QDialog *loginDlg)
    {
        if (loginDlg->objectName().isEmpty())
            loginDlg->setObjectName(QStringLiteral("loginDlg"));
        loginDlg->resize(400, 202);
        loginDlg->setStyleSheet(QString::fromUtf8("font: 750 13pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label = new QLabel(loginDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 111, 41));
        lineEdit = new QLineEdit(loginDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(150, 30, 131, 20));
        pbtnOk = new QPushButton(loginDlg);
        pbtnOk->setObjectName(QStringLiteral("pbtnOk"));
        pbtnOk->setGeometry(QRect(150, 140, 111, 51));
        pbtnCancel = new QPushButton(loginDlg);
        pbtnCancel->setObjectName(QStringLiteral("pbtnCancel"));
        pbtnCancel->setGeometry(QRect(280, 140, 111, 51));
        chbModifyDeviceNo = new QCheckBox(loginDlg);
        chbModifyDeviceNo->setObjectName(QStringLiteral("chbModifyDeviceNo"));
        chbModifyDeviceNo->setGeometry(QRect(30, 60, 181, 41));

        retranslateUi(loginDlg);

        QMetaObject::connectSlotsByName(loginDlg);
    } // setupUi

    void retranslateUi(QDialog *loginDlg)
    {
        loginDlg->setWindowTitle(QApplication::translate("loginDlg", "Dialog", 0));
        label->setText(QApplication::translate("loginDlg", "\347\231\273\351\231\206\345\257\206\347\240\201", 0));
        pbtnOk->setText(QApplication::translate("loginDlg", "\347\241\256\345\256\232", 0));
        pbtnCancel->setText(QApplication::translate("loginDlg", "\345\217\226\346\266\210", 0));
        chbModifyDeviceNo->setText(QApplication::translate("loginDlg", "\344\277\256\346\224\271\350\256\276\345\244\207\347\274\226\345\217\267", 0));
    } // retranslateUi

};

namespace Ui {
    class loginDlg: public Ui_loginDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDLG_H
