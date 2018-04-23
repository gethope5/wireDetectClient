/*
 * operator here for database
*/

#include <QtSql>
#include "database.h"



/*another database class */
QString MeasureDB::mysql_wireDetailTable=QString("wireDetectCd");
QString MeasureDB::mysqlDeviceInfoTb=QString("deviceInfo");
QString MeasureDB::mysql_bDetailTable=QString("bDetectKm");


QString MeasureDB::local_wireDetailName=QString("wireDetect");
QString MeasureDB::local_wireDetailTitle=QString::fromWCharArray(L"ID0,时间1,设备号1,线路号1,电压1,电流1,温度1,湿度1");
QString MeasureDB::local_wireDetailField=QString::fromWCharArray(L"id,tm,deviceNo,lineNo,voltage,current,temperature,humidity");

QString MeasureDB::local_bDetailName=QString::fromWCharArray(L"bDetect");
QString MeasureDB::local_bDetailTitle=QString::fromWCharArray(L"ID0,时间1,设备号1,导B(mm)1,承B(mm)1,环境温度(°C)0,湿度(%)1,设备电压(V)1,集中器电压(V)0,环境湿度(%)0,温度(°C)1,备注1");
QString MeasureDB::local_bDetailField=QString::fromWCharArray(L"id,tm,deviceNo,b1,b2,temperature,temperatureIn,voltage,voltage2,humidity,humidityIn,remark");


QString MeasureDB::local_deviceInfoName=QString("deviceInfoCd");
// 1    2       3         4          5             6         7         8     9     10    11    12    13    14
//"ID,deviceNO,deviceType,department,tableName,localPosition,installTm,line1,line2,line3,line4,line5,line6,remark"
//1
//                                                            1 2        3          4          5             6         7     8     9     10    11    12
QString MeasureDB::local_deviceInfoField=QString::fromWCharArray(L"ID,deviceNO,deviceType,department,localPosition,installTm,line1,line2,line3,line4,line5,line6");
//                                                           1  2       3   4       5      6       7    8    9    10    11   12
QString MeasureDB::local_deviceInfoTitle=QString::fromWCharArray(L"ID0,设备编号1,类型1,所属路局1,安装位置1,安装时间1,线路10,线路20,线路30,线路40,线路50,线路60");
QString MeasureDB::local_deviceInfoFilter="deviceNO in('0400020002')";
QString MeasureDB::curDepartment=QString::fromWCharArray(L"昆明供电段");//本地数据库详细数据表格tbTableInfo
DETECT_TYPE MeasureDB::curDetect=WIRE_TYPE;
MeasureDB::MeasureDB(const QString& dbName)
{
    QSqlError err;
    initialType= QPair<QString,DETECT_TYPE>("",NO_TYPE);
    readConfig();
    m_db = QSqlDatabase::addDatabase("QSQLITE", "mdb_connection");
    m_db.setDatabaseName(dbName);
    //    m_db.set
    if (!m_db.open())
    {
        qDebug()<<"can not open db..........";
        err = m_db.lastError();
        m_db = QSqlDatabase();
    }
    else
    {
        qDebug()<<"measure db is opened,create table status="<<createTable();
    }
    curDataName=dbName;
}
void MeasureDB::readConfig(void)
{
    QSettings  settings("Config.ini", QSettings::IniFormat);

    QString tmp=settings.value("par/devices","").toString();
    QString tmpDepartment=settings.value("par/local","").toString();

    if(!tmp.isNull())
    {
        tmp.replace('/',',');
        local_deviceInfoFilter=QString("deviceNO in(%1)").arg(tmp);
    }
    if(!tmpDepartment.isNull())
    {
        initialType.first=QString::fromWCharArray(L"电缆在线监测系统");
        if(tmpDepartment.contains("kunming"))
        {
            curDepartment=QString::fromWCharArray(L"昆明供电段");
            initialType.first= QString::fromWCharArray(L"B值");
            initialType.second=B_TYPE;
        }
        else if(tmpDepartment.contains("chengdu"))
        {
            curDepartment=QString::fromWCharArray(L"成都供电段");
            mysql_wireDetailTable="wireDetectCd";
            initialType.second=WIRE_TYPE;
        }
        else if(tmpDepartment.contains("qingdao"))
        {
            curDepartment=QString::fromWCharArray(L"青岛供电段");
            mysql_wireDetailTable="wireDetectQd";
            initialType.second=WIRE_TYPE;
        }
        else if(tmpDepartment.contains("dalian"))
        {
            curDepartment=QString::fromWCharArray(L"大连供电段");
            mysql_wireDetailTable="detailinfo0514";
            initialType.second=WIRE_TYPE;
        }
    }
    qDebug()<<"cur device filter="<<local_deviceInfoFilter<<curDepartment<<tmp<<"dd"<<tmpDepartment;
}
void MeasureDB::isOpenDB(void)
{
    if(!m_db.isOpen())
        m_db.open();
}
void MeasureDB::isCloseDB(void)
{
    Commit();
    m_db.close();
}

