#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    manager(NULL),
    deviceInfoModel(NULL),
    detectDataModel(NULL),
    overDataModel(NULL),
    localDb(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readConfigure();
    uiInitial();
    localDb =new MeasureDB("./wireDetectDb.db");
    if(localDb)
    {
        deviceInfoModel=new RailLineSqlModel(ui->tbTableInfo,localDb->currDatabase());
        detectDataModel=new RailLineSqlModel(ui->tbDetail,localDb->currDatabase());
        overDataModel=new RailLineSqlModel(ui->tbOverData,localDb->currDatabase());
    }

    connect2MysqlDb();
    curveInitial();

    connect(ui->cb1,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb2,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));

    connect(ui->cb3,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb4,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb5,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb6,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));

    //设置表格为只读模式
    ui->tbOverData->setEditTriggers(/*QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|*/QAbstractItemView::NoEditTriggers);
    ui->tbTableInfo->setEditTriggers(/*QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|*/QAbstractItemView::NoEditTriggers);

//    ui->tbDetail->setEditTriggers(/*QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|*/QAbstractItemView::NoEditTriggers);

    ui->cmbLine->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
    connect(ui->ptnbDeviceDelete,SIGNAL(clicked()),this,SLOT(slot_deviceStautsControl()));
    connect(ui->ptnbDeviceInfoUpdate,SIGNAL(clicked()),this,SLOT(slot_deviceStautsControl()));
    connect(ui->ptnbDeviceAdd,SIGNAL(clicked()),this,SLOT(slot_deviceStautsControl()));
    updateDeviceNo();
    ShowDB(false);
    ShowOverData();
    ShowStaturs();
    updateDatabase(true);
}
//函数功能：
void MainWindow::readConfigure(void)
{
    QSettings  settings("Config.ini", QSettings::IniFormat);
    ui->lnbOverCur->setText(QString::number(settings.value("par/constAlarm", 1).toFloat()));
    int tmp=settings.value("par/updateTime", 1).toInt();
    if(tmp==0)
    {
        updateInterval=10;
    }
    else
    {
        updateInterval=tmp;
    }
    qDebug()<<"update interval"<<updateInterval<<" minutes"<<tmp;
}
void MainWindow::setConfigure(void)
{
    QSettings  settings("Config.ini", QSettings::IniFormat);
    settings.setValue("par/constAlarm", ui->lnbOverCur->text().toFloat());
}
void MainWindow::updateDeviceNo(void)
{
    deviceNos.clear();
    QStringList cc=getALLDeviceNo();
    //    qDebug()<<"cc device no"<<cc;
    ui->cmbDeviceNo_2->clear();
    ui->cmbDeviceNo_2->addItem("ALL");
    ui->cmbDeviceNo_2->addItems(cc);
}


