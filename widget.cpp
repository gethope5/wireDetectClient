#include "widget.h"
#include "ui_widget.h"
#include <QColor>
#include <QVector>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSharedPointer>
#include <QDate>
#include <QDateTime>
#include "qcustomplot.h"

#define LOCALDEBUG 0

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    manager(NULL),
    tcpServer(NULL),
    model(NULL),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    overEelectric = 4000;

    //  ui->ip->setText("120.25.233.115");
    //  ui->port->setText(QString("%1").arg(9090));

    uiInitial();

    ConnectDB();
    ShowDB();
    ShowStaturs();
    ShowOverData();


    curveInitial();
    showTables("deviecestaturs0514");
}
void Widget::curveInitial(void)
{
    //曲线插件设置
    ui->dataWidget->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->dataWidget->xAxis->setLabel(QString::fromWCharArray(L"时间"));
    ui->dataWidget->yAxis->setLabel(QString::fromWCharArray(L"电流大小"));
    ui->dataWidget->xAxis->setRange(0,24*60*60);
    connect(ui->dataWidget,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(MouseWheel()));
    //    ui->dataWidget->yAxis->setRange(0,100);

    QDateTime tm(ui->dateEdit->date());

    QCPAxisTickerTime *tickerDateTime = new QCPAxisTickerTime;
    tickerDateTime->setTimeFormat(QString::fromWCharArray(L"%h点:%m分"));
    QSharedPointer<QCPAxisTickerTime> sharedTicker(tickerDateTime);

    ui->dataWidget->xAxis->setTicker(sharedTicker);
}
void Widget::uiInitial(void)
{
    //设置曲线颜色
    color.push_back(QColor(0,125,125));
    color.push_back(QColor(0,0,255));
    color.push_back(QColor(0,255,0));
    color.push_back(QColor(0,255,255));
    color.push_back(QColor(255,0,255));
    color.push_back(QColor(255,125,0));
    this->addAction(ui->deviceManager);


    //设置默认界面
    ui->checkBox_2->setChecked(true);
    ui->overflow->setChecked(true);
    ui->devieceStaturs->setChecked(true);
    ui->dataWidget->hide();
    //ui->start->setChecked(false);
    ui->label_6->hide();
    ui->label_7->hide();
    ui->no->hide();
    ui->dateEdit->hide();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->ok->hide();
    ui->label1->hide();
    ui->label2->hide();
    ui->label3->hide();
    ui->label4->hide();
    ui->label5->hide();
    ui->label6->hide();
    //
    ui->label->hide();
    ui->ip->hide();
    ui->label_2->hide();
    ui->port->hide();
    //ui->start->hide();
    ui->detailDate->setDate(QDate::currentDate());
    //connect(ui->detailDate,SIGNAL(editingFinished()),this,SLOT(ShowDB()));



    manager = new CDeviceManager(this);
    connect(manager,SIGNAL(SetDevice(qint16,QByteArray)),this,SLOT(SendData(qint16,QByteArray)));
    manager->SetDB(db);
    connect(manager,SIGNAL(AddDevice(qint16,QString,QString,QDateTime)),this,SLOT(AddDeviece(qint16,QString,QString,QDateTime)));
    connect(manager,SIGNAL(DeleteDeviece(qint16)),this,SLOT(DeleteDeviece(qint16)));
    connect(manager,SIGNAL(SetDevice(qint16,QByteArray)),this,SLOT(SendData(qint16,QByteArray)));
}
Widget::~Widget()
{
    delete ui;
}

