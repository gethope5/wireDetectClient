#ifndef MULTTABLEFRM_H
#define MULTTABLEFRM_H

#include <QWidget>
#include <qtableview.h>
#include "QtSql"
namespace Ui {
class multTableFrm;
}

class multTableFrm : public QWidget
{
    Q_OBJECT

public:
    explicit multTableFrm(QWidget *parent = 0);
    ~multTableFrm();
    QTableView *tableView;
    void setDateBase(QSqlDatabase &db,QString tbName,QString strShow,QString title);
    void showTable(  QString filter,bool f);
private:
    Ui::multTableFrm *ui;
    QSqlDatabase m_db;
    QString tableName;
    QString showField;
    QString tableTitle;
};
#endif // MULTTABLEFRM_H
