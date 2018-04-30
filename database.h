#ifndef _DATA_BASE_H_
#define _DATA_BASE_H_

#include <QString>
#include <QStringList>

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
struct  wire_data
{
    long id;
    QString tm;         //2时间
    QString deviceNo;   //3设备号
    int lineNo;         //4线路号
    float voltage;      //5电压
    float current;      //6电流
    float temperature;  //7温度
    float humidty;      //8湿度
};
struct B_Data
{
    float b1;             //1
    float b2;
    float temperature;
    float temperatureIn;
    float voltage;        //0x43
    float voltage2;
    float humidity;       //0x40
    float humidityIn;
    char package;
    QString deviceNo;
    QString tm;
    QString remark;
    long id;
    B_Data()
    {
        b1=0;             //1
        b2=0;
        temperature=0;
        temperatureIn=0;
        voltage=0;        //0x43
        voltage2=0;
        humidity=0;       //0x40
        humidityIn=0;
        package=0;
    }
};
struct current_Data
{
    long id;            //1
    QString tm;         //2
    QString deviceNo;   //3
    float t1;           //4
    float h1;           //5
    float v1;           //6
    float current;      //7
    float t2;           //8
    float h2;           //9
    float tmp1;         //10
    float tmp2;         //11
    QString remark;     //12
    char package;
};
struct device_management
{
    int id;
    QString local;
    QString remark;
    QString curDeviceID;
};
enum DETECT_TYPE
{
    WIRE_TYPE=1,
    B_TYPE=2,
    DEVICE_INFO=3,
    CURRENT_TYPE=5,
    NO_TYPE=4
};
class MeasureDB
{
public:
    MeasureDB(const QString& dbName,QSqlDatabase &mysql);
    ~MeasureDB();
    bool createTable(void);
    void Transaction(void);
    void Commit(void);
    QSqlDatabase currDatabase(void);
    QString curDataName;
    void isOpenDB(void);
    void isCloseDB(void);
    static QString local_wireDetailName;//本地数据库详细数据表格tbTableInfo
    static QString local_wireDetailTitle;
    static QString local_wireDetailField;

    static QString local_bDetailName;
    static QString local_bDetailTitle;
    static QString local_bDetailField;


    static QString local_currentDetailName;
    static QString local_currentDetailTitle;
    static QString local_currentDetailField;


    static QString local_deviceInfoName;//本地数据库设备信息表格
    static QString local_deviceInfoTitle;
    static QString local_deviceInfoField;
    static QString local_deviceInfoFilter;

    static QString local_devcieManagementName;
    static QString local_devcieManagementField;
    static QPair<QStringList,QStringList> local_curManagementDevices;//用户管理表格中的local和curDeviceID顺次对应存入该对象

    static QString mysql_wireDetailTable;
    static QString mysql_bDetailTable;
    static QString mysql_currentTable;
    static QString mysql_deviceManagementTb;
    static QString mysqlDeviceInfoTb;

    static DETECT_TYPE curDetect;
    int curManagementIndex;
    bool insert_wireDetailRecord(wire_data &record);
    bool insert_bDetailRecord(B_Data &record);
    bool insert_managementRecord(device_management &record);
    //    bool insert_deviceInfoRecord(deviceInfo &record);
    bool updateDeviceInfo(void);
    bool updateUserManagement(void );
    long recordCount(DETECT_TYPE f);
    void deleteAllData(void);
    void readConfig(void);
    void updateBDetailRecord(long localCount);
    void updateWireDetailRecord(long localCount);
    void updateCurrentDetailRecord(long localCount);
    bool insert_currentDetailRecord(current_Data &record);
private:

    QSqlDatabase m_db;
    QSqlDatabase m_mysql;
};

#endif