void Widget::SetBack()
{
    QPixmap pixmap = QPixmap(":/images/images/bk.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(this->backgroundRole(),QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
}

void Widget::paintEvent(QPaintEvent *paint)
{
    QPainter painter(this);
    QImage bkImage(":/images/images/bk.jpg");
    painter.drawImage(0,0,bkImage);
    // SetBack();

}

void Widget::MouseWheel()
{
    if (ui->dataWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->dataWidget->axisRect()->setRangeZoom(ui->dataWidget->xAxis->orientation());
    else if (ui->dataWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->dataWidget->axisRect()->setRangeZoom(ui->dataWidget->yAxis->orientation());
    else
        ui->dataWidget->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void Widget::DeleteDeviece(qint16 no)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(QString::fromWCharArray(L"SELECT * FROM deviecestaturs WHERE 设备编号 = ?"));
    sqlQuery.bindValue(0,no);
    if(sqlQuery.exec())
    {

        if(sqlQuery.size()<=0)//需要删除的设备不存在
        {
            QMessageBox::critical(manager,QString::fromWCharArray(L"错误"),QString::fromWCharArray(L"需要删除的设备不存在"));
        }
        else
        {
            QMessageBox msgBox(this);
            msgBox.setText(QString::fromWCharArray(L"是否确定删除设备"));
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Cancel)
                return;
            sqlQuery.prepare(QString::fromWCharArray(L"DELETE FROM deviecestaturs WHERE 设备编号 = ?"));
            sqlQuery.bindValue(0,no);
            if(sqlQuery.exec())
            {
                qDebug()<<QString::fromWCharArray(L"删除设备成功");
            }
        }
        ShowDB();
        ShowOverData();
        ShowStaturs();
    }
    else
    {
        qDebug()<<"deviecestaturs is not ok";
    }
}

void Widget::AddDeviece(qint16 no, QString owner, QString position, QDateTime dateTime)
{
    qDebug()<<"AddDeviece called!";
    ShowStaturs();
}

void Widget::SendData(qint16 no, QByteArray cmd)
{

    QFile file("cmd.txt");
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append))
        qDebug()<<QString::fromWCharArray(L"打开文件失败");
    else
    {
        QTextStream outfile(&file);
        outfile<<cmd.toHex()<<endl;
        file.close();
    }
    qDebug()<<"SendData!!!"<<cmd;
    QSqlQuery queryCmd;
    queryCmd.prepare("INSERT INTO devieceCmd VALUES(?,?)");
    queryCmd.bindValue(0,no);
    queryCmd.bindValue(1,cmd);
    if(!queryCmd.exec())
    {
        qDebug()<<queryCmd.lastError();

    }
}


void Widget::AcceptConnect()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    clientSocket->setParent(this);
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(ReadData()));
    //ui->label_3->setText("新连接成功");
}

void Widget::ShowCommand(CCommand cmd)
{
    //    if(cmd.key == 0x60)//温度湿度命令
    //    {
    //        FillTable(cmd,ui->tableWidget);
    //    }

    //    if(cmd.key>= 0x61 && cmd.key <= 0x66)
    //    {
    //        FillTable(cmd,ui->tableWidget_2);
    //    }
}

void Widget::FillTable(CCommand cmd, QTableWidget *table)
{
    //    int count = table->rowCount() + 1;
    //    table->setRowCount(count);
    //    qint8 rowIndex = 0;

    //    //长度
    //    QTableWidgetItem *item = NULL;
    ////    item=new  QTableWidgetItem(QString("%1").arg(cmd.length));
    ////    table->setItem(count-1,rowIndex++,item);

    ////    item = new QTableWidgetItem(QString("%1").arg(cmd.key));
    ////    table->setItem(count-1,rowIndex++,item);

    //    qint8 lineNumber = cmd.key - 0x60;
    //    if(lineNumber == 0)
    //    {
    //    item = new QTableWidgetItem(QString("总机"));
    //    table->setItem(count-1,rowIndex++,item);
    //    }
    //    else
    //    {
    //        item = new QTableWidgetItem(QString("线路%1").arg(lineNumber));
    //        table->setItem(count-1,rowIndex++,item);
    //    }

    //    //类型
    ////    item = new QTableWidgetItem(QString("%1").arg(cmd.type));
    ////    table->setItem(count-1,rowIndex++,item);


    //    item = new QTableWidgetItem(QString("%1").arg(cmd.no));
    //    table->setItem(count-1,rowIndex++,item);

    //    item = new QTableWidgetItem(QString("%1").arg(cmd.cv));
    //    table->setItem(count-1,rowIndex++,item);

    //    item = new QTableWidgetItem(QString("%1").arg(cmd.hi));
    //    table->setItem(count-1,rowIndex++,item);

    //    //时间
    //    item = new QTableWidgetItem(cmd.tm.toString());
    //    table->setItem(count-1,rowIndex++,item);
    //    //校验和
    ////    item = new QTableWidgetItem(QString("%1").arg(cmd.cks));
    ////    table->setItem(count-1,rowIndex,item);
}


