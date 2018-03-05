#ifndef CDEVICEMANAGER_H
#define CDEVICEMANAGER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDateTime>
#include <QSqlTableModel>
#include "mysqlmodel.h"

namespace Ui {
class CDeviceManager;
}

class CDeviceManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDeviceManager(QWidget *parent = 0);
    ~CDeviceManager();
    void SetDB(QSqlDatabase& database);
signals:
    void DeleteDeviece(qint16);
    void SetDevice(qint16,QByteArray);
    void AddDevice(qint16,QString,QString,QDateTime);
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_savePower_clicked();

    void on_runFast_clicked();

    void on_setTimeEescap_clicked();

    void on_setNewNo_clicked();

    void on_setWarningVal_clicked();

    void on_setErrVal_clicked();

    void on_setAllToZero_clicked();

    void on_setLineZero_clicked();

    void on_pushButton_clicked();

    void on_AddDeviece_clicked();

    void on_pushButton_2_clicked();


private:
    void ConnectDB();
    void ShowDeviece();

    MySqlModel *sqlTableModel;
    QSqlDatabase db;
    Ui::CDeviceManager *ui;
};

#endif // CDEVICEMANAGER_H