QStringList MainWindow::getALLDeviceNo(void)
{
    QSqlQuery query(localDb->currDatabase());
    //    qDebug()<<"db status"<<db_mysql.isOpen();
    QString strSql=QString("Select distinct deviceNo from %1 ").arg(MeasureDB::detailDataTb);
    QStringList deviceNo;
    QStringList deviceAddr;
    if(query.exec(strSql))
    {
        while(query.next())
        {
            deviceNo<<query.value(0).toString();
        }
    }
    //    qDebug()<<"device count"<<deviceNo<<deviceNo.count();
    lineNos.clear();
    for(int i=0;i<deviceNo.count();i++)
    {
        strSql=QString("select deviceAddr,line1,line2,line3,line4,line5,line6 from %1 where deviceNo='%2'").arg(MeasureDB::deviceInfoTb).arg(deviceNo.at(i));
        //        qDebug()<<"str buffer="<<strSql;
        if(query.exec(strSql))
        {
            while(query.next())
            {
                QString tmp=query.value(0).toString();
                if(tmp.isNull())
                {

                    deviceAddr<<deviceNo.at(i);
                    tmp=deviceNo.at(i);
                }
                else
                {
                    deviceAddr<<tmp;
                }
                QPair<int,QVector<QString> >  lineNo;
                for(int j=1;j<7;j++)
                {
                    lineNo.second<<query.value(j).toString();
                }
                deviceNos<<QPair<QString ,QString > (tmp,deviceNo.at(i));
                lineNo.first=deviceNos.count();
                lineNos<<lineNo;
                //qDebug()<<"addr device no"<<query.value(0).toString()<<deviceNo.at(i);
            }
        }
    }
    //    qDebug()<<"all device info="<<deviceNos.count()<<lineNos.count();
    //    for(int i=0;i<lineNos.count();i++)
    //    {
    //        qDebug()<<i<<lineNos.at(i).first<<lineNos.at(i).second<<deviceNos.at(i).second;
    //    }
    return deviceAddr;
}
void MainWindow::updateLineNo(QString strDevice)
{

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::curveInitial(void)
{
    //曲线插件设置
    ui->dataWidget->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->dataWidget->xAxis->setLabel(QString::fromWCharArray(L"时间"));
    ui->dataWidget->yAxis->setLabel(QString::fromWCharArray(L"电流大小"));
    ui->dataWidget->xAxis->setRange(0,24*60*60);
    connect(ui->dataWidget,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(MouseWheel()));
    //    ui->dataWidget->yAxis->setRange(0,100);

    QCPAxisTickerTime *tickerDateTime = new QCPAxisTickerTime;
    //    tickerDateTime->setTimeFormat(QString::fromWCharArray(L"%月%日%h点:%m分"));

    tickerDateTime->setTimeFormat(QString::fromWCharArray(L"%h点:%m分"));

    QSharedPointer<QCPAxisTickerTime> sharedTicker(tickerDateTime);

    ui->dataWidget->xAxis->setTicker(sharedTicker);
    //    qDebug()<<"ticker "<<sharedTicker.
}
void MainWindow::uiInitial(void)
{
    //设置曲线颜色
    color.push_back(QColor(0,125,125));
    color.push_back(QColor(0,0,255));
    color.push_back(QColor(0,255,0));
    color.push_back(QColor(0,255,255));
    color.push_back(QColor(255,0,255));
    color.push_back(QColor(255,125,0));
    //    this->addAction(ui->deviceManager);
    ;
    for(int i=0;i<CURVE_NUMBERS;i++)
    {
        //if(curveInfos[i].curveIndex==-1)
        {
            ui->dataWidget->addGraph();
            curveInfos[i].curveIndex=ui->dataWidget->graphCount()-1;
            curveInfos[i].color=color.at(i);
            ui->dataWidget->graph( curveInfos[i].curveIndex)->setPen(QPen( curveInfos[i].color));
        }
    }
    //设置默认界面
    //    ui->checkBox_2->setChecked(true);
    ui->overflow->setChecked(true);
    ui->devieceStaturs->setChecked(true);

    ui->gbCurve->hide();
    //    this->setWindowTitle(QString::fromWCharArray(L"高压线路在线检测智能预警系统V1.1-四川信达轨道交通设备有限责任公司"));
    //    this->setWindowTitle(QString::fromWCharArray(L"高压线路在线检测智能预警系统V1.2-1009-四川信达轨道交通设备有限责任公司"));
    this->setWindowTitle(QString::fromWCharArray(L"高压电缆屏铠接地智能在线监测系统-1009-四川信达轨道交通设备有限责任公司"));

    ui->dataWidget->addGraph();

    ui->dataWidget->addGraph();
    ui->dataWidget->addGraph();
    ui->dataWidget->addGraph();
    ui->dataWidget->addGraph();
    ui->dataWidget->addGraph();

    ui->cb1->setCheckState(Qt::Checked);
    ui->cb2->setCheckState(Qt::Checked);
    ui->cb3->setCheckState(Qt::Checked);
    ui->cb4->setCheckState(Qt::Checked);
    ui->cb5->setCheckState(Qt::Checked);
    ui->cb6->setCheckState(Qt::Checked);
    remoteDbStatus=new DeviceStatus(QString::fromWCharArray(L"远程数据库"),DISCONNECTED,this);
    lblLocalRecordCounts=new QLabel(this);
    ui->statusbar->addPermanentWidget(lblLocalRecordCounts);
    ui->statusbar->addPermanentWidget(remoteDbStatus);

    //    updateRecordStatus=new DeviceStatus(QString::fromWCharArray(L"数据同步"),DISCONNECTED,this);
    //    ui->statusbar->addPermanentWidget(updateRecordStatus);

    ui->date->setDateTime(QDateTime::currentDateTime());
    timer=new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_updateData()));

    timer->start(updateInterval*60*1000);//s
#if 0
    manager = new CDeviceManager(this);
    connect(manager,SIGNAL(SetDevice(qint16,QByteArray)),this,SLOT(SendData(qint16,QByteArray)));
    manager->SetDB(db_mysql);
    connect(manager,SIGNAL(AddDevice(qint16,QString,QString,QDateTime)),this,SLOT(AddDeviece(qint16,QString,QString,QDateTime)));
    connect(manager,SIGNAL(DeleteDeviece(qint16)),this,SLOT(DeleteDeviece(qint16)));
    connect(manager,SIGNAL(SetDevice(qint16,QByteArray)),this,SLOT(SendData(qint16,QByteArray)));
#endif
}

