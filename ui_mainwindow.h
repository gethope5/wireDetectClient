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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <hoverbitmapbtn.h>
#include <multtablefrm.h>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *deviceManager;
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pbtnExit;
    QPushButton *pbtnMin;
    QWidget *widget_3;
    QLineEdit *lnbOverValue;
    QLabel *label_15;
    QComboBox *cmbDeviceType;
    QLabel *lblOver;
    QLabel *lblOverUnit;
    QWidget *widget;
    QGridLayout *gridLayout_7;
    HoverBitmapBtn *pbtnClear;
    HoverBitmapBtn *pbtnUpdate;
    HoverBitmapBtn *pbtnDataFilter;
    QWidget *widget_4;
    QDateEdit *endDate;
    QLabel *label_20;
    QLabel *lblEndDate;
    QDateEdit *startDate;
    QTabWidget *tabWidget;
    QWidget *tabTable;
    QGridLayout *gridLayout_2;
    multTableFrm *wdgTable;
    QWidget *tabOver;
    QGridLayout *gridLayout_4;
    multTableFrm *wdgOver;
    QWidget *tabDevice;
    QGridLayout *gridLayout_5;
    QTableView *tbTableInfo;
    QWidget *tabCurve;
    QGridLayout *gridLayout_3;
    QCustomPlot *dataWidget;
    QGroupBox *groupBox;
    QCheckBox *cb2;
    QCheckBox *cb5;
    QCheckBox *cb3;
    QCheckBox *cb1;
    QCheckBox *cb4;
    QCheckBox *cb6;
    QLabel *label_16;
    QComboBox *cmbDeviceNo;
    QLabel *label_17;
    HoverBitmapBtn *pbtnCurve;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1850, 869);
        deviceManager = new QAction(MainWindow);
        deviceManager->setObjectName(QStringLiteral("deviceManager"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(300, 0));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_2 = new QWidget(groupBox_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 100));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(0, 85, 127);"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 50, 531, 51));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 750 16pt  \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 10, 461, 51));
        label_2->setStyleSheet(QString::fromUtf8("color:rgb(0, 255, 0);\n"
"font: 750 24pt  \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        pbtnExit = new QPushButton(widget_2);
        pbtnExit->setObjectName(QStringLiteral("pbtnExit"));
        pbtnExit->setGeometry(QRect(1680, 10, 80, 80));
        pbtnExit->setMinimumSize(QSize(80, 80));
        pbtnMin = new QPushButton(widget_2);
        pbtnMin->setObjectName(QStringLiteral("pbtnMin"));
        pbtnMin->setGeometry(QRect(1580, 10, 80, 80));
        pbtnMin->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(widget_2, 0, 0, 1, 2);

        widget_3 = new QWidget(groupBox_3);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(650, 0));
        widget_3->setMaximumSize(QSize(16777215, 30));
        lnbOverValue = new QLineEdit(widget_3);
        lnbOverValue->setObjectName(QStringLiteral("lnbOverValue"));
        lnbOverValue->setGeometry(QRect(450, 10, 50, 20));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lnbOverValue->sizePolicy().hasHeightForWidth());
        lnbOverValue->setSizePolicy(sizePolicy);
        lnbOverValue->setMinimumSize(QSize(50, 0));
        lnbOverValue->setMaximumSize(QSize(50, 16777215));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        lnbOverValue->setFont(font);
        lnbOverValue->setStyleSheet(QStringLiteral("background-color: rgb(213, 255, 239);"));
        label_15 = new QLabel(widget_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(12, 9, 80, 19));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_15->setFont(font1);
        cmbDeviceType = new QComboBox(widget_3);
        cmbDeviceType->setObjectName(QStringLiteral("cmbDeviceType"));
        cmbDeviceType->setGeometry(QRect(98, 10, 180, 20));
        cmbDeviceType->setMinimumSize(QSize(180, 0));
        cmbDeviceType->setMaximumSize(QSize(180, 16777215));
        lblOver = new QLabel(widget_3);
        lblOver->setObjectName(QStringLiteral("lblOver"));
        lblOver->setGeometry(QRect(284, 9, 160, 23));
        sizePolicy1.setHeightForWidth(lblOver->sizePolicy().hasHeightForWidth());
        lblOver->setSizePolicy(sizePolicy1);
        lblOver->setMinimumSize(QSize(160, 23));
        lblOver->setMaximumSize(QSize(160, 23));
        lblOver->setFont(font1);
        lblOverUnit = new QLabel(widget_3);
        lblOverUnit->setObjectName(QStringLiteral("lblOverUnit"));
        lblOverUnit->setGeometry(QRect(510, 10, 25, 19));
        sizePolicy1.setHeightForWidth(lblOverUnit->sizePolicy().hasHeightForWidth());
        lblOverUnit->setSizePolicy(sizePolicy1);
        lblOverUnit->setMinimumSize(QSize(25, 0));
        lblOverUnit->setFont(font1);

        gridLayout->addWidget(widget_3, 1, 0, 1, 1);

        widget = new QWidget(groupBox_3);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(120, 0));
        gridLayout_7 = new QGridLayout(widget);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        pbtnClear = new HoverBitmapBtn(widget);
        pbtnClear->setObjectName(QStringLiteral("pbtnClear"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pbtnClear->sizePolicy().hasHeightForWidth());
        pbtnClear->setSizePolicy(sizePolicy2);
        pbtnClear->setMinimumSize(QSize(100, 40));
        pbtnClear->setMaximumSize(QSize(75, 16777215));
        pbtnClear->setFont(font1);
        pbtnClear->setStyleSheet(QStringLiteral(""));

        gridLayout_7->addWidget(pbtnClear, 3, 0, 1, 1);

        pbtnUpdate = new HoverBitmapBtn(widget);
        pbtnUpdate->setObjectName(QStringLiteral("pbtnUpdate"));
        sizePolicy2.setHeightForWidth(pbtnUpdate->sizePolicy().hasHeightForWidth());
        pbtnUpdate->setSizePolicy(sizePolicy2);
        pbtnUpdate->setMinimumSize(QSize(100, 40));
        pbtnUpdate->setMaximumSize(QSize(75, 16777215));
        pbtnUpdate->setFont(font1);
        pbtnUpdate->setStyleSheet(QStringLiteral(""));

        gridLayout_7->addWidget(pbtnUpdate, 1, 0, 1, 1);

        pbtnDataFilter = new HoverBitmapBtn(widget);
        pbtnDataFilter->setObjectName(QStringLiteral("pbtnDataFilter"));
        sizePolicy2.setHeightForWidth(pbtnDataFilter->sizePolicy().hasHeightForWidth());
        pbtnDataFilter->setSizePolicy(sizePolicy2);
        pbtnDataFilter->setMinimumSize(QSize(100, 40));
        pbtnDataFilter->setMaximumSize(QSize(75, 16777215));
        pbtnDataFilter->setFont(font1);
        pbtnDataFilter->setStyleSheet(QStringLiteral(""));

        gridLayout_7->addWidget(pbtnDataFilter, 2, 0, 1, 1);


        gridLayout->addWidget(widget, 1, 1, 2, 1);

        widget_4 = new QWidget(groupBox_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(650, 0));
        widget_4->setMaximumSize(QSize(16777215, 30));
        endDate = new QDateEdit(widget_4);
        endDate->setObjectName(QStringLiteral("endDate"));
        endDate->setGeometry(QRect(450, 0, 160, 23));
        endDate->setMinimumSize(QSize(160, 0));
        endDate->setMaximumSize(QSize(160, 16777215));
        QFont font2;
        font2.setPointSize(14);
        endDate->setFont(font2);
        endDate->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));
        endDate->setAlignment(Qt::AlignCenter);
        endDate->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        endDate->setCalendarPopup(true);
        label_20 = new QLabel(widget_4);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(12, 0, 80, 19));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);
        label_20->setFont(font1);
        lblEndDate = new QLabel(widget_4);
        lblEndDate->setObjectName(QStringLiteral("lblEndDate"));
        lblEndDate->setGeometry(QRect(284, 0, 160, 19));
        sizePolicy1.setHeightForWidth(lblEndDate->sizePolicy().hasHeightForWidth());
        lblEndDate->setSizePolicy(sizePolicy1);
        lblEndDate->setMinimumSize(QSize(160, 0));
        lblEndDate->setMaximumSize(QSize(160, 16777215));
        lblEndDate->setFont(font1);
        startDate = new QDateEdit(widget_4);
        startDate->setObjectName(QStringLiteral("startDate"));
        startDate->setGeometry(QRect(98, 0, 180, 23));
        startDate->setMinimumSize(QSize(180, 0));
        startDate->setMaximumSize(QSize(180, 16777215));
        startDate->setFont(font2);
        startDate->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));
        startDate->setAlignment(Qt::AlignCenter);
        startDate->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        startDate->setCalendarPopup(true);

        gridLayout->addWidget(widget_4, 2, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabTable = new QWidget();
        tabTable->setObjectName(QStringLiteral("tabTable"));
        gridLayout_2 = new QGridLayout(tabTable);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        wdgTable = new multTableFrm(tabTable);
        wdgTable->setObjectName(QStringLiteral("wdgTable"));

        gridLayout_2->addWidget(wdgTable, 0, 0, 1, 1);

        tabWidget->addTab(tabTable, QString());
        tabOver = new QWidget();
        tabOver->setObjectName(QStringLiteral("tabOver"));
        gridLayout_4 = new QGridLayout(tabOver);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        wdgOver = new multTableFrm(tabOver);
        wdgOver->setObjectName(QStringLiteral("wdgOver"));

        gridLayout_4->addWidget(wdgOver, 0, 0, 1, 1);

        tabWidget->addTab(tabOver, QString());
        tabDevice = new QWidget();
        tabDevice->setObjectName(QStringLiteral("tabDevice"));
        gridLayout_5 = new QGridLayout(tabDevice);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tbTableInfo = new QTableView(tabDevice);
        tbTableInfo->setObjectName(QStringLiteral("tbTableInfo"));
        tbTableInfo->setMinimumSize(QSize(0, 0));
        tbTableInfo->setStyleSheet(QStringLiteral(""));
        tbTableInfo->setSortingEnabled(true);

        gridLayout_5->addWidget(tbTableInfo, 0, 0, 1, 1);

        tabWidget->addTab(tabDevice, QString());
        tabCurve = new QWidget();
        tabCurve->setObjectName(QStringLiteral("tabCurve"));
        gridLayout_3 = new QGridLayout(tabCurve);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        dataWidget = new QCustomPlot(tabCurve);
        dataWidget->setObjectName(QStringLiteral("dataWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dataWidget->sizePolicy().hasHeightForWidth());
        dataWidget->setSizePolicy(sizePolicy3);
        dataWidget->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(dataWidget, 0, 0, 1, 1);

        groupBox = new QGroupBox(tabCurve);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(120, 0));
        groupBox->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
"color: rgb(255, 255, 255);\n"
"	font:750, 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        cb2 = new QCheckBox(groupBox);
        cb2->setObjectName(QStringLiteral("cb2"));
        cb2->setGeometry(QRect(20, 100, 80, 40));
        cb2->setMinimumSize(QSize(80, 40));
        cb2->setMaximumSize(QSize(80, 40));
        cb2->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 255);"));
        cb5 = new QCheckBox(groupBox);
        cb5->setObjectName(QStringLiteral("cb5"));
        cb5->setGeometry(QRect(20, 250, 80, 40));
        cb5->setMinimumSize(QSize(80, 40));
        cb5->setMaximumSize(QSize(80, 40));
        cb5->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 255);"));
        cb3 = new QCheckBox(groupBox);
        cb3->setObjectName(QStringLiteral("cb3"));
        cb3->setGeometry(QRect(20, 150, 80, 40));
        cb3->setMinimumSize(QSize(80, 40));
        cb3->setMaximumSize(QSize(80, 40));
        cb3->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 0);"));
        cb1 = new QCheckBox(groupBox);
        cb1->setObjectName(QStringLiteral("cb1"));
        cb1->setGeometry(QRect(20, 50, 80, 40));
        cb1->setMinimumSize(QSize(80, 40));
        cb1->setMaximumSize(QSize(80, 40));
        cb1->setStyleSheet(QLatin1String("background-color: rgb(0, 125, 125);\n"
""));
        cb4 = new QCheckBox(groupBox);
        cb4->setObjectName(QStringLiteral("cb4"));
        cb4->setGeometry(QRect(20, 200, 80, 40));
        cb4->setMinimumSize(QSize(80, 40));
        cb4->setMaximumSize(QSize(80, 40));
        cb4->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 255);"));
        cb6 = new QCheckBox(groupBox);
        cb6->setObjectName(QStringLiteral("cb6"));
        cb6->setGeometry(QRect(20, 300, 80, 40));
        cb6->setMinimumSize(QSize(80, 40));
        cb6->setMaximumSize(QSize(80, 40));
        cb6->setStyleSheet(QStringLiteral("background-color: rgb(255, 125, 0);"));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 370, 80, 22));
        sizePolicy1.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy1);
        label_16->setFont(font1);
        cmbDeviceNo = new QComboBox(groupBox);
        cmbDeviceNo->setObjectName(QStringLiteral("cmbDeviceNo"));
        cmbDeviceNo->setGeometry(QRect(10, 400, 100, 20));
        cmbDeviceNo->setMinimumSize(QSize(100, 0));
        cmbDeviceNo->setMaximumSize(QSize(60, 16777215));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 20, 80, 22));
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);
        label_17->setFont(font1);
        pbtnCurve = new HoverBitmapBtn(groupBox);
        pbtnCurve->setObjectName(QStringLiteral("pbtnCurve"));
        pbtnCurve->setGeometry(QRect(10, 440, 100, 40));
        pbtnCurve->setMinimumSize(QSize(100, 40));

        gridLayout_3->addWidget(groupBox, 0, 1, 1, 1);

        tabWidget->addTab(tabCurve, QString());

        gridLayout_6->addWidget(tabWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


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
        label->setText(QApplication::translate("MainWindow", "\345\233\233\345\267\235\344\277\241\350\276\276\350\275\250\351\201\223\344\272\244\351\200\232\350\256\276\345\244\207\346\234\211\351\231\220\350\264\243\344\273\273\345\205\254\345\217\270", 0));
        label_2->setText(QApplication::translate("MainWindow", "\351\253\230\351\200\237\351\223\201\350\267\257\344\276\233\347\224\265\345\256\211\345\205\250\347\233\221\346\265\213\347\263\273\347\273\237-C6", 0));
        pbtnExit->setText(QApplication::translate("MainWindow", "PushButton", 0));
        pbtnMin->setText(QApplication::translate("MainWindow", "PushButton", 0));
        label_15->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\347\261\273\345\236\213", 0));
        lblOver->setText(QApplication::translate("MainWindow", "\350\266\205\351\231\220\346\240\207\345\207\206", 0));
        lblOverUnit->setText(QApplication::translate("MainWindow", "A", 0));
        pbtnClear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\346\225\260\346\215\256", 0));
        pbtnUpdate->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", 0));
        pbtnDataFilter->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", 0));
        label_20->setText(QApplication::translate("MainWindow", "\350\265\267\345\247\213\346\227\266\351\227\264", 0));
        lblEndDate->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\346\227\266\351\227\264", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabTable), QApplication::translate("MainWindow", "\351\207\207\351\233\206\346\225\260\346\215\256", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabOver), QApplication::translate("MainWindow", "\350\266\205\351\231\220\346\225\260\346\215\256", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabDevice), QApplication::translate("MainWindow", "\350\256\276\345\244\207\344\277\241\346\201\257", 0));
        groupBox->setTitle(QString());
        cb2->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2572", 0));
        cb5->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2575", 0));
        cb3->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2573", 0));
        cb1->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2571", 0));
        cb4->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2574", 0));
        cb6->setText(QApplication::translate("MainWindow", "\347\272\277\350\267\2576", 0));
        label_16->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\344\275\215\347\275\256", 0));
        label_17->setText(QApplication::translate("MainWindow", "\346\233\262\347\272\277\346\230\276\347\244\272", 0));
        pbtnCurve->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabCurve), QApplication::translate("MainWindow", "\346\243\200\346\265\213\346\233\262\347\272\277", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