void Widget::ReadData()
{
    QTcpSocket * client = qobject_cast<QTcpSocket *>(sender());


    //    wireCmdPackage wireCmd;
    //    int bytes=client->bytesAvailable();
    //    QByteArray cc=client->readAll();;
    //    unsigned char d=cc.at(0);
    //    qDebug()<<"read data"<<cc.toHex()<<bytes<<d;
    //    //this->statusBar()->showMessage(cc.toHex());
    //    //ui->label_3->setText(ui->label_3->text()+"\n"+cc.toHex());

    //    if(cc.endsWith("\n")&&(d==0xfe))
    //    {
    //        QDataStream in(cc);
    //        in.setVersion(QDataStream::Qt_4_0);
    //        qint32 tmp;
    //        in>>tmp;
    //        wireCmd.start=0xfe;
    //        wireCmd.relayNo=tmp&0x00ffffff;
    //        in>>wireCmd.length;
    //        in>>wireCmd.key;
    //        in>>wireCmd.type;
    //        in>>wireCmd.no;
    //        in>>wireCmd.cv;
    //        in>>wireCmd.hi;
    //        in>>wireCmd.cks;
    //        in>>wireCmd.enter;
    //    }

    //    cmd.length = wireCmd.length;
    //    cmd.key = wireCmd.key;
    //    cmd.type = wireCmd.type;
    //    cmd.no = wireCmd.no;
    //    cmd.cv = wireCmd.cv;
    //    cmd.hi = wireCmd.hi;
    //    cmd.cks = wireCmd.cks;
    //    cmd.enter = wireCmd.enter;
    //    cmd.lineNo = cmd.key - 0x60;
    //    /*
    //ui->label_3->setText("数据到达");
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_4_0);

    //收到不完整数据
    int bytes = client->bytesAvailable();
    //ui->label_3->setText(QString("%1").arg(bytes));


    //出错处理
    //QString errData;
    if(bytes != 12)
    {
        //ui->label_4->setText(QString("错误包数量:%1").arg(++errCount));
        qDebug()<<QString::fromWCharArray(L"可用数据：")<<client->bytesAvailable();
        char * errData =  NULL;
        uint len;
        in.readBytes(errData,len);
        qDebug()<<errData<<len;
        delete errData;
        return;
    }
    //读取命令

    // ui->pakageCount->setText(QString("数据包总数量:%1").arg(++pakageCount));
    in>>cmd.length;
    in>>cmd.key;
    in>>cmd.type;
    in>>cmd.no;
    in>>cmd.cv;
    in>>cmd.hi;
    in>>cmd.cks;
    in>>cmd.enter;

    cmd.lineNo = cmd.key-0x60;
    //添加时间
    //cmd.tm = QDateTime::currentDateTime();




    InsertDB();//插入数据库

    //更新设备状态
    UpdataStatursDB(cmd);
    //ui->label_3->setText("成功格式化数据");
    qDebug()<<QString::fromWCharArray(L"可用数据：")<<client->bytesAvailable();
    //this->ShowCommand(cmd);
}

void Widget::on_pushButton_2_clicked()
{
    manager->show();

    //设置弹出窗口的信号到发射数据槽

}

void Widget::on_checkBox_2_clicked(bool checked)
{
    if(!checked)
    {
        ui->detailLable->hide();
        ui->detailTableView->hide();
        ui->detailDate->hide();
        ui->pushButton->hide();
        ui->label_hint->hide();
    }
    else
    {
        ui->detailLable->show();
        ui->detailTableView->show();
        ui->detailDate->show();
        ui->pushButton->show();
        ui->label_hint->show();
    }
}

void Widget::on_devieceStaturs_clicked(bool checked)
{
    if(checked)
    {
        ui->label_8->show();
        //ui->staturs->show();
        ui->tbTableInfo->show();
    }
    else
    {
        ui->label_8->hide();
        ui->tbTableInfo->hide();
        //ui->staturs->hide();
    }
}