void MainWindow::SetBack()
{
    QPixmap pixmap = QPixmap(":/images/images/bk.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(this->backgroundRole(),QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
}

void MainWindow::MouseWheel()
{
    if (ui->dataWidget->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->dataWidget->axisRect()->setRangeZoom(ui->dataWidget->xAxis->orientation());
    else if (ui->dataWidget->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->dataWidget->axisRect()->setRangeZoom(ui->dataWidget->yAxis->orientation());
    else
        ui->dataWidget->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::DeleteDeviece(qint16 no)
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

void MainWindow::AddDeviece(qint16 no, QString owner, QString position, QDateTime dateTime)
{
    qDebug()<<"AddDeviece called!";
    ShowStaturs();
}

void MainWindow::SendData(qint16 no, QByteArray cmd)
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

void MainWindow::on_devieceStaturs_clicked(bool checked)
{
    if(checked)
    {
        ui->groupBox->show();
    }
    else
    {
        ui->groupBox->hide();
    }
}
void MainWindow::on_overflow_clicked(bool checked)
{
    if(checked)
    {
        ui->groupBox_2->show();

    }
    else
    {
        ui->groupBox_2->hide();
    }
}

void MainWindow::on_dataPic_clicked(bool checked)
{
    if(checked)
    {

        ui->gbCurve->show();
    }
    else
    {
        ui->gbCurve->hide();


        //ui->dataPic->hide();
    }
}
void MainWindow::DrawCurve()
{
    QString tmp("");
    if(!ui->cmbDeviceNo_2->currentText().contains("ALL"))
    {
        for(int i=0;i<CURVE_NUMBERS;i++)
            curveInfos[i].clear();

        if(deviceNos.count())
        {
            int curIndex=0;
            for(int i=0;i<deviceNos.count();i++)
            {
                if(deviceNos.at(i).first.contains(ui->cmbDeviceNo_2->currentText()))
                {
                    curIndex=i;
                    break;
                }
            }
            if(ui->cmbLine->currentText().contains("ALL"))
            {
                tmp=QString("deviceNo='%1'").arg(deviceNos.at(curIndex).second);
            }
            else
            {
                tmp=QString("deviceNo='%1'").arg(deviceNos.at(curIndex).second);
                tmp.append(QString(" and lineNo =%1").arg(ui->cmbLine->currentIndex()));
            }

            tmp.append(QString(" and tm like '%1%' ").arg(ui->date->dateTime().toString("yyyy-MM-dd")));


            QString strSql=QString("select lineNo,tm,current from %1 where %2").arg(MeasureDB::detailDataTb).arg(tmp);
            QSqlQuery query(localDb->currDatabase());
            qDebug()<<"string sql"<<strSql<<ui->date->dateTime().toString("yy-MM-dd");
            if(query.exec(strSql))
            {
                qDebug()<<"i get the record";
                while(query.next())
                {
                    if(query.value(2).toFloat())
                    {
                        QDateTime temp = query.value(1).toDateTime();
                        qint32 sCount = temp.time().msecsSinceStartOfDay()/1000;
                        int lineNo=query.value(0).toInt()-1;
                        //                    qDebug()<<"timer"<<temp<<curveInfos[lineNo].x.count()<<sCount<<query.value(2).toFloat();
                        if(lineNo<CURVE_NUMBERS)
                        {
                            curveInfos[lineNo].x<<sCount;
                            curveInfos[lineNo].y<<query.value(2).toFloat();
                        }
                        else
                        {
                            qDebug()<<"line index is out of memory";
                        }
                    }
                }
            }
            for(int i=0;i<CURVE_NUMBERS;i++)
            {
                //            if(curveInfos[i].y.count())
                ui->dataWidget->graph(curveInfos[i].curveIndex)->setData(curveInfos[i].x,curveInfos[i].y);
            }
            ui->dataWidget->replot();
        }
        else
        {
            qDebug()<<"device number is null";
        }
    }
}
void MainWindow::connect2MysqlDb()
{
    //本地测试
#if LOCALDEBUG
    db_mysql = QSqlDatabase::addDatabase("QMYSQL");
    db_mysql.setHostName("127.0.0.1");
    db_mysql.setPort(3306);
    db_mysql.setDatabaseName("electricdata");
    db_mysql.setUserName("root");
    db_mysql.setPassword("123456");
    if( !db_mysql.open())
    {
        QMessageBox::critical(this,"错误提示",db_mysql.lastError().text());
        //return false;
    }

#else
    db_mysql = QSqlDatabase::addDatabase("QMYSQL");
    db_mysql.setHostName("120.25.233.115");
    db_mysql.setPort(3306);
    db_mysql.setDatabaseName("electricdata");
    db_mysql.setUserName("root");
    db_mysql.setPassword("mytianjun-mysql");
    if( db_mysql.open())
    {
        remoteDbStatus->setCurStatus(CONNECTED);
        //        ui->statusbar->showMessage(QString::fromWCharArray(L"连接数据库成功......"));
        //        deviceInfoModel=new RailLineSqlModel(ui->tbTableInfo,db_mysql);
        //        detectDataModel=new RailLineSqlModel(ui->tbDetail,db_mysql);
        //        overDataModel=new RailLineSqlModel(ui->tbOverData,db_mysql);
    }
    else
    {
        remoteDbStatus->setCurStatus(DISCONNECTED);
        QMessageBox::critical(this,QString::fromWCharArray(L"错误提示"),QString::fromWCharArray(L"连接数据库失败\r\n请检查网络连接"));
        ui->statusbar->showMessage(QString::fromWCharArray(L"连接数据库成功......")+db_mysql.lastError().text());
    }
#endif
}

void MainWindow::ShowOverData()
{
    //    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    //    queryModel->setQuery("select 设备编号,线路编号,电压,电流,时间 from detailinformation ");
    //    ui->tbOverData->setModel(queryModel);
#if 0
    QSqlQuery query;
    query.prepare(QString::fromWCharArray(L"select 设备编号,线路编号,电压大小,电流大小,时间 from detailInformation WHERE 电流大小>?"));
    query.bindValue(0,overEelectric);
    query.exec();
    QSqlQueryModel * queryModel = new QSqlQueryModel(this);
    queryModel->setQuery(query);
    ui->tbOverData->setModel(queryModel);
    ui->tbOverData->resizeColumnsToContents();
#else

    QString tmp=ui->cmbDeviceNo_2->currentText();
    QString strFilter("");

    if(tmp.contains("ALL"))
    {
        ui->cmbLine->clear();
        ui->cmbLine->addItem("ALL");
        strFilter=QString("current>%1").arg(ui->lnbOverCur->text().toFloat());
    }
    else
    {
        for(int i=0;i<deviceNos.count();i++)
        {
            QString cc=deviceNos.at(i).first;
            if(cc.contains(tmp))
            {
                QString tmpLine=ui->cmbLine->currentText();
                int tmpIndex=ui->cmbLine->currentIndex();
                if(tmpLine.contains("ALL"))
                {
                    strFilter=QString("deviceNo='%1'").arg(deviceNos.at(i).second);
                }
                else
                {
                    strFilter=QString("deviceNo='%1' and lineNo='%2'").arg(deviceNos.at(i).second).arg(tmpIndex);
                }
            }
        }
        if(strFilter.contains("deviceNo"))
        {
            strFilter.append(QString(" and current>%1").arg(ui->lnbOverCur->text().toFloat()));
        }
    }

    //    qDebug()<<"over filter="<<strFilter;
    showDetailData(overDataModel,ui->tbOverData,strFilter);
#endif
}
void MainWindow::ShowDB(bool f)
{
    showDetailData(detectDataModel,ui->tbDetail->tableView,"id>0",f);
}
void MainWindow::showDetailData(RailLineSqlModel *model,QTableView *tableview,QString filter,bool f,QString  tableName,QString title)
{
    QTime timer;
    timer.start();
#if 1
    if(!model->database().isOpen())
        model->database().open();
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable(tableName);
    if(!f)
        filter=QString("tm like '%1%'").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    qDebug()<<"detail table filer"<<filter<<tableName<<title<<title.split(',').count();
    model->setFilter(filter);
    //    model->setSort(0,Qt::AscendingOrder);
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    for(int i=0;i<title.split(',').count();i++)
    {
        QString tmp=title.split(',').at(i);
        model->setHeaderData(i,Qt::Horizontal, QString(tmp.left(tmp.length()-1)));
        qDebug()<<"head string"<<i<<(title.split(',').at(i))<<tmp.length();
    }
//    while (model->canFetchMore())
//    {
//        model->fetchMore();
//    }
    qDebug()<<"show filter";
    tableview->setModel(model);
    tableview->selectRow(model->rowCount()-1);
    for(int i=0;i<title.split(',').count();i++)
    {
        QString tmp=title.split(',').at(i);
        qDebug()<<"tmp string"<<i<<tmp;
        if(tmp.count())
        {
            if(!tmp.right(1).toInt())
            {
                qDebug()<<"display flag"<<i<<tmp.right(1).toInt();
                tableview->setColumnHidden(i,true);//x倾角
            }
        }
        else
        {
            qDebug()<<i<<"cur title error"<<tmp;
        }
    }
#else
    qDebug()<<"ShowDB() called";
    QSqlQueryModel * queryModel = new QSqlQueryModel(this);
    QSqlQuery query;
    QString strSql=QString::fromWCharArray(L"SELECT * from %1").arg(MeasureDB::mysqlDetailDataTb);
    qDebug()<<"sql str="<<strSql<<
              query.exec(strSql);
    queryModel->setQuery(query);
    ui->tbDetail->setModel(queryModel);
    //    ui->detailTableView->
    //    ui->detailTableView->setVerticalHeader();
    ui->tbDetail->resizeColumnsToContents();
    qDebug()<<"table is ok"<<queryModel->lastError().text();
#endif
    qDebug()<<"time="<<timer.elapsed();
}
void MainWindow::showDeviceStatus(QString  tableName)
{
    if(!deviceInfoModel->database().isOpen())
        deviceInfoModel->database().open();
    deviceInfoModel->setEditStrategy(QSqlTableModel::OnRowChange);
    //    deviceInfoModel->set

    deviceInfoModel->setTable(tableName);
    //    qDebug()<<"cur table name="<<deviceInfoModel->tableName();
    //        deviceInfoModel->setFilter(QString("group by deviceNo"));
    deviceInfoModel->setSort(0,Qt::AscendingOrder);
    deviceInfoModel->select();
    for(int i=0;i<MeasureDB::deviceInfoTitle.split(',').count();i++)
    {
        QString tmp=MeasureDB::deviceInfoTitle.split(',').at(i);
        deviceInfoModel->setHeaderData(i,Qt::Horizontal, QString(tmp.left(tmp.length()-1)));
    }

    while (deviceInfoModel->canFetchMore())
    {
        deviceInfoModel->fetchMore();
    }

    ui->tbTableInfo->setModel(deviceInfoModel);

    //    qDebug()<<"row count"<<deviceInfoModel->rowCount();
    ui->tbTableInfo->selectRow(deviceInfoModel->rowCount()-1);

    for(int i=0;i<MeasureDB::deviceInfoTitle.split(',').count();i++)
    {
        QString tmp=MeasureDB::deviceInfoTitle.split(',').at(i);
        if(!tmp.right(1).toInt())
        {
            //            qDebug()<<"display flag"<<i<<tmp.right(1).toInt();
            ui->tbTableInfo->setColumnHidden(i,true);//x倾角
        }
    }
}
void MainWindow::ShowStaturs()
{
#if 0
    QSqlQueryModel * queryModel = new QSqlQueryModel(this);
    queryModel->setQuery(QString::fromWCharArray(L"select * from devieceStaturs"));
    ui->tbTableInfo->setModel(queryModel);
    ui->tbTableInfo->resizeColumnsToContents();
#else
    showDeviceStatus(MeasureDB::deviceInfoTb);
#endif
}

void MainWindow::UpdataStatursDB(CCommand cmd)
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"您确定退出应用程序吗")) == QMessageBox::No)
        event->ignore();
}
//函数功能：数据筛选刷新
void MainWindow::on_pbtnDetailUpdate_clicked()
{
    //ui->label_hint->setText("正在加载数据,请稍候……");
    //    ui->label_hint->setEnabled(false);

    //    ShowDB();
    //    ui->label_hint->setEnabled(true);
    setCursor(QCursor(Qt::WaitCursor));
    QString tmp=ui->cmbDeviceNo_2->currentText();
    QString strFilter("");

    if(tmp.contains("ALL"))
    {
        showDetailData(detectDataModel,ui->tbDetail->tableView,"id>0");
        ui->cmbLine->clear();
        ui->cmbLine->addItem("ALL");
    }
    else
    {
        for(int i=0;i<deviceNos.count();i++)
        {
            QString cc=deviceNos.at(i).first;
            qDebug()<<"first"<<cc.toInt()<<cc;
            if(cc.contains(tmp))
            {
                QString tmpLine=ui->cmbLine->currentText();
                int tmpIndex=ui->cmbLine->currentIndex();
                if(tmpLine.contains("ALL"))
                {
                    strFilter=QString("deviceNo='%1'").arg(deviceNos.at(i).second);
                }
                else
                {
                    strFilter=QString("deviceNo='%1' and lineNo=%2").arg(deviceNos.at(i).second).arg(tmpIndex);
                }
            }
        }
        qDebug()<<"detatil filter="<<strFilter;
        showDetailData(detectDataModel,ui->tbDetail->tableView,strFilter);
    }

    ShowOverData();
    DrawCurve();
    setConfigure();
    setCursor(QCursor(Qt::ArrowCursor));
}
void MainWindow::slot_deviceStautsControl()
{
    QPushButton * pbtn=(QPushButton * )this->sender();
    bool sqlFlag;
    QSqlQuery query(localDb->currDatabase());

    QString strSql("");
    if(pbtn==ui->ptnbDeviceInfoUpdate)
    {
        loginDlg logUi(this,false);

        if(!logUi.exec())
        {
            this->statusBar()->showMessage(QString::fromWCharArray(L"更新操作，登陆错误..."));
            return;
        }
        if(logUi.bDevcieNo)
        {
            QString curDeviceNo=ui->lneDeviceNo->text();
            QString strTmpSql=QString("select deviceNo from %1").arg(MeasureDB::deviceInfoTb);
            qDebug()<<"sql ="<<strTmpSql;
            if( query.exec(strTmpSql))
            {
                qDebug()<<"i get the table";
                QStringList alreadDevcieNo;
                int deviceNoIndex=query.record().indexOf("deviceNo");
                if(deviceNoIndex!=(-1))
                {
                    while(query.next())
                    {
                        alreadDevcieNo<< query.value(0).toString();
                    }
                }
                else
                {
                    qDebug()<<"tb is not contain deviceNO";
                    return;
                }
                qDebug()<<"cur device no"<<curDeviceNo<<"already="<<alreadDevcieNo;
                if(alreadDevcieNo.contains(curDeviceNo))
                {
                    QMessageBox::about(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"设备编号已经存在"));
                    return;
                }
                else if((curDeviceNo.length()!=10))
                {
                    qDebug()<<"cur device no"<<curDeviceNo<<curDeviceNo.count();
                    QMessageBox::about(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"请输入正确格式的设备编号"));
                }
                else
                {
                    strSql=QString("insert into %1 (deviceNo) values('%2') ").arg(MeasureDB::deviceInfoTb).arg(curDeviceNo);
                }
            }
            else
                qDebug()<<"i not get the table" ;
            mysql_updateDeviceNo(true);
        }
        else
        {
            qDebug()<<"update local database";
            strSql=QString("update %11 set deviceAddr='%1',department='%2',position='%3',line1='%4',line2='%5',line3='%6',line4='%7',line5='%8',line6='%9' where deviceNo=\'%10\'")
                    .arg(ui->lneDeviceAbbr->text())
                    .arg(ui->lneDepartment->text())
                    .arg(ui->lnePosition->text())
                    .arg(ui->line1->text())
                    .arg(ui->line2->text())
                    .arg(ui->line3->text())
                    .arg(ui->line4->text())
                    .arg(ui->line5->text())
                    .arg(ui->line6->text())
                    .arg(ui->lneDeviceNo->text())
                    .arg(MeasureDB::deviceInfoTb);
            mysql_updateDeviceNo(false);
        }
    }
    else if(pbtn==ui->ptnbDeviceDelete)
    {
        loginDlg logUi(this,false);
        if(!logUi.exec())
        {
            this->statusBar()->showMessage(QString::fromWCharArray(L"删除操作，登陆错误..."));
            return;
        }
        strSql=QString("delete from %1 where deviceNo='%2'").arg(MeasureDB::deviceInfoTb).arg(ui->lneDeviceNo->text());

        qDebug()<<"mysql delete device no"<<   mysql_deleteDeviceNo()<<ui->lneDeviceNo->text();
    }
    else if(pbtn==ui->ptnbDeviceAdd)
    {
        QStringList cc=getALLDeviceNo();
        qDebug()<<"alread device number"<<cc<<ui->lneDeviceNo->text();
        if(cc.contains(ui->lneDeviceNo->text()))
        {
            this->statusBar()->showMessage(QString::fromWCharArray(L"已包含该设备编号.."));
            return ;
        }
        else
        {
            if((ui->lneDeviceNo->text().length()!=10))
            {

                this->statusBar()->showMessage(QString::fromWCharArray(L"请输入正确格式的设备编号"));
                return ;
            }
            loginDlg logUi(this,false);
            if(!logUi.exec())
            {
                this->statusBar()->showMessage(QString::fromWCharArray(L"添加操作，登陆错误..."));
                return;
            }
            strSql=QString("insert into %1 (deviceNo) values('%2')").arg(MeasureDB::deviceInfoTb).arg(ui->lneDeviceNo->text());
            qDebug()<<"mysql add device no"<<mysql_addDeviceNo()<<ui->lneDeviceNo->text();
        }
        //        qDebug()<<"add device no"<<strSql;
    }
    sqlFlag=query.exec(strSql);
    if(sqlFlag)
    {
        this->statusBar()->showMessage(QString::fromWCharArray(L"更新成功..."));
    }
    else
    {
        this->statusBar()->showMessage(QString::fromWCharArray(L"更新失败..."));
    }
    qDebug()<<"insert ="<<sqlFlag<<strSql;

    ShowStaturs();
    updateDeviceNo();
}
void MainWindow::on_tbTableInfo_clicked(const QModelIndex &index)
{

    QSqlRecord record=deviceInfoModel->record(index.row());
    nIndex=record.value(record.indexOf("id")).toInt();
    //    qDebug()<<"index="<<nIndex;
    ui->lneDepartment->setText(record.value(record.indexOf("department")).toString());
    ui->lnePosition->setText(record.value(record.indexOf("position")).toString());
    ui->lneDeviceNo->setText(record.value(record.indexOf("deviceNo")).toString());
    ui->line1->setText(record.value(record.indexOf("line1")).toString());
    ui->line2->setText(record.value(record.indexOf("line2")).toString());
    ui->line3->setText(record.value(record.indexOf("line3")).toString());
    ui->line4->setText(record.value(record.indexOf("line4")).toString());
    ui->line5->setText(record.value(record.indexOf("line5")).toString());
    ui->line6->setText(record.value(record.indexOf("line6")).toString());
    ui->lneDeviceAbbr->setText(record.value(record.indexOf("deviceAddr")).toString());
}
void MainWindow::slot_lineCurve(void)
{
    QCheckBox * check=(QCheckBox * )this->sender();

    if(check==ui->cb1)
    {
        if(ui->cb1->checkState()==Qt::Checked	)
        {
            ui->dataWidget->graph(curveInfos[0].curveIndex)->setVisible(false);
        }
        else
        {
            ui->dataWidget->graph(curveInfos[0].curveIndex)->setVisible(true);
        }
    }
    else if(check==ui->cb2)
    {
        if(ui->cb2->checkState()==Qt::Checked	)
        {
            ui->dataWidget->graph(curveInfos[1].curveIndex)->setVisible(false);
        }
        else
        {
            ui->dataWidget->graph(curveInfos[1].curveIndex)->setVisible(true);
        }
    }
    else if(check==ui->cb3)
    {
        if(ui->cb3->checkState()==Qt::Checked	)
        {
            ui->dataWidget->graph(curveInfos[2].curveIndex)->setVisible(false);
        }
        else
        {
            ui->dataWidget->graph(curveInfos[2].curveIndex)->setVisible(true);
        }
    }
    else if(check==ui->cb4)
    {
        if(ui->cb4->checkState()==Qt::Checked	)
        {
            ui->dataWidget->graph(curveInfos[3].curveIndex)->setVisible(false);
        }
        else
        {
            ui->dataWidget->graph(curveInfos[3].curveIndex)->setVisible(true);
        }
    }
    else if(check==ui->cb5)
    {
        if(ui->cb5->checkState()==Qt::Checked	)
        {
            ui->dataWidget->graph(curveInfos[4].curveIndex)->setVisible(false);
        }
        else
        {
            ui->dataWidget->graph(curveInfos[4].curveIndex)->setVisible(true);
        }
    }
    else if(check==ui->cb6)
    {
        if(ui->cb6->checkState()==Qt::Checked	)
        {
            ui->dataWidget->graph(curveInfos[5].curveIndex)->setVisible(false);
        }
        else
        {
            ui->dataWidget->graph(curveInfos[5].curveIndex)->setVisible(true);
        }
    }
    ui->dataWidget->replot();
    //    ui->dataWidget->pain
}

