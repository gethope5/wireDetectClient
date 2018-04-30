/*
 * operator here for database
*/

#include <QtSql>
#include "database.h"



/*another database class */
QString MeasureDB::mysql_wireDetailTable=QString("wireDetectCd");
QString MeasureDB::mysqlDeviceInfoTb=QString("deviceInfo");
QString MeasureDB::mysql_bDetailTable=QString("bDetectKm");
QString MeasureDB::mysql_currentTable=QString("currentDetectDl");
QString MeasureDB::mysql_deviceManagementTb=QString("userManagement");


QString MeasureDB::local_wireDetailName=QString("wireDetect");
QString MeasureDB::local_wireDetailTitle=QString::fromWCharArray(L"ID0,时间1,设备号1,线路号1,电压1,电流1,温度1,湿度1");
QString MeasureDB::local_wireDetailField=QString::fromWCharArray(L"id,tm,deviceNo,lineNo,voltage,current,temperature,humidity");

QString MeasureDB::local_bDetailName=QString::fromWCharArray(L"bDetect");
QString MeasureDB::local_bDetailTitle=QString::fromWCharArray(L"ID0,时间1,设备号1,导B(mm)1,承B(mm)1,环境温度(°C)0,湿度(%)1,设备电压(V)1,集中器电压(V)0,环境湿度(%)0,温度(°C)1,备注1");
QString MeasureDB::local_bDetailField=QString::fromWCharArray(L"id,tm,deviceNo,b1,b2,temperature,temperatureIn,voltage,voltage2,humidity,humidityIn,remark");

QString MeasureDB::local_currentDetailName=QString::fromWCharArray(L"currentDetect");
QString MeasureDB::local_currentDetailTitle=QString::fromWCharArray(L"ID0,时间1,设备号1,温度1,湿度1,电压1,电流1,温度21,湿度21,临时0,临时21,备注1");
QString MeasureDB::local_currentDetailField=QString::fromWCharArray(L"id,tm,deviceNo,t1,h1,v1,current,t2,h2,tmp1,tmp2,remark");

QString MeasureDB::local_devcieManagementName=QString("devicesManagement");
QString MeasureDB::local_devcieManagementField=QString::fromWCharArray(L"id,local,remark,curDeviceID");

QString MeasureDB::local_deviceInfoName=QString("local_deviceInfo");
// 1    2       3         4          5             6         7         8     9     10    11    12    13    14
//"ID,deviceNO,deviceType,department,tableName,localPosition,installTm,line1,line2,line3,line4,line5,line6,remark"
//1
//                                                            1 2        3          4          5             6         7     8     9     10    11    12
QString MeasureDB::local_deviceInfoField=QString::fromWCharArray(L"ID,deviceNO,deviceType,department,localPosition,installTm,line1,line2,line3,line4,line5,line6");
//                                                           1  2       3   4       5      6       7    8    9    10    11   12
QString MeasureDB::local_deviceInfoTitle=QString::fromWCharArray(L"ID0,设备编号1,类型1,所属路局1,安装位置1,安装时间1,线路10,线路20,线路30,线路40,线路50,线路60");
QString MeasureDB::local_deviceInfoFilter="deviceNO in('0400020002')";
QPair<QStringList,QStringList> MeasureDB::local_curManagementDevices;//=QPair<QStringList,QStringList>("","");
DETECT_TYPE MeasureDB::curDetect=NO_TYPE;
MeasureDB::MeasureDB(const QString& dbName,QSqlDatabase &mysql)
{
    QSqlError err;
    m_mysql=mysql;
    curManagementIndex=-1;
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
        updateDeviceInfo();     //1
        updateUserManagement(); //2
    }
    curDataName=dbName;
}

