#ifndef MYSQLMODEL_H
#define MYSQLMODEL_H

#include <QObject>
//#include <QVector>
#include <QSqlQueryModel>


class MySqlModel:public QSqlQueryModel
{
    Q_OBJECT
public:
    MySqlModel(QObject *parent = 0);

    void SetEditAbleColumns(const QVector<unsigned int> columns);
    Qt::ItemFlags flags(const QModelIndex &index) const/* Q_DECL_OVERRIDE*/;
    bool setData(const QModelIndex &index, const QVariant &value, int role)/* Q_DECL_OVERRIDE*/;
private:
    //QVector<unsigned int> editAbleColumns;
};

#endif // MYSQLMODEL_H