void Widget::on_overflow_clicked(bool checked)
{
    if(checked)
    {
        ui->label_overflow->show();
        ui->overData->show();
    }
    else
    {
        ui->label_overflow->hide();
        ui->overData->hide();
    }
}

void Widget::on_dataPic_clicked(bool checked)
{
    if(checked)
    {
        ui->dataWidget->show();
        ui->label_6->show();
        ui->label_7->show();
        ui->no->show();
        ui->dateEdit->show();
        ui->ok->show();
        //ui->dataPic->show();

        ui->label1->show();
        ui->label2->show();
        ui->label3->show();
        ui->label4->show();
        ui->label5->show();
        ui->label6->show();
    }
    else
    {

        ui->dataWidget->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->no->hide();
        ui->dateEdit->hide();
        ui->ok->hide();

        //显示颜色栏
        ui->label1->hide();
        ui->label2->hide();
        ui->label3->hide();
        ui->label4->hide();
        ui->label5->hide();
        ui->label6->hide();
        //ui->dataPic->hide();
    }
}

void Widget::on_pushButton_2_clicked(bool checked)
{
    
}

void Widget::DrawCurve()
{
    ui->dataWidget->clearGraphs();

    //    int test = 1;
    //    int lineCount = 0;


    //    //从数据库中选择数据
    //    QSqlQuery sqlQuery;
    //    sqlQuery.prepare("select 电流大小,时间 from detailinformation WHERE 设备编号 = ? and 线路编号  and 电流大小 is not null ORDER BY 时间");
    //    int no = ui->no->text().toInt();
    //    sqlQuery.bindValue(0,no);

    //    QDateTime tempDateTime;
    //    while (test <7)
    //    {

    //        QString  lineNo =QString("线路%1").arg(test);

    //        sqlQuery.bindValue(1,lineNo);
    //        //sqlQuery.bindValue(2,);
    //        if(0)//!sqlQuery.exec())
    //        {
    //            QMessageBox::information(this,"错误提示",sqlQuery.lastError().text());
    //            return;
    //        }
    //        if(sqlQuery.size() <=0)
    //        {

    //            ++test;
    //            continue;
    //        }
    //        QVector<double> x_vector[7],y_vector[7];


    //        while(sqlQuery.next())
    //        {
    //            //时间匹配
    //            tempDateTime = sqlQuery.value(1).toDateTime();
    //            if(tempDateTime.date() != ui->dateEdit->date())
    //            {
    //                continue;
    //            }

    //            y_vector.push_back(sqlQuery.value(0).toInt());


    //            int sCount = tempDateTime.time().msecsSinceStartOfDay()/1000;//获取时间轴的数值
    //            x_vector.push_back(sCount);
    //        }

    //        ui->dataWidget->addGraph();
    //        ui->dataWidget->graph(lineCount)->addData(x_vector,y_vector);
    //        QPen linePen(color[test-1]);
    //        linePen.setWidth(2);
    //        ui->dataWidget->graph(lineCount)->setPen(linePen);
    //        ui->dataWidget->replot();
    //        ui->dataWidget->repaint();

    //        ++lineCount;
    //      ++test;
    //    }



    //查询数据库
    QSqlQuery query;
    QVector<double> xVector[6],yVector[6];
    QString strDate = ui->dateEdit->dateTime().toString("yyyy-MM-dd");
    query.prepare(QString::fromWCharArray(L"select 线路编号,电流大小,时间 from %1 WHERE 设备编号 = ? and date(时间)=?  and 电流大小 is not null ORDER BY 时间").arg(MeasureDB::mysqlDetailDataTb));
    int no = ui->no->text().toInt();
    query.bindValue(0,no);
    query.bindValue(1,strDate);

    if(!query.exec())
    {
        QMessageBox::critical(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"查询数据库失败"));
        return;
    }

    if(query.size() == 0)
    {
        QMessageBox::critical(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"没有查询到相关数据\r\n请检查您输入的编号及时间"));
        return;
    }
    while(query.next())
    {
        QString lineNo = query.value(0).toString();
        lineNo = lineNo.right(1);
        qint16 line= lineNo.toInt();

        if(line<0||line >5)
            continue;
        QDateTime temp = query.value(2).toDateTime();
        qint32 sCount ;//= temp.time()..msecsSinceStartOfDay()/1000;


        xVector[line - 1].push_back(sCount);

        yVector[line - 1].push_back(query.value(1).toInt()/1000.0f);

    }

    for(int i=0;i!=6;++i)
    {
        ui->dataWidget->addGraph();
        ui->dataWidget->graph(i)->addData(xVector[i],yVector[i]);
        QPen linePen(color[i]);
        linePen.setWidth(2);
        ui->dataWidget->graph(i)->setPen(linePen);
        ui->dataWidget->replot();
        ui->dataWidget->repaint();

    }


    //绘制超限预警线
    QCPGraph *warningLine =  ui->dataWidget->addGraph();
    warningLine->setPen(QPen(QColor(255,0,0)));

    QVector<double> x,y;
    x.push_back(0);
    x.push_back(24*60*60);
    y.push_back(overEelectric/1000.0f);
    y.push_back(overEelectric/1000.0f);
    warningLine->addData(x,y);
    ui->dataWidget->replot();
    ui->dataWidget->repaint();


    //    if(lineCount == 0)
    //    {
    //        //QMessageBox::information(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"未查询到相关数据\n请检查输入的设备及线路是否正确"));
    //    }

}
void Widget::ConnectDB()
{

    //本地测试
#if LOCALDEBUG
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("electricdata");
    db.setUserName("root");
    db.setPassword("123456");
    if( !db.open())
    {
        QMessageBox::critical(this,"错误提示",db.lastError().text());
        //return false;
    }

#else
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("120.25.233.115");
    db.setPort(3306);
    db.setDatabaseName("electricdata");
    db.setUserName("root");
    db.setPassword("mytianjun-mysql");
    if( db.open())
    {
        qDebug()<<QString::fromWCharArray(L"连接数据库成功......")<<db.lastError();
        model=new RailLineSqlModel(ui->tbTableInfo,db);

    }
    else
    {
        QMessageBox::critical(this,QString::fromWCharArray(L"错误提示"),QString::fromWCharArray(L"连接数据库失败\r\n请检查网络连接"));
        //return false;
    }
#endif
}

