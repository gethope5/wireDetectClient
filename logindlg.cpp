#include "logindlg.h"
#include "ui_logindlg.h"
#include <qdebug.h>
loginDlg::loginDlg(QWidget *parent,bool f) :
    QDialog(parent),bDevcieNo(false),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromWCharArray(L"请输入管理员密码..."));
    ui->chbModifyDeviceNo->setEnabled(f);
}

loginDlg::~loginDlg()
{
    delete ui;
}

void loginDlg::on_pbtnOk_clicked()
{
    if(bCheckOk)
    {
        ui->chbModifyDeviceNo->setEnabled(true);
    }
    if(ui->lineEdit->text()=="123456")
    {
        qDebug()<<"login ok";
        accept();
    }
    else
    {
        qDebug()<<"login not ok";
        reject();
    }
}
void loginDlg::on_pbtnCancel_clicked()
{
    reject();
}

void loginDlg::on_chbModifyDeviceNo_clicked()
{
    if(ui->chbModifyDeviceNo->checkState()==Qt::Checked)
    {
        bDevcieNo=true;
        //        qDebug()<<"check is ok";
    }
    else
    {
        bDevcieNo=false;
        //        qDebug()<<"check is not ok";
    }
}