void MainWindow::on_cmbDeviceNo_2_activated(const QString &arg1)
{
    //    qDebug()<<"cur "<<arg1;
    int curIndex;
    for(int i=0;i<deviceNos.count();i++)
    {
        if(deviceNos.at(i).first.contains(arg1))
        {
            curIndex=i;
            break;
        }
    }
    ui->cmbLine->clear();
    if(curIndex<lineNos.count())
    {
        QVector<QString> line=lineNos.at(curIndex).second;
        ui->cmbLine->addItem("ALL");
        for (int i=0;i<line.count();i++)
            ui->cmbLine->addItem(line.at(i));
    }
    else
    {
        qDebug()<<"cur Index >lineNos count";
    }
}
long MainWindow::mysql_recordCount(bool flag)
{
    QSqlQuery query(db_mysql);
    QString strSql;
    if(flag)
    {
        strSql=QString("select count(*) from %1").arg(MeasureDB::mysqlDetailDataTb);
    }
    else
    {
        strSql=QString("select count(*) from %1").arg(MeasureDB::mysqlDeviceInfoTb);
    }
    if(query.exec(strSql))
    {
        long count=0;
        while(query.next())
        {
            count=query.value(0).toLongLong();
        }
        return count;
    }
    else
        return 0;
}
bool MainWindow::mysql_addDeviceNo(void)
{
    QSqlQuery query(db_mysql);
    bool flag;
    QString strSql;

    strSql=QString("insert into %1 (deviceNo) VALUES ('%2')").arg(MeasureDB::mysqlDeviceInfoTb).arg(ui->lneDeviceNo->text());
    qDebug()<<"insert mysql device number"<<strSql;
    flag=query.exec(strSql);
    return flag;
}
bool MainWindow::mysql_updateDeviceNo(bool f)
{
    QSqlQuery query(db_mysql);
    bool flag;
    QString strSql;

    strSql=QString("update %11 set deviceAddr='%1',department='%2',position='%3',line1='%4',line2='%5',line3='%6',line4='%7',line5='%8',line6='%9' where deviceNo=\'%10\'")
            .arg(ui->lneDeviceAbbr->text())
            .arg(ui->lneDepartment->text())
            .arg(ui->lnePosition->text())
            .arg(ui->line1->text())
            .arg(ui->line2->text())
            .arg(ui->line3->text())
            .arg(ui->line4->text())
            .arg(ui->line5->text())
            .arg(ui->line6->text())
            .arg(ui->lneDeviceNo->text())
            .arg(MeasureDB::mysqlDeviceInfoTb);

    flag=query.exec(strSql);
    return flag;
}
bool MainWindow::mysql_deleteDeviceNo(void)
{
    QSqlQuery query(db_mysql);
    bool flag;
    QString strSql;
    strSql=QString("delete from %1 where deviceNo='%2'").arg(MeasureDB::mysqlDeviceInfoTb).arg(ui->lneDeviceNo->text());
    qDebug()<<"delete mysql device number"<<strSql;
    flag=query.exec(strSql);
    return flag;

}

