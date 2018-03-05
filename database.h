#ifndef _DATA_BASE_H_
#define _DATA_BASE_H_

#include <QString>
#include <QStringList>

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
//zbw:2012-09
struct MeasureDebugData
{
    //1id 2时间 3 里程4轨距      5超高       6 拉出值   7 导高      8 X倾角  9Y倾角
    //id  tm   nWalkDistance  railwidth railheight wirewidth wireheigth fXangle fYangle
    int id;             //1     id
    QString tm;         //2     时间
    double nWalkDistance;  //3     里程
    float dKm;  //3     公里标
    QString station;    //4     站区
    QString poleID;     //5     杆号
    int nRailWidth;     //6     轨距
    int nRailHeight;    //7     超高
    int nWireWidth;     //8     拉出值
    int nWireHeight;    //9     导高
    float fXAngle;      //10    X倾角,05-27:承力索高度
    float fYAngle;      //11    Y倾角,05-27:结构高度
    QString orgData;    //12    原始数据
    QPoint wire1;
    int nSide;          //侧面界限
    int carrier;        //承力索
    float baseAngle;
    bool bDropper;
    bool bMidPole;
    MeasureDebugData()
    {
        carrier=-1;
        baseAngle=0;
        bDropper=false;
        bMidPole=false;
    }
};
typedef struct
{
    int     nRailWidth;     //7 轨距
    int     nRailHeight;    //8 超高
    float sideWidth;        //9 侧面界限
    float sideHeight;       //10 红线
    float structHeight;     //11 结构高度
    float dWireWidth;       //12 定拉
    float dWireHeight;      //13 定高
    float slope;            //14 坡度
    float  gaocha;          //15 高差
    float midWireHeight;    //16 中高
    float midWireWidth;     //17 中拉
    float wireWidth1;       //18 非支拉出值
    float wireHeight1;      //19 非支导高1
    float wiresWidth;       //20 水平距离
    float wiresHeight;      //21 垂直距离
    float wire500Height;    //22 500高差
}OnePolePar;
/* 2012-05-14 */    //id,时间，里程，站区，杆号，最大导高，最小导高，高差，最大拉出值，定位器描述
//(id INT, tm ;,nWalkDistance float,station varchar(30),poleid varchar(10),maxDaogao float, minDaogao float, gaocha float, maxLachuzhi float,LocationRemark varchar(100))

typedef struct
{
    int id;                 //1 ID
    QString tm;             //2 时间
    float nWalkDistance;             //3 里程
    float dKm;              //4 公里标
    QString station;        //5 站区
    QString poleid;         //6 杆号

    OnePolePar  onePolePar;
    QString locationRemark; //23 定位器描述
    QByteArray PicPath;     //24 图片存放位置
    float  maxdaogao;       //6 最大导高
    float  mindaogao;       //7 最小导高
    float  maxLachuzhi;     //9 拉出值
    QPair<bool,int> sideLimit;     //10 侧面界限

    //ID, 2 时间, 3 里程(米), 4公里标(千米),  5站区,   6杆号,  7轨距,       8超高,
    //id, tm,    nWalkDistance       ,km ,         station, poleid,railwidth ,railheight
    //9侧面界限,  10 红线 11 结构高度   12定拉       13定高,       14坡度,      高差,    16中高,
    //sideWidth,Height,structHeight ,dWireWidth ,dWireHeight ,slope float,gaocha, midWireHeight,
    //17中拉,       18非支拉出值,19非支导高1, 20 水平距离,21垂直距离,   22 500高差,      23 定位器描述,   24 巡视图片;
    //midWireWidht,wirewidth1,wireheight1,wiresWidth,wiresHeight,wire500Height,LocationRemark,picPath");

    QString railwayName;
    QString direction;
}MeasureIdEx_t;
typedef struct
{
    QString poleindex;
    QString station;
}tableStruct_t;
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
struct deviceInfo
{
    int id ;                //1  id
    QString deviceNo ;      //2  设备编号
    QString deviceAddr ;    //3  设备线路
    QString department ;    //4  所属路局
    QString position ;      //5  安装位置
    //    QString installTm ;     //6  安装时间
    //    QString addTm ;         //7  添加时间
    QString line1 ;         //8  线路1
    QString line2 ;         //9  线路2
    QString line3 ;         //10 线路3
    QString line4 ;         //11 线路4
    QString line5 ;         //12 线路5
    QString line6 ;         //13 线路6
    //    int remainCell;         //14 剩余电量
    //    float temperature ;     //15 温度
    //    float humidity ;        //16 湿度
    //    float recentTmUpdate ;  //17 更新时间
};

struct fieldInfo
{
    QString fieldName;
    QString fieldTitle;
    QString dataType;
    bool bVisible;
};
struct tableInfo
{
    QVector<fieldInfo> fields;
    QString name;
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
    static QString detailDataTb;//本地数据库详细数据表格
    static QString deviceInfoTb;//本地数据库设备信息表格
    static QString mysqlDetailDataTb;
    static QString mysqlDeviceInfoTb;
    static QString detailDataTitle;
    static QString overDataTitle;
    static QString detectDataTitle;
    static QString deviceInfoTitle;


    bool insert_detailRecord(detailRecord &record);
    bool insert_deviceInfoRecord(deviceInfo &record);
    long recordCount(bool);
private:

    QSqlDatabase m_db;
};

#endif


