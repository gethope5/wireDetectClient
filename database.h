#ifndef _DATA_BASE_H_
#define _DATA_BASE_H_

#include <QString>
#include <QStringList>

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
struct  detailRecord
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
enum DETECT_TYPE
{
    WIRE_TYPE=1,
    B_TYPE=2,
    DEVICE_INFO=3,
    NO_TYPE=4
};
class MeasureDB
{
public:
    MeasureDB(const QString& dbName);
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

    static QString local_deviceInfoName;//本地数据库设备信息表格
    static QString local_deviceInfoTitle;
    static QString local_deviceInfoField;
    static QString local_deviceInfoFilter;



    static QString mysql_wireDetailTable;
    static QString mysql_bDetailTable;

    static QString mysqlDeviceInfoTb;
    static QString curDepartment;//本地数据库详细数据表格tbTableInfo
    static DETECT_TYPE curDetect;
    bool insert_wireDetailRecord(detailRecord &record);
    bool insert_bDetailRecord(B_Data &record);

    //    bool insert_deviceInfoRecord(deviceInfo &record);
    bool updateDeviceInfo(QSqlDatabase mm);
    long recordCount(DETECT_TYPE f=WIRE_TYPE);
    QPair<QString,DETECT_TYPE> initialType;
private:

    QSqlDatabase m_db;
    void readConfig(void);
};

#endif


