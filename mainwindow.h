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
#include "widget.h"
#include <QTableView>
#include "logindlg.h"
#include <QTime>
#include "devicestatus.h"
#include "database.h"
#define pbtn_width 80
#define pbtn_height 80
#define CURVE_NUMBERS 6
#define B_CURVE_NUMBERS 2
#define debug_UI 0
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
    void showTable(QTableView *tableview,QString filter);
    void closeEvent(QCloseEvent *event);
    //私有成员函数
    void DrawCurve();
    void connect2MysqlDb();
    void UpdataStatursDB(CCommand cmd);

    //私有成员变量
    QVector<QColor> color;
    QSqlDatabase db_mysql;
    CDeviceManager* manager;
    int nIndex;
    QTimer *timer;
    void updateDeviceType(void);
    QVector<QPair<int,QVector<QString> > > lineNos;
    curveInfo curveInfos[CURVE_NUMBERS];
    curveInfo curveBTemperture;
    void readConfigure(void);
    void setConfigure(void);
    MeasureDB *localDb;
    long mysql_recordCount(DETECT_TYPE f=WIRE_TYPE);
    long updateDatabase(DETECT_TYPE=WIRE_TYPE);
    DeviceStatus *remoteDbStatus;
    QLabel *lblLocalRecordCounts;
    int updateInterval;
    void initialViewDb(void);
    QPushButton *pbtnOver;//超限
    QPushButton *pbtnTable;//表格
    QPushButton *pbtnDevice;//设备信息
    QPushButton *pbtnCurveUI;//曲线
    QPushButton *pbtnUpdate;//刷新
    QPushButton *pbtnExit;//刷新
    void updateDeviceLocal(void);
    QString getDeviceNO(QString localPosition);
    void curveSim(void);
    void drawLine(curveInfo curveData);
    void updateWireDetailRecord(long localCount);
    void updateBDetailRecord(long localCount);
    void setUI(QString arg1);
    QPair<QString,DETECT_TYPE> curType;
    QPair<QString,QString> getShowTableInfo(QString field,QString title);
    QString getStrFilter(void);
    void updateAllTable(void);
    void resizeEvent(QResizeEvent *);
private slots:
    void slot_updateData(void);
    void MouseWheel();//鼠标滚轮在曲线图上滚动
    void DeleteDeviece(qint16 no);
    void SendData(qint16 no,QByteArray cmd);

    void slot_lineCurve(void);
    void on_pbtnDataFilter_clicked();
    void on_cmbDeviceType_activated(const QString &arg1);
    void toolPbtnProcessing(void);
    void on_pbtnCurve_clicked();
    void on_pbtnUpdate_clicked();
    void on_pbtnExit_clicked();
    void on_pbtnMin_clicked();
};

#endif // MAINWINDOW_H