bool MeasureDB::createTable(void)
{    
    isOpenDB();
    QSqlQuery query(m_db);
    //"ID,deviceNO,deviceType,department,tableName,localPosition,installTm,line1,line2,line3,line4,line5,line6,remark"

    QString strWireSql=QString("CREATE TABLE %1(id long UNIQUE ,tm varchar(30),deviceNo varchar(30),lineNo int,voltage float,current float, temperature float, humidity float)").arg(local_wireDetailName);
    QString strDeviceInfoSql=QString("CREATE TABLE %1"\
                                     "(ID integer UNIQUE,deviceNO varchar(30),"\
                                     "deviceType varchar(30),department varchar(30),"\
                                     "tableName varchar(30),localPosition varchar(30),"\
                                     "installTm varchar(30),line1 varchar(30),line2 varchar(30),line3 varchar(30),"\
                                     "line4 varchar(30),line5 varchar(30),line6 varchar(30),"
                                     "remark varchar(30))").arg(local_deviceInfoName);
    QString strBSql=QString("CREATE TABLE %1"\
                            "(id integer UNIQUE,tm varchar(30),deviceNO varchar(30),"\
                            "b1 float,b2 float,"\
                            "temperature float,temperatureIn float,"\
                            "voltage float,voltage2 float,humidity float,humidityIn float,"\
                            "remark varchar(30))").arg(local_bDetailName);

    bool b1=query.exec(strWireSql);
    bool b2=query.exec(strDeviceInfoSql);
    bool b3=query.exec(strBSql);
    //    qDebug()<<"sql str2="<<str2;
    //    isCloseDB();
    //    qDebug()<<"create detail"<<b1<<"create devcie "<<b2<<"devcie sql="<<str2;
    return b1&b2&b3;
}
void MeasureDB::Transaction(void)
{
    if(m_db.isOpen())
        m_db.transaction();
}
void MeasureDB::Commit(void)
{
    if(m_db.isOpen())
        m_db.commit();
}
MeasureDB::~MeasureDB()
{
    if(m_db.isOpen())
        m_db.close();
    if(m_db.isOpen())
    {
        qDebug()<<"~~~~"<<m_db.connectionName();
        QSqlDatabase::removeDatabase(m_db.connectionName());
    }
}
QSqlDatabase MeasureDB::currDatabase(void)
{
    return m_db;
}
bool MeasureDB::insert_wireDetailRecord(detailRecord &record)
{
    QSqlQuery query(m_db);
    QString strSql=QString("insert into %1(id,tm,deviceNo,lineNo,voltage,current,temperature,humidity) values(%2,'%3','%4',%5,%6,%7,%8,%9)").arg(local_wireDetailName)
            .arg(record.id)
            .arg(record.tm)
            .arg(record.deviceNo)
            .arg(record.lineNo)
            .arg(record.voltage)
            .arg(record.current)
            .arg(record.temperature)
            .arg(record.humidty);
    //    qDebug()<<"data"<<strSql;
    return query.exec(strSql);
}
bool MeasureDB::insert_bDetailRecord(B_Data &curBValue)
{
    QSqlQuery query(m_db);
    bool bFlag=false;
    QString strSql=QString("insert into %11 (tm,deviceNo,b1,b2,temperature,temperatureIn,voltage,voltage2,humidity,humidityIn,remark,id) "\
                           "values (\'%12\',\'%1\',%2,%3,%4,%5,%6,%7,%8,%9,\'%10\',%13)")
            .arg(curBValue.deviceNo).arg(curBValue.b1).arg(curBValue.b2).arg(curBValue.temperature).arg(curBValue.temperatureIn)
            .arg(curBValue.voltage).arg(curBValue.voltage2).arg(curBValue.humidity).arg(curBValue.humidityIn).arg("")
            .arg(local_bDetailName).arg(curBValue.tm).arg(curBValue.id);
    bFlag=query.exec(strSql);
    //    qDebug()<<"insert data"<<strSql<<bFlag;

    return query.exec(strSql);
}
//函数功能：获取本地数据库的记录数，true,获取详细数据的记录数;false,获取设备数据的记录数
long MeasureDB::recordCount(DETECT_TYPE flag)
{
    QSqlQuery query(m_db);
    QString strSql;
    if(flag==WIRE_TYPE)
    {
        strSql=QString("select count(*) from %1").arg(local_wireDetailName);
    }
    else if(flag==B_TYPE)
    {
        strSql=QString("select count(*) from %1").arg(local_bDetailName);
    }
    else if(flag==DEVICE_INFO)
    {
        strSql=QString("select count(*) from %1").arg(local_deviceInfoName);
    }
    if(query.exec(strSql))
    {
        long count=0;
        while(query.next())
        {
            count=query.value(0).toLongLong();
        }
        return count;
    }
    else
        return 0;
}
//函数功能：将远程数据库中的设备信息同步至本地数据库中的设备信息表格，通过ID号是否一致判别是否更新
bool MeasureDB::updateDeviceInfo(QSqlDatabase mysql_db)
{
    if(!mysql_db.isOpen())
        return false;
    QSqlQuery query(m_db);
    QSqlQuery query1(mysql_db);
    QString strMysql=QString("select ID,deviceNO,deviceType,department,tableName,"\
                             "localPosition,installTm,line1,line2,line3,line4,"\
                             "line5,line6,remark from %1").arg(mysqlDeviceInfoTb);
    //    qDebug()<<"mysql sql"<<strMysql;
    if(query1.exec(strMysql))
    {
        while(query1.next())
        {
            QString tmp="";
            for(int i=1;i<14;i++)
            {
                tmp+=QString("\'%1\',").arg(query1.value(i).toString());
            }
            tmp=tmp.left(tmp.count()-1);
            QString strInsertSql=QString("insert into %1(ID,deviceNO,deviceType,department,tableName,"\
                                         "localPosition,installTm,line1,line2,line3,line4,line5,line6,remark"\
                                         ") values(%2,%3)").arg(local_deviceInfoName).arg(query1.value(0).toString()).arg(tmp);

            //              qDebug()<<"insert sql"<<strInsertSql<<
            query.exec(strInsertSql);
        }
        return true;
    }
    else
    {
        qDebug()<<"get mysql db is error";
        return false;
    }
}
