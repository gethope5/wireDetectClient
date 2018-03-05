/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QAction *deviceManager;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QCheckBox *dataPic;
    QPushButton *pushButton_refresh;
    QCheckBox *checkBox_2;
    QCheckBox *overflow;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ip;
    QCheckBox *devieceStaturs;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *port;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *detailLable;
    QDateEdit *detailDate;
    QPushButton *pushButton;
    QLabel *label_hint;
    QTableView *detailTableView;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_overflow;
    QTableView *overData;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QTableView *tbTableInfo;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *no;
    QLabel *label_7;
    QDateEdit *dateEdit;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QCustomPlot *dataWidget;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1466, 842);
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(14);
        Widget->setFont(font);
        Widget->setStyleSheet(QLatin1String("QTableView {\n"
"      selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5,\n"
"                                  stop: 0 #0092BB, stop: 1 \n"
"#0000BB);\n"
"  }"));
        deviceManager = new QAction(Widget);
        deviceManager->setObjectName(QStringLiteral("deviceManager"));
        verticalLayout_6 = new QVBoxLayout(Widget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        dataPic = new QCheckBox(Widget);
        dataPic->setObjectName(QStringLiteral("dataPic"));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        dataPic->setFont(font1);
        dataPic->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(dataPic, 2, 2, 1, 1);

        pushButton_refresh = new QPushButton(Widget);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_refresh->setFont(font2);
        pushButton_refresh->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(pushButton_refresh, 2, 3, 1, 1);

        checkBox_2 = new QCheckBox(Widget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setFont(font1);
        checkBox_2->setLayoutDirection(Qt::LeftToRight);
        checkBox_2->setAutoFillBackground(false);
        checkBox_2->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(checkBox_2, 0, 1, 1, 1);

        overflow = new QCheckBox(Widget);
        overflow->setObjectName(QStringLiteral("overflow"));
        overflow->setFont(font1);
        overflow->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(overflow, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);

        horizontalLayout->addWidget(label);

        ip = new QLineEdit(Widget);
        ip->setObjectName(QStringLiteral("ip"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ip->sizePolicy().hasHeightForWidth());
        ip->setSizePolicy(sizePolicy);
        ip->setMinimumSize(QSize(130, 0));
        ip->setMaximumSize(QSize(130, 16777215));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        ip->setFont(font4);
        ip->setStyleSheet(QStringLiteral("background-color: rgb(213, 255, 239);"));

        horizontalLayout->addWidget(ip);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        devieceStaturs = new QCheckBox(Widget);
        devieceStaturs->setObjectName(QStringLiteral("devieceStaturs"));
        devieceStaturs->setFont(font1);
        devieceStaturs->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        gridLayout->addWidget(devieceStaturs, 2, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font3);

        horizontalLayout_2->addWidget(label_2);

        port = new QLineEdit(Widget);
        port->setObjectName(QStringLiteral("port"));
        sizePolicy.setHeightForWidth(port->sizePolicy().hasHeightForWidth());
        port->setSizePolicy(sizePolicy);
        port->setMinimumSize(QSize(130, 0));
        port->setMaximumSize(QSize(130, 16777215));
        port->setFont(font4);
        port->setStyleSheet(QStringLiteral("background-color: rgb(213, 255, 239);"));

        horizontalLayout_2->addWidget(port);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 30));
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));
        pushButton_2->setFlat(false);

        gridLayout->addWidget(pushButton_2, 0, 3, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        QFont font5;
        font5.setPointSize(30);
        font5.setBold(true);
        font5.setItalic(true);
        font5.setUnderline(false);
        font5.setWeight(75);
        label_3->setFont(font5);
        label_3->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(label_3);


        verticalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalSpacer = new QSpacerItem(13, 628, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_8->addItem(verticalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        detailLable = new QLabel(Widget);
        detailLable->setObjectName(QStringLiteral("detailLable"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font6.setPointSize(16);
        font6.setBold(true);
        font6.setWeight(75);
        detailLable->setFont(font6);
        detailLable->setStyleSheet(QStringLiteral(""));
        detailLable->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(detailLable);

        detailDate = new QDateEdit(Widget);
        detailDate->setObjectName(QStringLiteral("detailDate"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(detailDate->sizePolicy().hasHeightForWidth());
        detailDate->setSizePolicy(sizePolicy2);
        QFont font7;
        font7.setPointSize(14);
        detailDate->setFont(font7);
        detailDate->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));
        detailDate->setCurrentSection(QDateTimeEdit::YearSection);
        detailDate->setCalendarPopup(true);

        horizontalLayout_4->addWidget(detailDate);

        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy3);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        horizontalLayout_4->addWidget(pushButton);

        label_hint = new QLabel(Widget);
        label_hint->setObjectName(QStringLiteral("label_hint"));
        label_hint->setMinimumSize(QSize(20, 0));
        label_hint->setFont(font2);
        label_hint->setScaledContents(false);

        horizontalLayout_4->addWidget(label_hint);


        verticalLayout->addLayout(horizontalLayout_4);

        detailTableView = new QTableView(Widget);
        detailTableView->setObjectName(QStringLiteral("detailTableView"));
        detailTableView->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(129, 131, 21, 255), stop:0.463277 rgba(129, 170, 80, 255), stop:1 rgba(255, 255, 255, 255));"));
        detailTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        detailTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        detailTableView->setGridStyle(Qt::DashLine);
        detailTableView->setSortingEnabled(false);

        verticalLayout->addWidget(detailTableView);


        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_overflow = new QLabel(Widget);
        label_overflow->setObjectName(QStringLiteral("label_overflow"));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font8.setPointSize(14);
        font8.setBold(true);
        font8.setWeight(75);
        label_overflow->setFont(font8);
        label_overflow->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        label_overflow->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_overflow);

        overData = new QTableView(Widget);
        overData->setObjectName(QStringLiteral("overData"));
        overData->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(129, 131, 21, 255), stop:0.463277 rgba(129, 170, 80, 255), stop:1 rgba(255, 255, 255, 255));"));
        overData->setSortingEnabled(true);

        verticalLayout_2->addWidget(overData);


        horizontalLayout_7->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout_7);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_8 = new QLabel(Widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font8);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_8);

        tbTableInfo = new QTableView(Widget);
        tbTableInfo->setObjectName(QStringLiteral("tbTableInfo"));
        tbTableInfo->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(129, 131, 21, 255), stop:0.463277 rgba(129, 170, 80, 255), stop:1 rgba(255, 255, 255, 255));"));
        tbTableInfo->setSortingEnabled(true);

        verticalLayout_3->addWidget(tbTableInfo);


        verticalLayout_5->addLayout(verticalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);
        label_6->setFont(font2);

        horizontalLayout_5->addWidget(label_6);

        no = new QLineEdit(Widget);
        no->setObjectName(QStringLiteral("no"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(no->sizePolicy().hasHeightForWidth());
        no->setSizePolicy(sizePolicy5);
        no->setMaximumSize(QSize(100, 16777215));
        QFont font9;
        font9.setPointSize(15);
        no->setFont(font9);
        no->setStyleSheet(QStringLiteral("background-color: rgb(213, 255, 239);"));

        horizontalLayout_5->addWidget(no);

        label_7 = new QLabel(Widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy4.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy4);
        label_7->setFont(font2);

        horizontalLayout_5->addWidget(label_7);

        dateEdit = new QDateEdit(Widget);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setFont(font7);
        dateEdit->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));
        dateEdit->setAlignment(Qt::AlignCenter);
        dateEdit->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dateEdit->setCalendarPopup(true);

        horizontalLayout_5->addWidget(dateEdit);

        ok = new QPushButton(Widget);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setFont(font2);
        ok->setStyleSheet(QStringLiteral("background-image: url(:/images/images/lableBk.png);"));

        horizontalLayout_5->addWidget(ok);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label1 = new QLabel(Widget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setFont(font2);
        label1->setStyleSheet(QStringLiteral("background-color: rgb(0, 125, 125);"));

        verticalLayout_4->addWidget(label1);

        label2 = new QLabel(Widget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setFont(font2);
        label2->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 255);"));

        verticalLayout_4->addWidget(label2);

        label3 = new QLabel(Widget);
        label3->setObjectName(QStringLiteral("label3"));
        label3->setFont(font2);
        label3->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 0);"));

        verticalLayout_4->addWidget(label3);

        label4 = new QLabel(Widget);
        label4->setObjectName(QStringLiteral("label4"));
        label4->setFont(font2);
        label4->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 255);"));

        verticalLayout_4->addWidget(label4);

        label5 = new QLabel(Widget);
        label5->setObjectName(QStringLiteral("label5"));
        label5->setFont(font2);
        label5->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 255);"));

        verticalLayout_4->addWidget(label5);

        label6 = new QLabel(Widget);
        label6->setObjectName(QStringLiteral("label6"));
        label6->setFont(font2);
        label6->setStyleSheet(QStringLiteral("background-color: rgb(255, 125, 0);"));

        verticalLayout_4->addWidget(label6);


        horizontalLayout_6->addLayout(verticalLayout_4);

        dataWidget = new QCustomPlot(Widget);
        dataWidget->setObjectName(QStringLiteral("dataWidget"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(2);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(dataWidget->sizePolicy().hasHeightForWidth());
        dataWidget->setSizePolicy(sizePolicy6);
        dataWidget->setMinimumSize(QSize(0, 250));

        horizontalLayout_6->addWidget(dataWidget);


        verticalLayout_5->addLayout(horizontalLayout_6);


        horizontalLayout_8->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_8);


        retranslateUi(Widget);

        pushButton_2->setDefault(false);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\351\253\230\345\216\213\347\272\277\350\267\257\345\234\250\347\272\277\346\243\200\346\265\213\346\231\272\350\203\275\351\242\204\350\255\246\347\263\273\347\273\237", 0));
        deviceManager->setText(QApplication::translate("Widget", "\350\256\276\345\244\207\347\256\241\347\220\206", 0));
#ifndef QT_NO_TOOLTIP
        deviceManager->setToolTip(QApplication::translate("Widget", "\347\256\241\347\220\206\346\216\247\345\210\266\347\233\270\345\205\263\347\232\204\350\256\276\345\244\207", 0));
#endif // QT_NO_TOOLTIP
        dataPic->setText(QApplication::translate("Widget", "\346\225\260\346\215\256\346\233\262\347\272\277\345\233\276", 0));
        pushButton_refresh->setText(QApplication::translate("Widget", "\345\210\267\346\226\260\346\225\260\346\215\256", 0));
        checkBox_2->setText(QApplication::translate("Widget", "\350\257\246\347\273\206\346\225\260\346\215\256", 0));
        overflow->setText(QApplication::translate("Widget", "\350\266\205\351\231\220\346\225\260\346\215\256", 0));
        label->setText(QApplication::translate("Widget", "IP\345\234\260\345\235\200", 0));
        devieceStaturs->setText(QApplication::translate("Widget", "\350\256\276\345\244\207\347\212\266\346\200\201", 0));
        label_2->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_2->setToolTip(QApplication::translate("Widget", "\347\202\271\345\207\273\344\273\245\350\277\233\350\241\214\350\256\276\345\244\207\346\267\273\345\212\240\345\210\240\351\231\244\347\255\211", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_2->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_2->setText(QApplication::translate("Widget", "\350\256\276\345\244\207\347\256\241\347\220\206", 0));
        label_3->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" color:#0000ff;\">\345\233\233\345\267\235\344\277\241\350\276\276\350\275\250\351\201\223\344\272\244\351\200\232\350\256\276\345\244\207\346\234\211\351\231\220\350\264\243\344\273\273\345\205\254\345\217\270</span></p></body></html>", 0));
        detailLable->setText(QApplication::translate("Widget", "\347\224\265\347\274\206\345\261\217\351\207\207\351\233\206\347\232\204\350\257\246\347\273\206\346\225\260\346\215\256", 0));
        detailDate->setDisplayFormat(QApplication::translate("Widget", "yyyy/MM/dd", 0));
        pushButton->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", 0));
        label_hint->setText(QString());
        label_overflow->setText(QApplication::translate("Widget", "\350\266\205\351\231\220\346\225\260\346\215\256", 0));
        label_8->setText(QApplication::translate("Widget", "\350\256\276\345\244\207\344\277\241\346\201\257", 0));
        label_6->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\350\256\276\345\244\207", 0));
        label_7->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\227\266\351\227\264", 0));
        ok->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", 0));
        label1->setText(QApplication::translate("Widget", "\347\272\277\350\267\2571", 0));
        label2->setText(QApplication::translate("Widget", "\347\272\277\350\267\2572", 0));
        label3->setText(QApplication::translate("Widget", "\347\272\277\350\267\2573", 0));
        label4->setText(QApplication::translate("Widget", "\347\272\277\350\267\2574", 0));
        label5->setText(QApplication::translate("Widget", "\347\272\277\350\267\2575", 0));
        label6->setText(QApplication::translate("Widget", "\347\272\277\350\267\2576", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