void MeasureDB::readConfig(void)
{
    QSettings  settings("Config.ini", QSettings::IniFormat);

    QString tmpDepartment=settings.value("par/local","").toString();
    curManagementIndex=local_curManagementDevices.first.indexOf(tmpDepartment);
    if(curManagementIndex!=-1)
    {
        local_deviceInfoFilter=QString("deviceNO in(%1)").arg(local_curManagementDevices.second.at(curManagementIndex));
        qDebug()<<"cur device filter="<<local_deviceInfoFilter;//<<curDepartment<<tmp<<"dd"<<tmpDepartment;
        QSqlQuery query(m_db);
        QString strSql=QString("select tableName,deviceType from %1 where %2 group by tablename")
                .arg(local_deviceInfoName)
                .arg(local_deviceInfoFilter);
        if(query.exec(strSql))
        {
            qDebug()<<"get tablename and deviceType by config.ini set,sql"<<strSql;
            while(query.next())
            {
                //利用存储数据的表格名称判别其传感器类型
                QString tmp=query.value(0).toString();
                //                qDebug()<<"cur my name"<<tmp;
                if(tmp.contains("wireDetect")||tmp.contains("detailinfo0514"))
                {
                    mysql_wireDetailTable=tmp;
                    qDebug()<<"wire detect,table="<<mysql_wireDetailTable;
                    //qDebug()<<"here------------"<<mysql_wireDetailTable;
                    curDetect=WIRE_TYPE;
                }
                else if(tmp.contains("BDetect"))
                {
                    mysql_bDetailTable=tmp;
                    qDebug()<<"B detect,table="<<mysql_bDetailTable;
                    curDetect=B_TYPE;
                }
                else if(tmp.contains("currentDetect"))
                {
                    mysql_currentTable=tmp;
                    qDebug()<<"current detect,table="<<mysql_currentTable;
                    curDetect=CURRENT_TYPE;
                }
            }
        }
        else
        {
            qDebug()<<"error,local device info tb"<<strSql;
        }
    }
    else
    {
        qDebug()<<"error,no right local set"<<tmpDepartment<<local_curManagementDevices;
    }
    if(settings.value("par/initialData","").toInt())
    {
        deleteAllData();
        settings.setValue("par/initialData",0);
    }
}
void MeasureDB::deleteAllData(void)
{
    //    if(m_db.isOpen())
    {
        QSqlQuery query(m_db);
        //        qDebug()<<"b1"<<query.exec(QString("delect from %1").arg(local_wireDetailName));
        //        qDebug()<<"b2"<<query.exec(QString("delect from %1").arg(local_bDetailName));
        //        qDebug()<<"b3"<<query.exec(QString("delect from %1").arg(local_devcieManagementName));
        //        qDebug()<<"b4"<<query.exec(QString("delect from %1").arg(local_deviceInfoName));

        //        qDebug()<<QString("delete all data,wire=%1,b=%2,management=%3,deviceinfo=%4")
        //                  .arg(query.exec(QString("delect from %1").arg(local_wireDetailName)))        //删除本地电屏铠数据
        //                  .arg(query.exec(QString("delect from %1").arg(local_bDetailName)))           //删除本地B值数据
        //                  .arg(query.exec(QString("delect from %1").arg(local_devcieManagementName)))  //删除本地用户管理数据
        //                  .arg(query.exec(QString("delect from %1").arg(local_deviceInfoName)));        //输出本地设备信息数据
    }
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

    QString strManagementSql=QString("CREATE TABLE %1 "\
                                     "(ID int UNIQUE,local varchar(100),remark varchar(100),curDeviceID varchar(1000))")
            .arg(local_devcieManagementName);
    QString strCurrentSql=QString("CREATE TABLE %1 "\
                                  "(ID int UNIQUE,tm varchar(30),deviceNO varchar(30),"\
                                  "t1 float,h1 float,v1 float,current float,t2 float,h2 float,"\
                                  "tmp1 varchar(100),tmp2 varchar(100),remark varchar(100))")
            .arg(local_currentDetailName );

    bool b1=query.exec(strWireSql);
    bool b2=query.exec(strDeviceInfoSql);
    bool b3=query.exec(strBSql);
    bool b4=query.exec(strManagementSql);
    bool b5=query.exec(strCurrentSql);
    //    qDebug()<<"current table,sql="<<strCurrentSql<<b5;
    //    isCloseDB();
    //    qDebug()<<"create detail"<<b1<<"create devcie "<<b2<<"devcie sql="<<str2;
    return b1&b2&b3&b4;
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
bool MeasureDB::insert_managementRecord(device_management &record)
{
    QSqlQuery query(m_db);
    QString strSql=QString("insert into %1(id,local,remark,curDeviceID) values(%2,'%3','%4',%5)")
            .arg(local_devcieManagementName)
            .arg(record.id)
            .arg(record.local)
            .arg(record.remark)
            .arg(record.curDeviceID);
    qDebug()<<"insert management"<<strSql;
    return query.exec(strSql);
}
bool MeasureDB::insert_wireDetailRecord(wire_data &record)
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
//函数功能：插入泄漏电流检测数据
bool MeasureDB::insert_currentDetailRecord(current_Data &record)
{
    QSqlQuery query(m_db);
    //                                  1  2  3  4        5  6  7  8       9  10 11   12    13
    QString strSql=QString("insert into %1(id,tm,deviceNo,t1,h1,v1,current,t2,h2,tmp1,tmp2,remark)"\
                           "values(%2,'%3','%4',%5,%6,%7,%8,%9,%10,\'%11\',\'%12\',\'%13\')").arg(local_currentDetailName)
            .arg(record.id)         //1
            .arg(record.tm)         //2
            .arg(record.deviceNo)   //3
            .arg(record.t1)         //4
            .arg(record.h1)         //5
            .arg(record.v1)         //6
            .arg(record.current)    //7
            .arg(record.t2)         //8
            .arg(record.h2)         //9
            .arg(record.tmp1)       //10
            .arg(record.tmp2)       //11
            .arg(record.remark);    //12
    bool b=query.exec(strSql);
    qDebug()<<"current insert,sql"<<strSql<<b;
    return b;
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
//        strSql=QString("select id from %1 order by id").arg(local_wireDetailName);

    }
    else if(flag==B_TYPE)
    {
        strSql=QString("select count(*) from %1").arg(local_bDetailName);
    }
    else if(flag==CURRENT_TYPE)
    {
        strSql=QString("select count(*) from %1").arg(local_currentDetailName);
    }
    else if(flag==DEVICE_INFO)
    {
        strSql=QString("select count(*) from %1").arg(local_deviceInfoName);
    }
    bool b=query.exec(strSql);
    qDebug()<<"get local record count="<<strSql<<b;
    if(b)
    {
        long count=0;
#if 1
        while(query.next())
        {
            count=query.value(0).toLongLong();
//            quer
        }
#else
        if(query.first())
        {
            qDebug()<<"id value first"<<query.value("id").toLongLong();
        }
        if(query.last())
        {
            qDebug()<<"id value last"<<query.value("id").toLongLong();
        }
#endif
        return count;
    }
    else
        return 0;
}
//函数功能：将远程数据库中的设备信息同步至本地数据库中的设备信息表格，通过ID号是否一致判别是否更新
bool MeasureDB::updateDeviceInfo( void)
{
    if(!m_mysql.isOpen())
        return false;
    QSqlQuery query(m_db);
    QSqlQuery query1(m_mysql);
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

            //                        qDebug()<<"insert management tb,sql"<<strInsertSql<<
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
bool MeasureDB::updateUserManagement( void)
{
    if(m_mysql.isOpen())
    {
        QSqlQuery query_localDb(m_db);
        QSqlQuery query_remoteMysql(m_mysql);
        QString strMysql=QString("select ID,local,remark,curDeviceID from %1").arg(mysql_deviceManagementTb);
        //    qDebug()<<"mysql sql"<<strMysql;
        //        QString strDelectManagement=QString("delete from %1").arg(local_devcieManagementName);
        //        query_localDb.exec(strDelectManagement);

        if(query_remoteMysql.exec(strMysql))
        {
            local_curManagementDevices.first.clear();
            local_curManagementDevices.second.clear();
            QString oneManagement;
            while(query_remoteMysql.next())
            {
                QString tmp="";

                for(int i=1;i<3;i++)
                {
                    tmp+=QString("\'%1\',").arg(query_remoteMysql.value(i).toString());
                }
                oneManagement=query_remoteMysql.value("curDeviceID").toString();
                local_curManagementDevices.second<<oneManagement;
                local_curManagementDevices.first<<query_remoteMysql.value("local").toString();
                tmp+=QString("\'%1\'").arg(oneManagement.replace("'","''"));

                QString strInsertSql=QString("insert into %1(ID,local,remark,curDeviceID"\
                                             ") values(%2,%3)").arg(local_devcieManagementName).arg(query_remoteMysql.value(0).toString()).arg(tmp);
                //qDebug()<<"insert management tb,sql"<<strInsertSql<<
                query_localDb.exec(strInsertSql);
            }
            readConfig();
            return true;
        }
        else
        {
            qDebug()<<"get mysql db is error";
            return false;
        }
    }
    else
    {
        qDebug()<<"remote is not ok,i will get local management";
        QSqlQuery query_localDb(m_db);
        QString strMysql=QString("select ID,local,remark,curDeviceID from %1").arg(local_devcieManagementName);
        if(query_localDb.exec(strMysql))
        {
            local_curManagementDevices.first.clear();
            local_curManagementDevices.second.clear();
            while(query_localDb.next())
            {
                local_curManagementDevices.second<<query_localDb.value("curDeviceID").toString();
                local_curManagementDevices.first<<query_localDb.value("local").toString();
            }
            readConfig();
        }
    }
}
void MeasureDB::updateBDetailRecord(long localCount)
{
    QSqlQuery query(m_mysql);
    QString strSql;
    bool bflag=false;
    //                      0 1  2        3  4  5           6             7       8        9        10         11
    strSql=QString("select id,tm,deviceNo,b1,b2,temperature,temperatureIn,voltage,voltage2,humidity,humidityIn,remark from %1 where id>%2")
            .arg(MeasureDB::mysql_bDetailTable).arg(localCount);

    bflag=query.exec(strSql);
    qDebug()<<"b value,sql"<<strSql<<bflag;
    if(bflag)
    {
        m_mysql.transaction();
        Transaction();
        while(query.next())
        {

            //detail table
            B_Data dd;
            dd.id=query.value(0).toLongLong();
            dd.tm=query.value(1).toString();
            dd.deviceNo=query.value(2).toString();
            dd.b1=query.value(3).toFloat();
            dd.b2=query.value(4).toFloat();
            dd.temperature=query.value(5).toFloat();
            dd.temperatureIn=query.value(6).toFloat();
            dd.voltage=query.value(7).toFloat();
            dd.voltage2=query.value(8).toFloat();
            dd.humidity=query.value(9).toFloat();
            dd.humidityIn=query.value(10).toFloat();
            dd.remark=query.value(11).toString();
            insert_bDetailRecord(dd);
        }
        Commit();
        m_mysql.commit();
    }
}
void MeasureDB::updateWireDetailRecord(long localCount)
{
    QSqlQuery remote_query(m_mysql);
    QString strSql;

    strSql=QString("select id,tm,deviceNo,lineNo,voltage,current,temperature,humidity from %1 where id>%2").arg(MeasureDB::mysql_wireDetailTable).arg(localCount);
    if(remote_query.exec(strSql))
    {
        m_mysql.transaction();
        Transaction();
        while(remote_query.next())
        {

            //detail table
            wire_data dd;
            dd.id=remote_query.value(0).toLongLong();
            dd.tm=remote_query.value(1).toString();
            dd.deviceNo=remote_query.value(2).toString();
            dd.lineNo=remote_query.value(3).toInt();
            dd.voltage=remote_query.value(4).toFloat();
            dd.current=remote_query.value(5).toFloat();
            dd.temperature=remote_query.value(6).toFloat();
            dd.humidty=remote_query.value(7).toFloat();
            insert_wireDetailRecord(dd);
        }
        Commit();
        m_mysql.commit();
    }
}
void MeasureDB::updateCurrentDetailRecord(long localCount)
{
    if(!m_mysql.isOpen())
        return ;
    QSqlQuery remote_query(m_mysql);
    QString strSql;

    strSql=QString("select id,tm,deviceNo,t1,h1,v1,current,t2,h2,tmp1,tmp2,remark from %1 where id>%2")
            .arg(mysql_currentTable).arg(localCount);
    if(remote_query.exec(strSql))
    {
        m_mysql.transaction();
        Transaction();
        while(remote_query.next())
        {
            //detail table
            current_Data dd;
            dd.id       =remote_query.value("id").toLongLong();
            dd.tm       =remote_query.value("tm").toString();
            dd.deviceNo =remote_query.value("deviceNo").toString();
            dd.t1       =remote_query.value("t1").toInt();
            dd.h1       =remote_query.value("h1").toFloat();
            dd.v1       =remote_query.value("v1").toFloat();
            dd.current  =remote_query.value("current").toFloat();
            dd.t2       =remote_query.value("t2").toFloat();
            dd.h2       =remote_query.value("h2").toFloat();
            dd.tmp1     =remote_query.value("tmp1").toFloat();
            dd.tmp2     =remote_query.value("tmp2").toFloat();
            dd.remark   =remote_query.value("remark").toFloat();
            insert_currentDetailRecord(dd);
        }
        Commit();
        m_mysql.commit();
    }
}
