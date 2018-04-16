#include "multtablefrm.h"
#include "ui_multtablefrm.h"

multTableFrm::multTableFrm(QWidget *parent) :
    QWidget(parent),tableName(""),
    ui(new Ui::multTableFrm)
{
    ui->setupUi(this);
    tableView=ui->tbTableInfo;
    tableView->setEditTriggers(/*QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|*/QAbstractItemView::NoEditTriggers);
    qDebug()<<" db status="<<m_db.isValid();
    ui->tbTableInfo->setAlternatingRowColors(true);


    ui->tbTableInfo->setStyleSheet("QTableView{color: rgb(0, 0, 0);"\
                                 /*  "border: 1px solid #C07010;gridline-color:#C07010;"\
                                   "background-color: rgb(20, 20, 20);alternate-background-color: rgb(200, 200, 200);"\*/
                                   "selection-background-color: rgb(130, 190, 100); }  "\
                                   "QTableView::item:!alternate:!selected{"\
                                   "background-color: rgb(220, 220, 220);}");
    ui->pbtnFront->setVisible(false);
    ui->pbtnNext->setVisible(false);
    ui->label->setVisible(false);
    ui->lneJump->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->label->setVisible(false);
}
void multTableFrm::setDateBase(QSqlDatabase &db,QString tbName,QString strShow,QString title)
{
//    qDebug()<<" before ,db status="<<m_db.isValid()<<m_db.isOpen();
    m_db=db;
    tableName=tbName;
    tableTitle=title;
    showField=strShow;
    qDebug()<<" initial,db status="<<m_db.isValid()<<m_db.isOpen();

}
multTableFrm::~multTableFrm()
{
    delete ui;
}
void multTableFrm::showTable(QString filter,bool f)
{
    QTime timer;
    bool bExec;
    timer.start();
    if(!f)
        filter=QString("tm like '%1%'").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd"));

    QSqlQueryModel * queryModel = new QSqlQueryModel(this);

    QSqlQuery query(m_db);
    QString strSql=QString("SELECT %1 from %2 where %3").arg(showField).arg(tableName).arg(filter);
//    QString strSql=QString::fromWCharArray(L"SELECT * from %1 where id>0").arg(tableName);
    bExec=query.exec(strSql);
    queryModel->setQuery(query);
    for(int i=0;i<tableTitle.split(',').count();i++)
    {
        QString tmp=tableTitle.split(',').at(i);
        queryModel->setHeaderData(i,Qt::Horizontal, QString(tmp.left(tmp.length()-1)));
    }
    this->tableView->setModel(queryModel);
//    tableview->selectAll();
//    tableview->resizeColumnsToContents();
    qDebug()<<"filter"<<strSql<<"table="<<tableName<<"time="<<timer.elapsed()<<"query="<<bExec;
}