bool Widget::InsertDB()
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO detailInformation VALUES(:no,:lineNo,:v,:i,:c,:h,now())");

    sqlQuery.bindValue(":no",cmd.no);


    if(cmd.lineNo == 0)
    {
        sqlQuery.bindValue(":lineNo",QString::fromWCharArray(L"总机"));
        //sqlQuery.bindValue(":v",0);
        //sqlQuery.bindValue(":i",0);
        sqlQuery.bindValue(":c",cmd.cv);
        sqlQuery.bindValue(":h",cmd.hi);
    }
    else
    {
        sqlQuery.bindValue(":lineNo",QString::fromWCharArray(L"线路%0").arg(cmd.lineNo));
        sqlQuery.bindValue(":v",cmd.cv);
        sqlQuery.bindValue(":i",cmd.hi);
        //sqlQuery.bindValue(":c",0);
        //sqlQuery.bindValue(":h",0);
    }
    bool b=sqlQuery.exec();
    if(b)
    {
        ShowDB();
        qDebug()<<"写入数据库成功";
    }
    return b;
}

void Widget::ShowOverData()
{
    //    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    //    queryModel->setQuery("select 设备编号,线路编号,电压,电流,时间 from detailinformation ");
    //    ui->overData->setModel(queryModel);
    QSqlQuery query;
    query.prepare(QString::fromWCharArray(L"select 设备编号,线路编号,电压大小,电流大小,时间 from detailInformation WHERE 电流大小>?"));
    query.bindValue(0,overEelectric);
    query.exec();
    QSqlQueryModel * queryModel = new QSqlQueryModel(this);
    queryModel->setQuery(query);
    ui->overData->setModel(queryModel);
    ui->overData->resizeColumnsToContents();
}

