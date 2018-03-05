#include "multtablefrm.h"
#include "ui_multtablefrm.h"

multTableFrm::multTableFrm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::multTableFrm)
{
    ui->setupUi(this);
    tableView=ui->tbTableInfo;
    tableView->setEditTriggers(/*QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|*/QAbstractItemView::NoEditTriggers);
}

multTableFrm::~multTableFrm()
{
    delete ui;
}
