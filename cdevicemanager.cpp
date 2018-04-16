#include "cdevicemanager.h"
#include "ui_cdevicemanager.h"
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

CDeviceManager::CDeviceManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CDeviceManager)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    //设置编辑表格
    sqlTableModel = new MySqlModel(this);
    sqlTableModel->setQuery("SELECT *FROM linesaliase");
    ui->linesAliase->setModel(sqlTableModel);
    ui->linesAliase->horizontalHeader()->setStretchLastSection(true);
    //ui->linesAliase->horizontalHeader()->setStretchLastSection(true);
    //ui->linesAliase->resizeColumnsToContents();
}

CDeviceManager::~CDeviceManager()
{
    delete ui;
}

void CDeviceManager::SetDB(QSqlDatabase& database)
{
    db = database;
}

void CDeviceManager::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage bkImage(":/images/images/bk.jpg");
    painter.drawImage(0,0,bkImage);
}

void CDeviceManager::on_savePower_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();
    out<<qint8(10);//长度
    out<<qint8(0x61);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint8(0xAA);
    out<<qint16(0);
    out<<qint8(0);
    out<<qint8(10);//校验和
    out<<qint16(0x0D0A);//回车
    emit SetDevice(no,cmd);

    qDebug()<<cmd.size();
    qDebug()<<cmd;
}

void CDeviceManager::on_runFast_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();
    out<<qint8(0x0A);//长度
    out<<qint8(0x62);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint8(0x55);
    out<<qint16(0);
    out<<qint8(0);
    out<<qint8(0);//校验和
    out<<qint16(0X0D0A);//回车
    emit SetDevice(no,cmd);
    //qDebug()<<out;
}

void CDeviceManager::on_setTimeEescap_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();//设备编号
    qint8 timeEescap = ui->tm->value();
    out<<qint8(0x0A);//长度
    out<<qint8(0x63);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint8(timeEescap);//时间间隔
    out<<qint16(0);
    out<<qint8(0);
    out<<qint8(0);//校验和
    out<<qint16(0X0D0A);//回车
    emit SetDevice(no,cmd);
}

void CDeviceManager::on_setNewNo_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();//设备编号
    qint16 newNo = ui->newNo->value();
    out<<qint8(0x0A);//长度
    out<<qint8(0x64);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint16(newNo);//时间间隔
    out<<qint16(0);
    //out<<qint8(0);
    out<<qint8(0);//校验和
    out<<qint16(0X0D0A);//回车
    emit SetDevice(no,cmd);
}

void CDeviceManager::on_setWarningVal_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();//设备编号
    qint8 lineNo = ui->lineNo->value();
    qint16 iVal = ui->warningVal->value();

    out<<qint8(0x0A);//长度
    out<<qint8(0x65);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint8(lineNo);//时间间隔
    out<<qint16(iVal);
    out<<qint8(0);
    out<<qint8(0);//校验和
    out<<qint16(0X0D0A);//回车
    emit SetDevice(no,cmd);
}

void CDeviceManager::on_setErrVal_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();//设备编号
    qint8 lineNo = ui->errNo->value();
    qint16 iVal = ui->errVal->value();

    out<<qint8(0x0A);//长度
    out<<qint8(0x66);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint8(lineNo);//时间间隔
    out<<qint16(iVal);
    out<<qint8(0);
    out<<qint8(0);//校验和
    out<<qint16(0X0D0A);//回车
    emit SetDevice(no,cmd);
}

void CDeviceManager::on_setAllToZero_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();//设备编号

    out<<qint8(0x0A);//长度
    out<<qint8(0x67);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint8(0x07);
    out<<qint16(no);
    out<<qint8(0);
    out<<qint8(0);//校验和
    out<<qint16(0X0D0A);//回车
    emit SetDevice(no,cmd);
}

void CDeviceManager::on_setLineZero_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    qint16 no = ui->devieceNo->text().toInt();//设备编号
    qint8 line = ui->zeroLineNo->value();
    out<<qint8(0x0A);//长度
    out<<qint8(0x67);//特征码
    out<<qint8(0x06);//类型
    out<<no;//编号
    out<<qint8(line);//线路编号
    out<<qint16(line);
    out<<qint8(0);
    out<<qint8(0);//校验和
    out<<qint16(0X0D0A);//回车
    emit SetDevice(no,cmd);
}

void CDeviceManager::on_pushButton_clicked()
{
    //if(ui->tableAddDeviece->)
    sqlTableModel->setQuery("SELECT * FROM linesaliase");

}

void CDeviceManager::on_AddDeviece_clicked()
{
    bool ok;//判断输入的编号是否合法
    qint16 no = ui->devieceNo_2->text().toInt(&ok);
    if(ok == false)
    {
        QMessageBox::critical(this,"提示",QString::fromWCharArray(L"请输入正确的设备编号"));
        return;
    }
    QString strOwner = ui->devieceOwner->text();
    QString strPosition = ui->deviecePosition->text();
    QDateTime dateTime = ui->dateTimeEdit->dateTime();
    if(strOwner.isEmpty()||strPosition.isEmpty()||ui->devieceNo_2->text().isEmpty())
    {
        QMessageBox::critical(this,"提示","输入的数据不完整");
        return;
    }

    QSqlQuery sqlQuery(db);

    sqlQuery.prepare("INSERT INTO deviecestaturs(设备编号,所属路局,安装位置,安装时间,添加时间) VALUES(?,?,?,?,now())");
    sqlQuery.bindValue(0,no);
    sqlQuery.bindValue(1,strOwner);
    sqlQuery.bindValue(2,strPosition);
    sqlQuery.bindValue(3,dateTime);

    if(!sqlQuery.exec())
    {
        QMessageBox::information(this,QString::fromWCharArray(L"错误"),QString::fromWCharArray(L"添加设备失败设备编号已存在"));
        return;
    }

    sqlQuery.prepare("INSERT INTO linesaliase (设备编号,线路编号) VALUES(?,'总机')");
    sqlQuery.bindValue(0,no);
    if(!sqlQuery.exec())
    {
        QMessageBox::information(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"添加设备失败已存在相同编号设备"));
    }
    for(int lineNo = 0;lineNo!=6;++lineNo)
    {

        sqlQuery.prepare("INSERT INTO linesaliase (设备编号,线路编号) VALUES(?,?)");
        sqlQuery.bindValue(0,no);
        sqlQuery.bindValue(1,QString("线路%0").arg(lineNo+1));
        if(!sqlQuery.exec())
        {
            qDebug()<<sqlQuery.lastError().text();
        }
    }

    emit AddDevice(no,strOwner,strPosition,dateTime);
    //sqlTableModel->select();
    sqlTableModel->setQuery("SELECT * FROM linesaliase");


}

void CDeviceManager::on_pushButton_2_clicked()
{
    qint16 no = ui->lineEdit->text().toInt();
    emit DeleteDeviece(no);
    QSqlQuery sqlQuery(db);
    sqlQuery.prepare("DELETE FROM linesaliase WHERE 设备编号 = ?");
    sqlQuery.bindValue(0,no);
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError().text();
    }
    //sqlTableModel->select();
    sqlTableModel->setQuery("SELECT * FROM linesaliase");
}
