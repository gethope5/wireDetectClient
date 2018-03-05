#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QDateTime>
#include <QSqlDatabase>
#include "cdevicemanager.h"
#include <QPair>
#include <QtSql>
#include <QVector>
#include <QSqlTableModel>
#include "raillinesqlmodel.h"
#include "widget.h"
#include <QTableView>
#include "logindlg.h"
#include <QTime>
#include "devicestatus.h"
#include "database.h"
#define CURVE_NUMBERS 6
struct curveInfo
{
    int curveIndex;
    QVector<double> x;
    QVector<double> y;
    QColor color;
    curveInfo():curveIndex(-1)
    {
        x.clear();
        y.clear();
        color=Qt::red;
    }
    void clear(void)
    {
        x.clear();
        y.clear();
    }
};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    void SetBack();
    void uiInitial(void);
    void curveInitial(void);
    RailLineSqlModel *deviceInfoModel;
    RailLineSqlModel *detectDataModel;
    RailLineSqlModel *overDataModel;
    void showDeviceStatus(  QString  tableName);
    void showDetailData(RailLineSqlModel *model,QTableView *tableview,QString filter,bool f=true,QString  tableName=MeasureDB::detailDataTb,QString title=MeasureDB::detectDataTitle);
    void closeEvent(QCloseEvent *event);
    //私有成员函数
    void DrawCurve();
    void connect2MysqlDb();
    void ShowOverData();//显示超限数据
    void ShowStaturs();
    void UpdataStatursDB(CCommand cmd);

    //私有成员变量
    QVector<QColor> color;
    QSqlDatabase db_mysql;
    CDeviceManager* manager;
    int nIndex;
    QStringList getALLDeviceNo(void);
    QTimer *timer;
    void updateDeviceNo(void);
    QVector<QPair<QString,QString> > deviceNos;//<设备简称,设备编号>
    QVector<QPair<int,QVector<QString> > > lineNos;
    void updateLineNo(QString strDevice);
    curveInfo curveInfos[CURVE_NUMBERS];
    void readConfigure(void);
    void setConfigure(void);
    MeasureDB *localDb;
    long mysql_recordCount(bool);
    bool mysql_addDeviceNo(void);
    bool mysql_updateDeviceNo(bool);
    bool mysql_deleteDeviceNo(void);

    void updateDatabase(bool);
    DeviceStatus *remoteDbStatus;
    QLabel *lblLocalRecordCounts;
    int updateInterval;
private slots:
    void slot_updateData(void);
    void ShowDB(bool f=true);
    void MouseWheel();//鼠标滚轮在曲线图上滚动
    void DeleteDeviece(qint16 no);
    void AddDeviece(qint16,QString,QString,QDateTime);
    void SendData(qint16 no,QByteArray cmd);

    void slot_lineCurve(void);

    void on_devieceStaturs_clicked(bool checked);

    void on_overflow_clicked(bool checked);

    void on_dataPic_clicked(bool checked);
//    void on_ok_clicked();
    void on_pbtnDetailUpdate_clicked();
    void slot_deviceStautsControl();
    void on_tbTableInfo_clicked(const QModelIndex &index);
    void on_cmbDeviceNo_2_activated(const QString &arg1);
    void on_pbtnReshData_clicked();
};

#endif // MAINWINDOW_H
