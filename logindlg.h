#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class loginDlg;
}

class loginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit loginDlg(QWidget *parent = 0,bool f=false);
    ~loginDlg();
    bool bCheckOk;
    bool bDevcieNo; //设备号修改
private slots:
    void on_pbtnOk_clicked();

    void on_pbtnCancel_clicked();


    void on_chbModifyDeviceNo_clicked();

private:
    Ui::loginDlg *ui;
};

#endif // LOGINDLG_H