void Widget::ShowDB()
{
    //详细信息视图的显示
    qDebug()<<"ShowDB() called";
    QSqlQueryModel * queryModel = new QSqlQueryModel(this);
    QSqlQuery query;
    QString strDate = ui->detailDate->date().toString("yyyy-MM-dd");
//    query.prepare(QString::fromWCharArray(L"SELECT detailinformation.设备编号,detailinformation.线路编号,线路名称,电压大小 电压（mV）,电流大小 电流（mA）,温度大小 '温度（0.01度）',湿度大小 '湿度(0.001\%)' ,时间 FROM detailInformation ,linesAliase WHERE date(时间) = ? AND detailinformation.设备编号 = linesAliase.设备编号 AND detailinformation.线路编号 = linesAliase.线路编号 "));
//    query.prepare(QString::fromWCharArray(L"SELECT %1.deviceNO,%2.lineNo,线路名称,voltage,current,temperature,humidity,tm FROM %3 ,linesAliase WHERE tm = ? AND %4.deviceNo = linesAliase.deviceNo AND %5.lineNo = linesAliase.lineNo ")).arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb);
//    query.prepare(QString::fromWCharArray(L"SELECT %1.deviceNO,%2.lineNo,voltage,current,temperature,humidity,tm FROM %3 ,linesAliase WHERE tm = ? AND %4.deviceNo = linesAliase.deviceNo AND %5.lineNo = linesAliase.lineNo ").arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb).arg(MeasureDB::mysqlDetailDataTb));
//    query.bindValue(0,strDate);
//    if(!query.exec())
//    {
//        if(query.lastError().number() == 2006)
//            QMessageBox::information(this,QString::fromWCharArray(L"错误"),QString::fromWCharArray(L"网络连接已断开"));
//        qDebug()<<"query not data";
//    }
//    else
//    {
//        qDebug()<<"query data";
//    }
    QString strSql=QString::fromWCharArray(L"SELECT * from %1").arg(MeasureDB::mysqlDetailDataTb);
    qDebug()<<"sql str="<<strSql<<
    query.exec(strSql);
    queryModel->setQuery(query);
    ui->detailTableView->setModel(queryModel);
//    ui->detailTableView->
//    ui->detailTableView->setVerticalHeader();
    ui->detailTableView->resizeColumnsToContents();
    qDebug()<<"table is ok"<<queryModel->lastError().text();

    //设备状态视图的显示
    //    QSqlQueryModel *queryDevieceStaturs = new QSqlQueryModel();
    //    queryModel->setQuery("select * from devieceStaturs");
    //    ui->tbTableInfo->setModel(queryDevieceStaturs);
}
void Widget::showTables(QString  tableName)
{
        if(!model->database().isOpen())
            model->database().open();
        model->setEditStrategy(QSqlTableModel::OnRowChange);
        model->setTable(tableName);
    //    qDebug()<<"cur table name="<<model->tableName();
        model->setFilter(QString("id>0"));
        model->setSort(0,Qt::AscendingOrder);
        model->select();
        for(int i=0;i<xlsTitleName.split(',').count();i++)
        {
            QString tmp=xlsTitleName.split(',').at(i);
            model->setHeaderData(i,Qt::Horizontal, QString(tmp.left(tmp.length()-1)));
        }

        while (model->canFetchMore())
        {
            model->fetchMore();
        }
      ui->tbTableInfo->setModel(model);
        ui->tbTableInfo->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        //    qDebug()<<"row count"<<model->rowCount();


        ui->tbTableInfo->selectRow(model->rowCount()-1);

        for(int i=0;i<xlsTitleName.split(',').count();i++)
        {
            QString tmp=xlsTitleName.split(',').at(i);
            if(!tmp.right(1).toInt())
            {
                //            qDebug()<<"display flag"<<i<<tmp.right(1).toInt();
                ui->tbTableInfo->setColumnHidden(i,true);//x倾角
            }
        }
}
void Widget::ShowStaturs()
{
    QSqlQueryModel * queryModel = new QSqlQueryModel(this);
    queryModel->setQuery(QString::fromWCharArray(L"select * from devieceStaturs"));
    ui->tbTableInfo->setModel(queryModel);
    ui->tbTableInfo->resizeColumnsToContents();
}

