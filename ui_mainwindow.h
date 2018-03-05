/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <multtablefrm.h>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *deviceManager;
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QPushButton *pbtnDetailUpdate;
    QLabel *label_18;
    QLineEdit *lnbOverCur;
    QLabel *label_19;
    QCheckBox *overflow;
    QPushButton *pbtnReshData;
    QCheckBox *dataPic;
    QCheckBox *devieceStaturs;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_15;
    QComboBox *cmbDeviceNo_2;
    QDateEdit *date;
    QLabel *label_17;
    QComboBox *cmbLine;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QGroupBox *gbDetail;
    QGridLayout *gridLayout_6;
    multTableFrm *tbDetail;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QTableView *tbOverData;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *line2;
    QLabel *label_11;
    QLineEdit *line3;
    QLabel *label_12;
    QLineEdit *line4;
    QLabel *label_13;
    QLineEdit *line5;
    QLabel *label_14;
    QLineEdit *line6;
    QPushButton *ptnbDeviceInfoUpdate;
    QTableView *tbTableInfo;
    QLabel *label_4;
    QLineEdit *lneDeviceNo;
    QLabel *label_16;
    QLineEdit *lneDeviceAbbr;
    QLabel *label_5;
    QLineEdit *lneDepartment;
    QLabel *label_8;
    QLineEdit *lnePosition;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_9;
    QLineEdit *line1;
    QLabel *label_10;
    QPushButton *ptnbDeviceAdd;
    QPushButton *ptnbDeviceDelete;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *gbCurve;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *cb1;
    QCheckBox *cb2;
    QCheckBox *cb3;
    QCheckBox *cb4;
    QCheckBox *cb5;
    QCheckBox *cb6;
    QCustomPlot *dataWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1466, 869);
        deviceManager = new QAction(MainWindow);
        deviceManager->setObjectName(QStringLiteral("deviceManager"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(300, 0));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pbtnDetailUpdate = new QPushButton(groupBox_3);
        pbtnDetailUpdate->setObjectName(QStringLiteral("pbtnDetailUpdate"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbtnDetailUpdate->sizePolicy().hasHeightForWidth());
        pbtnDetailUpdate->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pbtnDetailUpdate->setFont(font);
        pbtnDetailUpdate->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(pbtnDetailUpdate, 1, 15, 1, 1);

        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);
        label_18->setFont(font);

        gridLayout->addWidget(label_18, 1, 7, 1, 1);

        lnbOverCur = new QLineEdit(groupBox_3);
        lnbOverCur->setObjectName(QStringLiteral("lnbOverCur"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lnbOverCur->sizePolicy().hasHeightForWidth());
        lnbOverCur->setSizePolicy(sizePolicy2);
        lnbOverCur->setMinimumSize(QSize(30, 0));
        lnbOverCur->setMaximumSize(QSize(30, 16777215));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        lnbOverCur->setFont(font1);
        lnbOverCur->setStyleSheet(QStringLiteral("background-color: rgb(213, 255, 239);"));

        gridLayout->addWidget(lnbOverCur, 1, 8, 1, 1);

        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);
        label_19->setFont(font);

        gridLayout->addWidget(label_19, 1, 9, 1, 1);

        overflow = new QCheckBox(groupBox_3);
        overflow->setObjectName(QStringLiteral("overflow"));
        QFont font2;
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setWeight(75);
        overflow->setFont(font2);
        overflow->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(overflow, 0, 0, 1, 1);

        pbtnReshData = new QPushButton(groupBox_3);
        pbtnReshData->setObjectName(QStringLiteral("pbtnReshData"));
        pbtnReshData->setFont(font);
        pbtnReshData->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(pbtnReshData, 1, 1, 1, 1);

        dataPic = new QCheckBox(groupBox_3);
        dataPic->setObjectName(QStringLiteral("dataPic"));
        dataPic->setFont(font2);
        dataPic->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(dataPic, 1, 0, 1, 1);

        devieceStaturs = new QCheckBox(groupBox_3);
        devieceStaturs->setObjectName(QStringLiteral("devieceStaturs"));
        devieceStaturs->setFont(font2);
        devieceStaturs->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(devieceStaturs, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 14, 1, 1);

        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);
        label_15->setFont(font);

        gridLayout->addWidget(label_15, 1, 2, 1, 1);

        cmbDeviceNo_2 = new QComboBox(groupBox_3);
        cmbDeviceNo_2->setObjectName(QStringLiteral("cmbDeviceNo_2"));
        cmbDeviceNo_2->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(cmbDeviceNo_2, 1, 3, 1, 1);

        date = new QDateEdit(groupBox_3);
        date->setObjectName(QStringLiteral("date"));
        QFont font3;
        font3.setPointSize(14);
        date->setFont(font3);
        date->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));
        date->setAlignment(Qt::AlignCenter);
        date->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        date->setCalendarPopup(true);

        gridLayout->addWidget(date, 1, 13, 1, 1);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);
        label_17->setFont(font);

        gridLayout->addWidget(label_17, 1, 4, 1, 1);

        cmbLine = new QComboBox(groupBox_3);
        cmbLine->setObjectName(QStringLiteral("cmbLine"));
        cmbLine->setMinimumSize(QSize(100, 0));
        cmbLine->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(cmbLine, 1, 5, 1, 1);


        horizontalLayout_3->addWidget(groupBox_3);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gbDetail = new QGroupBox(centralwidget);
        gbDetail->setObjectName(QStringLiteral("gbDetail"));
        gbDetail->setMinimumSize(QSize(600, 0));
        gridLayout_6 = new QGridLayout(gbDetail);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        tbDetail = new multTableFrm(gbDetail);
        tbDetail->setObjectName(QStringLiteral("tbDetail"));

        gridLayout_6->addWidget(tbDetail, 0, 0, 1, 1);


        verticalLayout->addWidget(gbDetail);


        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 100));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tbOverData = new QTableView(groupBox_2);
        tbOverData->setObjectName(QStringLiteral("tbOverData"));
        tbOverData->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(129, 131, 21, 255), stop:0.463277 rgba(129, 170, 80, 255), stop:1 rgba(255, 255, 255, 255));"));
        tbOverData->setSortingEnabled(true);

        gridLayout_4->addWidget(tbOverData, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);


        horizontalLayout_7->addLayout(verticalLayout_2);


        gridLayout_5->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 250));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        line2 = new QLineEdit(groupBox);
        line2->setObjectName(QStringLiteral("line2"));

        gridLayout_2->addWidget(line2, 4, 4, 1, 3);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 4, 7, 1, 1);

        line3 = new QLineEdit(groupBox);
        line3->setObjectName(QStringLiteral("line3"));

        gridLayout_2->addWidget(line3, 4, 8, 1, 2);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 4, 10, 1, 1);

        line4 = new QLineEdit(groupBox);
        line4->setObjectName(QStringLiteral("line4"));

        gridLayout_2->addWidget(line4, 4, 11, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 4, 12, 1, 1);

        line5 = new QLineEdit(groupBox);
        line5->setObjectName(QStringLiteral("line5"));

        gridLayout_2->addWidget(line5, 4, 13, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 4, 14, 1, 1);

        line6 = new QLineEdit(groupBox);
        line6->setObjectName(QStringLiteral("line6"));

        gridLayout_2->addWidget(line6, 4, 15, 1, 2);

        ptnbDeviceInfoUpdate = new QPushButton(groupBox);
        ptnbDeviceInfoUpdate->setObjectName(QStringLiteral("ptnbDeviceInfoUpdate"));
        ptnbDeviceInfoUpdate->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(ptnbDeviceInfoUpdate, 2, 20, 1, 1);

        tbTableInfo = new QTableView(groupBox);
        tbTableInfo->setObjectName(QStringLiteral("tbTableInfo"));
        tbTableInfo->setMinimumSize(QSize(0, 0));
        tbTableInfo->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(129, 131, 21, 255), stop:0.463277 rgba(129, 170, 80, 255), stop:1 rgba(255, 255, 255, 255));"));
        tbTableInfo->setSortingEnabled(true);

        gridLayout_2->addWidget(tbTableInfo, 0, 0, 1, 22);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 2);

        lneDeviceNo = new QLineEdit(groupBox);
        lneDeviceNo->setObjectName(QStringLiteral("lneDeviceNo"));

        gridLayout_2->addWidget(lneDeviceNo, 2, 2, 1, 3);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_2->addWidget(label_16, 2, 5, 1, 1);

        lneDeviceAbbr = new QLineEdit(groupBox);
        lneDeviceAbbr->setObjectName(QStringLiteral("lneDeviceAbbr"));

        gridLayout_2->addWidget(lneDeviceAbbr, 2, 6, 1, 3);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 2, 9, 1, 1);

        lneDepartment = new QLineEdit(groupBox);
        lneDepartment->setObjectName(QStringLiteral("lneDepartment"));

        gridLayout_2->addWidget(lneDepartment, 2, 10, 1, 2);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 2, 13, 1, 1);

        lnePosition = new QLineEdit(groupBox);
        lnePosition->setObjectName(QStringLiteral("lnePosition"));

        gridLayout_2->addWidget(lnePosition, 2, 14, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(132, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 16, 1, 2);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 4, 0, 1, 1);

        line1 = new QLineEdit(groupBox);
        line1->setObjectName(QStringLiteral("line1"));

        gridLayout_2->addWidget(line1, 4, 1, 1, 2);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 4, 3, 1, 1);

        ptnbDeviceAdd = new QPushButton(groupBox);
        ptnbDeviceAdd->setObjectName(QStringLiteral("ptnbDeviceAdd"));
        ptnbDeviceAdd->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(ptnbDeviceAdd, 2, 18, 1, 1);

        ptnbDeviceDelete = new QPushButton(groupBox);
        ptnbDeviceDelete->setObjectName(QStringLiteral("ptnbDeviceDelete"));
        ptnbDeviceDelete->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(ptnbDeviceDelete, 2, 19, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(69, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 4, 17, 1, 4);


        verticalLayout_3->addWidget(groupBox);


        gridLayout_5->addLayout(verticalLayout_3, 2, 0, 1, 1);

        gbCurve = new QGroupBox(centralwidget);
        gbCurve->setObjectName(QStringLiteral("gbCurve"));
        gbCurve->setMinimumSize(QSize(0, 80));
        gridLayout_3 = new QGridLayout(gbCurve);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        cb1 = new QCheckBox(gbCurve);
        cb1->setObjectName(QStringLiteral("cb1"));
        cb1->setMinimumSize(QSize(0, 25));
        cb1->setStyleSheet(QStringLiteral("background-color: rgb(0, 125, 125);"));

        verticalLayout_4->addWidget(cb1);

        cb2 = new QCheckBox(gbCurve);
        cb2->setObjectName(QStringLiteral("cb2"));
        cb2->setMinimumSize(QSize(0, 25));
        cb2->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 255);"));

        verticalLayout_4->addWidget(cb2);

        cb3 = new QCheckBox(gbCurve);
        cb3->setObjectName(QStringLiteral("cb3"));
        cb3->setMinimumSize(QSize(0, 25));
        cb3->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 0);"));

        verticalLayout_4->addWidget(cb3);

        cb4 = new QCheckBox(gbCurve);
        cb4->setObjectName(QStringLiteral("cb4"));
        cb4->setMinimumSize(QSize(0, 25));
        cb4->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 255);"));

        verticalLayout_4->addWidget(cb4);

        cb5 = new QCheckBox(gbCurve);
        cb5->setObjectName(QStringLiteral("cb5"));
        cb5->setMinimumSize(QSize(0, 25));
        cb5->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 255);"));

        verticalLayout_4->addWidget(cb5);

        cb6 = new QCheckBox(gbCurve);
        cb6->setObjectName(QStringLiteral("cb6"));
        cb6->setMinimumSize(QSize(0, 25));
        cb6->setStyleSheet(QStringLiteral("background-color: rgb(255, 125, 0);"));

        verticalLayout_4->addWidget(cb6);


        gridLayout_3->addLayout(verticalLayout_4, 0, 0, 1, 1);

        dataWidget = new QCustomPlot(gbCurve);
        dataWidget->setObjectName(QStringLiteral("dataWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dataWidget->sizePolicy().hasHeightForWidth());
        dataWidget->setSizePolicy(sizePolicy3);
        dataWidget->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(dataWidget, 0, 1, 1, 1);


        gridLayout_5->addWidget(gbCurve, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1466, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        deviceManager->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\347\256\241\347\220\206", 0));
#ifndef QT_NO_TOOLTIP
        deviceManager->setToolTip(QApplication::translate("MainWindow", "\347\256\241\347\220\206\346\216\247\345\210\266\347\233\270\345\205\263\347\232\204\350\256\276\345\244\207", 0));
#endif // QT_NO_TOOLTIP
        groupBox_3->setTitle(QString());
        pbtnDetailUpdate->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0));
        label_18->setText(QApplication::translate("MainWindow", "\350\266\205\351\231\220\346\240\207\345\207\206", 0));
        label_19->setText(QApplication::translate("MainWindow", "A", 0));
        overflow->setText(QApplication::translate("MainWindow", "\350\266\205\351\231\220\346\225\260\346\215\256", 0));
        pbtnReshData->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260\346\225\260\346\215\256", 0));
        dataPic->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\233\262\347\272\277\345\233\276", 0));
        devieceStaturs->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\347\212\266\346\200\201", 0));
        label_15->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\256\276\345\244\207", 0));
        label_17->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\257", 0));
        gbDetail->setTitle(QApplication::translate("MainWindow", "\351\207\207\351\233\206\346\225\260\346\215\256", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\350\266\205\351\231\220\346\225\260\346\215\256", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\350\256\276\345\244\207\344\277\241\346\201\257", 0));
        label_11->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2573", 0));
        label_12->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2574", 0));
        label_13->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2575", 0));
        label_14->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2576", 0));
        ptnbDeviceInfoUpdate->setText(QApplication::translate("MainWindow", "\346\233\264\346\226\260", 0));
        label_4->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\347\274\226\345\217\267", 0));
        label_16->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\347\256\200\347\247\260", 0));
        label_5->setText(QApplication::translate("MainWindow", "\346\211\200\345\261\236\350\267\257\345\261\200", 0));
        label_8->setText(QApplication::translate("MainWindow", "\345\256\211\350\243\205\344\275\215\347\275\256", 0));
        label_9->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2571", 0));
        label_10->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2572", 0));
        ptnbDeviceAdd->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240", 0));
        ptnbDeviceDelete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", 0));
        gbCurve->setTitle(QApplication::translate("MainWindow", "\346\243\200\346\265\213\346\233\262\347\272\277", 0));
        cb1->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2571", 0));
        cb2->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2572", 0));
        cb3->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2573", 0));
        cb4->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2574", 0));
        cb5->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2575", 0));
        cb6->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2576", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
