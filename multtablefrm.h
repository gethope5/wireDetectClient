#ifndef MULTTABLEFRM_H
#define MULTTABLEFRM_H

#include <QWidget>
#include <qtableview.h>
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
private:
    Ui::multTableFrm *ui;
};

#endif // MULTTABLEFRM_H
