/*
 * operator here for database
*/

#include <QtSql>
#include "database.h"



/*another database class */
QString MeasureDB::detailDataTb=QString("debugMeasure");
QString MeasureDB::mysqlDetailDataTb=QString("detailinfo0514");
QString MeasureDB::mysqlDeviceInfoTb=QString("deviecestaturs0514");


QString MeasureDB::deviceInfoTb=QString("deviecestaturs0514");
QString MeasureDB::detailDataTitle=QString::fromWCharArray(L"ID1,时间1,设备号1,线路号1,电压1,电流1,温度1,湿度1");
QString MeasureDB::overDataTitle=QString::fromWCharArray(L"ID1,时间1,里程(m)1,公里标(Km)1,站区1,杆号1,轨距0,超高0,拉出值1,导高1,拉出值10,导高10");
QString MeasureDB::detectDataTitle=QString::fromWCharArray(L"ID0,时间1,设备编号1,线路名1,电压(V)1,电流(A)1,温度1,湿度1");
QString MeasureDB::deviceInfoTitle=QString::fromWCharArray(L"ID0,设备编号1,设备线路1,所属路局1,安装位置1,安装时间0,添加时间0,线路11,线路21,线路31,线路41,线路51,线路61,电池电量0,温度0,湿度0,更新时间0");
MeasureDB::MeasureDB(const QString& dbName)
{
    QSqlError err;
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
    QString str1=QString("CREATE TABLE %1(id long UNIQUE ,tm varchar(30),deviceNo varchar(30),lineNo int,voltage float,current float, temperature float, humidity float)").arg(detailDataTb);
    QString str2=QString("CREATE TABLE %1(ID integer,deviceNo varchar(30),deviceAddr varchar(30),department varchar(30),position varchar(30),installTm varchar(30),addTm varchar(30),line1 varchar(30),line2 varchar(30),line3 varchar(30),line4 varchar(30),line5 varchar(30),line6 varchar(30),remainCell int,temperature float,humidity float,recentTmUpdate varchar(30))").arg(deviceInfoTb);

//    qDebug()<<"sql str2="<<str2;
    //    isCloseDB();
    return query.exec(str1)&query.exec(str2);
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
bool MeasureDB::insert_detailRecord(detailRecord &record)
{
    QSqlQuery query(m_db);
    QString strSql=QString("insert into %1(id,tm,deviceNo,lineNo,voltage,current,temperature,humidity) values(%2,'%3','%4',%5,%6,%7,%8,%9)").arg(detailDataTb)
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
//函数功能：获取本地数据库的记录数，true,获取详细数据的记录数;false,获取设备数据的记录数
long MeasureDB::recordCount(bool flag)
{
    QSqlQuery query(m_db);
    QString strSql;
    if(flag)
    {
        strSql=QString("select count(*) from %1").arg(detailDataTb);
    }
    else
    {
        strSql=QString("select count(*) from %1").arg(deviceInfoTb);
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
bool MeasureDB::insert_deviceInfoRecord(deviceInfo &record)
{
    QSqlQuery query(m_db);
#if 1
    QString strSql=QString("insert into %1(id,deviceNo,deviceAddr,department,position,line1,line2,line3,line4,line5,line6) values(%2,'%3','%4','%5','%6','%7','%8','%9','%10','%11','%12')")
            .arg(deviceInfoTb)
            .arg(record.id)
            .arg(record.deviceNo)
            .arg(record.deviceAddr)
            .arg(record.department)
            .arg(record.position)
            .arg(record.line1)
            .arg(record.line2)
            .arg(record.line3)
            .arg(record.line4)
            .arg(record.line5)
            .arg(record.line6);
#else
    QString strSql=QString("insert into %1(id,deviceNo,line1,line2,line3,line4,line5,line6,deviceAddr) values(%2,'%3','%4','%5','%6','%7','%8','%9','%10')")
            .arg(deviceInfoTb)
            .arg(record.id)
            .arg(record.deviceNo)
            .arg(record.line1)
            .arg(record.line2)
            .arg(record.line3)
            .arg(record.line4)
            .arg(record.line5)
            .arg(record.line6)
            .arg(record.deviceAddr);
#endif
//    qDebug()<<"insert device info,sql str="<<strSql;
    return query.exec(strSql);
}
