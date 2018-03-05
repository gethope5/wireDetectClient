#include "mysqlmodel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


MySqlModel::MySqlModel(QObject *parent)
    :QSqlQueryModel(parent)
{

}

//void MySqlModel::SetEditAbleColumns(const QVector<unsigned int> columns)
//{
//    editAbleColumns = columns;
//}

Qt::ItemFlags MySqlModel::flags(const QModelIndex &index) const
{
        Qt::ItemFlags flags = QSqlQueryModel::flags(index);
        if (index.column() == 2)
            flags |= Qt::ItemIsEditable;
        return flags;
}

bool MySqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if(index.column()!=2)
        return false;
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QModelIndex lineNoIndex = QSqlQueryModel::index(index.row(),1);
    qint16 No= data(primaryKeyIndex).toInt();
    QString lineNo = data(lineNoIndex).toString();
    clear();

    bool ok;
    QSqlQuery query;
    query.prepare("UPDATE linesaliase SET 线路名称 = ? WHERE 设备编号 = ? AND 线路编号 = ?");
    query.addBindValue(value.toString());
    query.addBindValue(No);
    query.addBindValue(lineNo);
    qDebug()<<No<<lineNo;
    ok = query.exec();
    if(!ok)
        qDebug()<<query.lastError();
    setQuery("SELECT * FROM linesaliase");
    return ok;
}
