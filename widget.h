#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QDateTime>
#include <QSqlDatabase>
#include "cdevicemanager.h"
#include <QPair>
#include <QVector>
#include <QSqlTableModel>
#include <QtGui>
#include <QDateTime>
#include "database.h"
class QDatabase;
class QTableWidget;
#include "raillinesqlmodel.h"
//新的数据格式
struct wireCmdPackage
{
    qint8 start;
    qint32 relayNo;
    qint8 length;   //数据长度
    qint8 key;      //特征码
    qint8 type;     //装置类型
    qint16 no;      //设备序号
    qint16 cv;      //温度或电压
    qint16 hi;      //湿度或电流
    qint8 cks;      //校验和
    qint16 enter;//处理多余的回车换行
};


struct CCommand
{
    qint8 length;
    qint8 key;
    qint8 type;
    qint16 no;
    qint16 cv;//温度或电压
    qint16 hi;//湿度或电流
    qint8 cks;//校验和
    qint16 enter;//处理多余的回车换行
    QDateTime tm;//时间
    qint8 lineNo;//线路编号
};

class QTcpServer;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    
    void SetBack();
    void paintEvent(QPaintEvent *);
    void uiInitial(void);
    void curveInitial(void);
private slots:
    void ShowDB();
    void MouseWheel();//鼠标滚轮在曲线图上滚动
    void DeleteDeviece(qint16 no);
    void AddDeviece(qint16,QString,QString,QDateTime);
    void SendData(qint16 no,QByteArray cmd);
    void ReadData();
    void AcceptConnect();


    void on_pushButton_2_clicked();
#if EXPAND
    void on_start_clicked(bool checked);
    void on_exportData_clicked();
#endif
    void on_checkBox_2_clicked(bool checked);

    void on_devieceStaturs_clicked(bool checked);

    void on_overflow_clicked(bool checked);

    void on_dataPic_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_ok_clicked();

    void on_pushButton_refresh_clicked();


    void on_pushButton_clicked();

    void on_dataPic_clicked();
private:
    RailLineSqlModel *model;
    void showTables(  QString  tableName);
    void closeEvent(QCloseEvent *event);
    QString xlsTitleName;
    //私有成员函数
    void DrawCurve();
    void ConnectDB();
    bool InsertDB();
    void ShowOverData();//显示超限数据
    void ShowStaturs();
    void UpdataStatursDB(CCommand cmd);

    //私有成员变量
    QVector<QColor> color;
    qint16 overEelectric;
    CCommand cmd;//当前收到的命令
    QSqlDatabase db;
    CDeviceManager* manager;
    qint16 errCount;//错误的包的数量
    qint16 pakageCount;//包的总数量
    void ShowCommand(CCommand cmd);
    void FillTable(CCommand cmd,QTableWidget *table);
    QTcpServer *tcpServer;
    Ui::Widget *ui;
};

#endif // WIDGET_H