void Widget::UpdataStatursDB(CCommand cmd)
{
    QSqlQuery queryStaturs;
    if(cmd.lineNo == 0)
    {
        //更新温度湿度
        queryStaturs.prepare(QString::fromWCharArray(L"UPDATE devieceStaturs SET 温度= ? ,湿度 = ?,最近更新时间 = now() WHERE 设备编号 = ?"));
        queryStaturs.bindValue(0,cmd.cv);
        queryStaturs.bindValue(1,cmd.hi);
        queryStaturs.bindValue(2,cmd.no);
    }

    else
    {
        //更新电压电流
        switch (cmd.lineNo)
        {
        case 1:
            queryStaturs.prepare(QString::fromWCharArray(L"UPDATE devieceStaturs SET 线路1= ?,电源剩余= ?  WHERE 设备编号 = ?"));
            break;
        case 2:
            queryStaturs.prepare(QString::fromWCharArray(L"UPDATE devieceStaturs SET 线路2= ?,电源剩余= ?  WHERE 设备编号 = ?"));
            break;
        case 3:
            queryStaturs.prepare(QString::fromWCharArray(L"UPDATE devieceStaturs SET 线路3= ?,电源剩余= ?  WHERE 设备编号 = ?"));
            break;
        case 4:
            queryStaturs.prepare(QString::fromWCharArray(L"UPDATE devieceStaturs SET 线路4= ?,电源剩余= ?  WHERE 设备编号 = ?"));
            break;
        case 5:
            queryStaturs.prepare(QString::fromWCharArray(L"UPDATE devieceStaturs SET 线路5= ?,电源剩余= ?  WHERE 设备编号 = ?"));
            break;
        case 6:
            queryStaturs.prepare(QString::fromWCharArray(L"UPDATE devieceStaturs SET 线路6= ?,电源剩余= ?  WHERE 设备编号 = ?"));
            break;
        default:
            break;
        }
        queryStaturs.bindValue(0,cmd.hi);
        queryStaturs.bindValue(1,(cmd.cv-3500)/10);
        queryStaturs.bindValue(2,cmd.no);
    }

    if(!queryStaturs.exec())
    {

        QMessageBox::information(this,QString::fromWCharArray(L"错误"),queryStaturs.lastError().text());

    }
    else
    {
        ShowStaturs();
    }

}



void Widget::on_ok_clicked()
{
    if(ui->no->text().isEmpty())
    {
        QMessageBox::critical(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"请输入设备编号"));
    }
    else
    {
        DrawCurve();
    }
}

void Widget::on_pushButton_refresh_clicked()
{
    ShowDB();
    ShowStaturs();
    ShowOverData();
}
#if EXPAND
void Widget::on_start_clicked(bool checked)
{
        if(checked)
        {
            if(ui->ip->text().isEmpty()||ui->port->text().isEmpty())
            {
                QMessageBox::information(this,"提示","ip和端口号不能为空");
                return;
            }
            tcpServer = new QTcpServer(this);
            bool res = tcpServer->listen(QHostAddress(ui->ip->text()),ui->port->text().toInt());
            if(res)
            {
               //连接成功
                connect(tcpServer,SIGNAL(newConnection()),this,SLOT(AcceptConnect()));
                //ui->label_3->setText("开启服务器成功");

                //包的总数量为0
                pakageCount = 0;
                errCount = 0;

                 ui->start->setText("关闭服务器");
            }
            else
            {
                QMessageBox::warning(this,"错误","开启失败，请检查端口号和地址是否正确");
                ui->start->setChecked(false);//设置为来继续开启服务器
            }
        }
        else
        {
            tcpServer->close();
            ui->start->setText("开启服务器");
        }
}
void Widget::on_exportData_clicked()
{
    QFile file("detailInformation.txt");
    if(!file.open(QFile::ReadWrite|QFile::Text))
    {
        qDebug()<<QString::fromWCharArray(L"打开文件失败");
    }
    QTextStream out(&file);
    out<<"test"<<"\r\n";
    out<<"sucessed";
    file.close();
}
#endif
void Widget::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"您确定退出应用程序吗")) == QMessageBox::No)
        event->ignore();
    else
    {
        if(tcpServer)
            tcpServer->close();
    }

}

void Widget::on_pushButton_clicked()
{
    //ui->label_hint->setText("正在加载数据,请稍候……");
    ui->label_hint->setEnabled(false);
    ShowDB();
    ui->label_hint->setEnabled(true);
}

void Widget::on_dataPic_clicked()
{

}