void MainWindow::updateDatabase(bool flag)
{
    long localCount=localDb->recordCount(flag);
    long remoteCount=mysql_recordCount(flag);
    //    qDebug()<<"+++++++++++++++++++++++++++++";
    if(flag)
    {
        qDebug()<<"detail data record count,local database="<<localCount<<"remote database records="<<remoteCount;
        lblLocalRecordCounts->setText(QString::fromWCharArray(L"数据记录: %1 条 ").arg(localCount));
    }
    else
    {
        qDebug()<<"device data record count,local database="<<localCount<<"remote database records="<<remoteCount;
    }
    if(localCount<remoteCount)
    {
        QSqlQuery query(db_mysql);
        QString strSql;
        if(flag)
        {
            strSql=QString("select id,tm,deviceNo,lineNo,voltage,current,temperature,humidity from %1 where id>%2").arg(MeasureDB::mysqlDetailDataTb).arg(localCount);
        }
        else
        {
            strSql=QString("select id,deviceNo,deviceAddr,department,position,line1,line2,line3,line4,line5,line6 from %1").arg(MeasureDB::mysqlDeviceInfoTb);
        }
        //        qDebug()<<"update sql="<<strSql;
        QTime cc;
        cc.start();
        if(query.exec(strSql))
        {
            localDb->Transaction();
            int i=0;
            while(query.next())
            {
                if(flag)
                {
                    //detail table
                    detailRecord dd;
                    dd.id=query.value(0).toLongLong();
                    dd.tm=query.value(1).toString();
                    dd.deviceNo=query.value(2).toString();
                    dd.lineNo=query.value(3).toInt();
                    dd.voltage=query.value(4).toFloat();
                    dd.current=query.value(5).toFloat();
                    dd.temperature=query.value(6).toFloat();
                    dd.humidty=query.value(7).toFloat();
                    localDb->insert_detailRecord(dd);
                }
                else
                {
                    //devcie information table
                    deviceInfo dd;
                    dd.id=query.value(0).toInt();
                    dd.deviceNo=QString::fromWCharArray(( wchar_t *)query.value(1).toString().utf16());
                    dd.deviceAddr=QString::fromWCharArray(( wchar_t *)query.value(2).toString().utf16());
                    dd.department=QString::fromWCharArray(( wchar_t *)query.value(3).toString().utf16());
                    dd.position=QString::fromWCharArray(( wchar_t *)query.value(4).toString().utf16());
                    dd.line1=QString::fromWCharArray(( wchar_t *)query.value(5).toString().utf16());
                    dd.line2=QString::fromWCharArray(( wchar_t *)query.value(6).toString().utf16());
                    dd.line3=QString::fromWCharArray(( wchar_t *)query.value(7).toString().utf16());
                    dd.line4=QString::fromWCharArray(( wchar_t *)query.value(8).toString().utf16());
                    dd.line5=QString::fromWCharArray(( wchar_t *)query.value(9).toString().utf16());
                    dd.line6=QString::fromWCharArray(( wchar_t *)query.value(10).toString().utf16());
                    //qDebug()<<"insert device record status="<<i++<<dd.deviceAddr<<
                    localDb->insert_deviceInfoRecord(dd);
                }
            }
            localDb->Commit();
        }
        if(flag)
        {
            qDebug()<<"detail record update time="<<cc.elapsed();
            ui->statusbar->showMessage(QString::fromWCharArray(L"数据更新：%1 条,时间:%2").arg(abs(localCount-remoteCount)).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")));
            //更新数据条数
            lblLocalRecordCounts->setText(QString::fromWCharArray(L"当前数据条数: %1").arg(localDb->recordCount(true)));
        }
        else
        {
            qDebug()<<"device infomation record update time="<<cc.elapsed();
        }
    }
}

void MainWindow::on_pbtnReshData_clicked()
{
    slot_updateData();
}
void MainWindow::slot_updateData(void)
{
    qDebug()<<"timer out,update record";
    updateDatabase(true);
    //    updateDatabase(false);
    updateDeviceNo();
    qDebug()<<"1 update";
    ShowDB();
    qDebug()<<"2 update";
    ShowStaturs();
    qDebug()<<"3 update";
    ShowOverData();
}
