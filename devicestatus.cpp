#include "devicestatus.h"

DeviceStatus::DeviceStatus(QString deviceName,DEVICE_CONNECT_STATUS initialFlag,QWidget *parent) :
    QPushButton(parent)
{
    this->setMaximumHeight(20);
    this->setIconSize(QSize(30,20));
    this->setStyleSheet("border:0px;");
    setDeviceStatusInitial(deviceName,initialFlag);
}
void DeviceStatus::setDeviceStatusInitial(QString deviceName,DEVICE_CONNECT_STATUS initialFlag)
{
    this->setText(deviceName);
    slot_deviceStatusChange(initialFlag);
}
void DeviceStatus::slot_deviceStatusChange(DEVICE_CONNECT_STATUS flag)
{
//    if((QPushButton *)this->sender()->parent()==mcuTcpDevice)
//    {
//        qDebug()<<"mct tcp";
//    }
    setCurStatus(flag);
}
void DeviceStatus::setCurStatus(DEVICE_CONNECT_STATUS flag)//flag=true,设备连接；false，设备掉线
{
    if(flag==DISCONNECTED)
    {
        this->setIcon(QIcon(QPixmap::fromImage(QImage("./images/deviceoff.png"))));
        this->setToolTip(this->text()+QTextCodec::codecForName("gbk")->toUnicode("未连接..."));
    }
    else if(flag==CONNECTED)
    {
        this->setIcon(QIcon(QPixmap::fromImage(QImage("./images/deviceon.png"))));
        this->setToolTip(this->text()+QTextCodec::codecForName("gbk")->toUnicode("已连接..."));
    }
    else if(flag==CONNECTING)
    {
        this->setIcon(QIcon(QPixmap::fromImage(QImage("./images/deviceconnecting.png"))));
        this->setToolTip(this->text()+QTextCodec::codecForName("gbk")->toUnicode("连接中..."));
    }
}
