/********************************************************************************
** Form generated from reading UI file 'cdevicemanager.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDEVICEMANAGER_H
#define UI_CDEVICEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDeviceManager
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_13;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QLineEdit *devieceOwner;
    QPushButton *AddDeviece;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_2;
    QLineEdit *devieceNo_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QLineEdit *deviecePosition;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QDateTimeEdit *dateTimeEdit;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QTableView *linesAliase;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *devieceNo;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *savePower;
    QPushButton *runFast;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QSpinBox *tm;
    QPushButton *setTimeEescap;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *newNo;
    QPushButton *setNewNo;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *warningVal;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpinBox *lineNo;
    QPushButton *setWarningVal;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QSpinBox *errVal;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QSpinBox *errNo;
    QPushButton *setErrVal;
    QPushButton *setAllToZero;
    QVBoxLayout *verticalLayout_9;
    QSpinBox *zeroLineNo;
    QPushButton *setLineZero;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *CDeviceManager)
    {
        if (CDeviceManager->objectName().isEmpty())
            CDeviceManager->setObjectName(QStringLiteral("CDeviceManager"));
        CDeviceManager->resize(500, 755);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CDeviceManager->sizePolicy().hasHeightForWidth());
        CDeviceManager->setSizePolicy(sizePolicy);
        CDeviceManager->setMinimumSize(QSize(500, 600));
        CDeviceManager->setMaximumSize(QSize(500, 1000));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        CDeviceManager->setFont(font);
        CDeviceManager->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(CDeviceManager);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_5->setFont(font1);

        horizontalLayout_10->addWidget(label_5);

        devieceOwner = new QLineEdit(groupBox_3);
        devieceOwner->setObjectName(QStringLiteral("devieceOwner"));
        QFont font2;
        font2.setPointSize(12);
        devieceOwner->setFont(font2);

        horizontalLayout_10->addWidget(devieceOwner);


        gridLayout->addLayout(horizontalLayout_10, 1, 0, 1, 1);

        AddDeviece = new QPushButton(groupBox_3);
        AddDeviece->setObjectName(QStringLiteral("AddDeviece"));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        AddDeviece->setFont(font3);
        AddDeviece->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        gridLayout->addWidget(AddDeviece, 4, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        horizontalLayout_9->addWidget(label_2);

        devieceNo_2 = new QLineEdit(groupBox_3);
        devieceNo_2->setObjectName(QStringLiteral("devieceNo_2"));
        devieceNo_2->setFont(font2);

        horizontalLayout_9->addWidget(devieceNo_2);


        gridLayout->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        horizontalLayout_11->addWidget(label_7);

        deviecePosition = new QLineEdit(groupBox_3);
        deviecePosition->setObjectName(QStringLiteral("deviecePosition"));
        deviecePosition->setFont(font2);

        horizontalLayout_11->addWidget(deviecePosition);


        gridLayout->addLayout(horizontalLayout_11, 2, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font2);

        horizontalLayout_12->addWidget(label_10);

        dateTimeEdit = new QDateTimeEdit(groupBox_3);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setFont(font2);
        dateTimeEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        dateTimeEdit->setCalendarPopup(true);

        horizontalLayout_12->addWidget(dateTimeEdit, 0, Qt::AlignHCenter);


        gridLayout->addLayout(horizontalLayout_12, 3, 0, 1, 1);


        horizontalLayout_13->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font4;
        font4.setPointSize(13);
        label_6->setFont(font4);

        verticalLayout_2->addWidget(label_6);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setFont(font2);

        verticalLayout_2->addWidget(lineEdit);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFont(font3);
        pushButton_2->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout_2->addWidget(pushButton_2);


        horizontalLayout_13->addWidget(groupBox_2);


        verticalLayout_4->addLayout(horizontalLayout_13);

        linesAliase = new QTableView(centralwidget);
        linesAliase->setObjectName(QStringLiteral("linesAliase"));
        linesAliase->setFont(font2);
        linesAliase->setSortingEnabled(true);

        verticalLayout_4->addWidget(linesAliase);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font3);
        pushButton->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout_4->addWidget(pushButton);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font2);
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        horizontalLayout_3->addWidget(label);

        devieceNo = new QLineEdit(groupBox);
        devieceNo->setObjectName(QStringLiteral("devieceNo"));

        horizontalLayout_3->addWidget(devieceNo);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        savePower = new QPushButton(groupBox);
        savePower->setObjectName(QStringLiteral("savePower"));
        savePower->setFont(font1);
        savePower->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        horizontalLayout_4->addWidget(savePower);

        runFast = new QPushButton(groupBox);
        runFast->setObjectName(QStringLiteral("runFast"));
        runFast->setFont(font1);
        runFast->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        horizontalLayout_4->addWidget(runFast);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tm = new QSpinBox(groupBox);
        tm->setObjectName(QStringLiteral("tm"));

        verticalLayout->addWidget(tm);

        setTimeEescap = new QPushButton(groupBox);
        setTimeEescap->setObjectName(QStringLiteral("setTimeEescap"));
        setTimeEescap->setFont(font1);
        setTimeEescap->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout->addWidget(setTimeEescap);


        horizontalLayout_8->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        newNo = new QSpinBox(groupBox);
        newNo->setObjectName(QStringLiteral("newNo"));

        verticalLayout_3->addWidget(newNo);

        setNewNo = new QPushButton(groupBox);
        setNewNo->setObjectName(QStringLiteral("setNewNo"));
        setNewNo->setFont(font1);
        setNewNo->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout_3->addWidget(setNewNo);


        horizontalLayout_8->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        horizontalLayout->addWidget(label_3);

        warningVal = new QSpinBox(groupBox);
        warningVal->setObjectName(QStringLiteral("warningVal"));

        horizontalLayout->addWidget(warningVal);


        verticalLayout_6->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        horizontalLayout_2->addWidget(label_4);

        lineNo = new QSpinBox(groupBox);
        lineNo->setObjectName(QStringLiteral("lineNo"));

        horizontalLayout_2->addWidget(lineNo);


        verticalLayout_6->addLayout(horizontalLayout_2);

        setWarningVal = new QPushButton(groupBox);
        setWarningVal->setObjectName(QStringLiteral("setWarningVal"));
        setWarningVal->setFont(font1);
        setWarningVal->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout_6->addWidget(setWarningVal);


        horizontalLayout_7->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font1);

        horizontalLayout_5->addWidget(label_8);

        errVal = new QSpinBox(groupBox);
        errVal->setObjectName(QStringLiteral("errVal"));

        horizontalLayout_5->addWidget(errVal);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font1);

        horizontalLayout_6->addWidget(label_9);

        errNo = new QSpinBox(groupBox);
        errNo->setObjectName(QStringLiteral("errNo"));

        horizontalLayout_6->addWidget(errNo);


        verticalLayout_7->addLayout(horizontalLayout_6);

        setErrVal = new QPushButton(groupBox);
        setErrVal->setObjectName(QStringLiteral("setErrVal"));
        setErrVal->setFont(font1);
        setErrVal->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout_7->addWidget(setErrVal);


        horizontalLayout_7->addLayout(verticalLayout_7);


        verticalLayout_5->addLayout(horizontalLayout_7);

        setAllToZero = new QPushButton(groupBox);
        setAllToZero->setObjectName(QStringLiteral("setAllToZero"));
        setAllToZero->setFont(font1);
        setAllToZero->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout_5->addWidget(setAllToZero);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        zeroLineNo = new QSpinBox(groupBox);
        zeroLineNo->setObjectName(QStringLiteral("zeroLineNo"));

        verticalLayout_9->addWidget(zeroLineNo);

        setLineZero = new QPushButton(groupBox);
        setLineZero->setObjectName(QStringLiteral("setLineZero"));
        setLineZero->setFont(font1);
        setLineZero->setStyleSheet(QStringLiteral("background-image: url(:/images/images/fuck.jpg);"));

        verticalLayout_9->addWidget(setLineZero);


        verticalLayout_5->addLayout(verticalLayout_9);


        verticalLayout_4->addWidget(groupBox);

        CDeviceManager->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(CDeviceManager);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CDeviceManager->setStatusBar(statusbar);
        menubar = new QMenuBar(CDeviceManager);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 23));
        CDeviceManager->setMenuBar(menubar);

        retranslateUi(CDeviceManager);

        QMetaObject::connectSlotsByName(CDeviceManager);
    } // setupUi

    void retranslateUi(QMainWindow *CDeviceManager)
    {
        CDeviceManager->setWindowTitle(QApplication::translate("CDeviceManager", "\350\256\276\345\244\207\347\256\241\347\220\206\345\231\250", 0));
        groupBox_3->setTitle(QString());
        label_5->setText(QApplication::translate("CDeviceManager", "\346\211\200\345\261\236\350\267\257\345\261\200", 0));
#ifndef QT_NO_TOOLTIP
        AddDeviece->setToolTip(QApplication::translate("CDeviceManager", "\350\257\267\345\234\250\344\270\212\346\226\271\350\276\223\345\205\245\350\256\276\345\244\207\347\233\270\345\205\263\344\277\241\346\201\257\345\220\216\347\202\271\345\207\273", 0));
#endif // QT_NO_TOOLTIP
        AddDeviece->setText(QApplication::translate("CDeviceManager", "\346\267\273\345\212\240\350\256\276\345\244\207", 0));
        label_2->setText(QApplication::translate("CDeviceManager", "\350\256\276\345\244\207\347\274\226\345\217\267", 0));
        label_7->setText(QApplication::translate("CDeviceManager", "\345\256\211\350\243\205\344\275\215\347\275\256", 0));
        label_10->setText(QApplication::translate("CDeviceManager", "\345\256\211\350\243\205\346\227\266\351\227\264", 0));
        groupBox_2->setTitle(QString());
        label_6->setText(QApplication::translate("CDeviceManager", "\351\234\200\350\246\201\345\210\240\351\231\244\347\232\204\350\256\276\345\244\207\347\232\204\347\274\226\345\217\267\357\274\232", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_2->setToolTip(QApplication::translate("CDeviceManager", "<html><head/><body><p>\345\234\250\344\270\212\346\226\271\350\241\250\346\240\274\344\270\255\351\200\211\346\213\251\350\256\276\345\244\207\346\211\200\345\234\250\350\241\214\347\202\271\345\207\273\345\215\263\345\217\257</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButton_2->setText(QApplication::translate("CDeviceManager", "\345\210\240\351\231\244\350\256\276\345\244\207", 0));
        pushButton->setText(QApplication::translate("CDeviceManager", "\345\210\267\346\226\260", 0));
        groupBox->setTitle(QApplication::translate("CDeviceManager", "\346\216\247\345\210\266\350\256\276\345\244\207", 0));
        label->setText(QApplication::translate("CDeviceManager", "\350\256\276\345\244\207\347\274\226\345\217\267", 0));
        savePower->setText(QApplication::translate("CDeviceManager", "\345\205\250\351\200\237\350\277\220\350\241\214", 0));
        runFast->setText(QApplication::translate("CDeviceManager", "\350\277\233\345\205\245\347\234\201\347\224\265\346\250\241\345\274\217", 0));
        setTimeEescap->setText(QApplication::translate("CDeviceManager", "\350\256\276\347\275\256\346\243\200\346\265\213\346\227\266\351\227\264\351\227\264\351\232\224", 0));
        setNewNo->setText(QApplication::translate("CDeviceManager", "\350\256\276\347\275\256\350\256\276\345\244\207\346\226\260\347\274\226\345\217\267", 0));
        label_3->setText(QApplication::translate("CDeviceManager", "\347\224\265\346\265\201\351\242\204\350\255\246\345\200\274", 0));
        label_4->setText(QApplication::translate("CDeviceManager", "\347\272\277\350\267\257\347\274\226\345\217\267", 0));
        setWarningVal->setText(QApplication::translate("CDeviceManager", "\350\256\276\347\275\256\347\224\265\346\265\201\351\242\204\350\255\246\345\200\274", 0));
        label_8->setText(QApplication::translate("CDeviceManager", "\347\224\265\346\265\201\351\242\204\350\255\246\345\200\274", 0));
        label_9->setText(QApplication::translate("CDeviceManager", "\347\272\277\350\267\257\347\274\226\345\217\267", 0));
        setErrVal->setText(QApplication::translate("CDeviceManager", "\350\256\276\347\275\256\347\224\265\346\265\201\346\212\245\350\255\246\345\200\274", 0));
        setAllToZero->setText(QApplication::translate("CDeviceManager", "\347\272\277\350\267\257\347\224\265\346\265\201\351\233\266\347\202\271\346\240\241\345\207\206\350\256\276\347\275\256\345\221\275\344\273\244", 0));
        setLineZero->setText(QApplication::translate("CDeviceManager", "\347\272\277\350\267\257\347\224\265\346\265\201\346\240\241\345\207\206\345\221\275\344\273\244", 0));
    } // retranslateUi

};

namespace Ui {
    class CDeviceManager: public Ui_CDeviceManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDEVICEMANAGER_H
