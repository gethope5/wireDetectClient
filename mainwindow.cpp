#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    manager(NULL),
    localDb(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readConfigure();
    uiInitial();
    localDb =new MeasureDB("./wireDetectDb.db");
    if(localDb)
    {
        initialViewDb();
    }
    connect2MysqlDb();
    curveInitial();
    slot_updateData();
}
void MainWindow::initialViewDb(void)
{
    QSqlDatabase md=localDb->currDatabase();
    //    ui->wdgTable->setDateBase(md,MeasureDB::local_wireDetailName);
}
//函数功能：
void MainWindow::readConfigure(void)
{
    QSettings  settings("Config.ini", QSettings::IniFormat);
    ui->lnbOverValue->setText(QString::number(settings.value("par/constAlarm", 1).toFloat()));
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
    settings.setValue("par/constAlarm", ui->lnbOverValue->text().toFloat());
}
//函数功能：更新设备类型
void MainWindow::updateDeviceType(void)
{
    QSqlQuery query(localDb->currDatabase());
    //    qDebug()<<"db status"<<db_mysql.isOpen();

    QString strSql=QString("Select distinct deviceType from %1  where department =\'%2\'")
            .arg(MeasureDB::local_deviceInfoName).arg(MeasureDB::curDepartment);
    qDebug()<<"device type s "<<strSql;
    if(query.exec(strSql))
    {
        ui->cmbDeviceType->clear();
        while(query.next())
        {
            ui->cmbDeviceType->addItem(query.value(0).toString());
        }
        setUI(ui->cmbDeviceType->currentText());
    }
    updateDeviceLocal();
}
//函数功能:获取满足特定设备类型及设备所属路局条件下的所有设备对应的位置
void MainWindow::updateDeviceLocal(void)
{
    QSqlQuery query(localDb->currDatabase());
    QString strSql=QString("Select distinct localPosition from %1  where department =\'%2\' and deviceType=\'%3\'")
            .arg(MeasureDB::local_deviceInfoName)
            .arg(MeasureDB::curDepartment)
            .arg(ui->cmbDeviceType->currentText());
    if(query.exec(strSql))
    {
        ui->cmbDeviceNo->clear();
        qDebug()<<"update device number ok,sql"<<strSql;
        while(query.next())
        {
            ui->cmbDeviceNo->addItem(query.value(0).toString());
        }
    }
    else
    {
        qDebug()<<"update device NO. error"<<strSql;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::curveInitial(void)
{
    //设置曲线颜色
    color.push_back(QColor(0,125,125));
    color.push_back(QColor(0,0,255));
    color.push_back(QColor(0,255,0));
    color.push_back(QColor(0,255,255));
    color.push_back(QColor(255,0,255));
    color.push_back(QColor(255,125,0));
    //this->addAction(ui->deviceManager);
    ;
    for(int i=0;i<CURVE_NUMBERS;i++)
    {
        //if(curveInfos[i].curveIndex==-1)
        {
            ui->dataWidget->addGraph();
            curveInfos[i].curveIndex=ui->dataWidget->graphCount()-1;
            curveInfos[i].color=color.at(i);
            ui->dataWidget->graph( curveInfos[i].curveIndex)->setLineStyle(QCPGraph::lsLine);
            ui->dataWidget->graph( curveInfos[i].curveIndex)->setPen(QPen( curveInfos[i].color));
        }
    }
    //B值温度曲线初始化
    ui->dataWidget->addGraph(ui->dataWidget->xAxis,ui->dataWidget->yAxis2);
    curveBTemperture.curveIndex=ui->dataWidget->graphCount()-1;
    curveBTemperture.color=color.at(2);
    ui->dataWidget->graph( curveBTemperture.curveIndex)->setLineStyle(QCPGraph::lsLine);
    ui->dataWidget->graph( curveBTemperture.curveIndex)->setPen(QPen( curveBTemperture.color));

    //曲线插件设置
    ui->dataWidget->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->dataWidget->xAxis->setLabel(QString::fromWCharArray(L"时间"));
    ui->dataWidget->yAxis->setLabel(QString::fromWCharArray(L"电流大小"));
    ui->dataWidget->xAxis->setRange(0,24*60*60);
    connect(ui->dataWidget,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(MouseWheel()));
    //    ui->dataWidget->yAxis->setRange(0,100);

    ui->dataWidget->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->dataWidget->xAxis->setDateTimeFormat("MM-dd-hh");
    // 设置一个更紧凑的字体大小为底部和左轴刻度标签：
    ui->dataWidget->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    ui->dataWidget->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // 设置一天为固定的一个刻度
    ui->dataWidget->xAxis->setAutoTickStep(false);
    ui->dataWidget->xAxis->setTickStep(3600/**24*/); // 一天的秒数
    ui->dataWidget->xAxis->setSubTickCount(9);//一个大刻度包含4个小刻度

    //    curveSim();
    //    qDebug()<<"ticker "<<sharedTicker.


    ui->dataWidget->xAxis2->setVisible(true);
    ui->dataWidget->yAxis2->setVisible(true);//坐标轴是否可见
    ui->dataWidget->xAxis2->setTicks(false);//刻度是否可见
    ui->dataWidget->yAxis2->setTicks(false);
    ui->dataWidget->xAxis2->setTickLabels(false);//轴标签是否可见
    ui->dataWidget->yAxis2->setTickLabels(false);
    qDebug()<<"legend "<<ui->dataWidget->legend->itemCount()/*<<ui->dataWidget->legend->*/;
    ui->dataWidget->legend->setVisible(false);
}

void MainWindow::curveSim(void)
{
    QString results = "2016-06-01 08:00:00#36#"
                      "2016-06-01 12:00:00#37#2016-06-01 18:00:00#37#"
                      "2016-06-02 08:00:00#36#2016-06-02 12:00:00#37#"
                      "2016-06-02 18:00:00#37#2016-06-03 08:00:00#36#"
                      "2016-06-03 12:00:00#35#2016-06-03 18:00:00#37#"
                      "2016-06-04 08:00:00#36#2016-06-04 12:00:00#37#"
                      "2016-06-04 18:00:00#37#2016-06-05 08:00:00#36#"
                      "2016-06-05 12:00:00#37#2016-06-05 18:00:00#36#"
                      "2016-06-06 08:00:00#37#2016-06-06 12:00:00#36#"
                      "2016-06-06 18:00:00#37#2016-06-07 08:00:00#37#"
                      "2016-06-07 12:00:00#37#2016-06-07 18:00:00#36#";
    QStringList list = results.split("#");//假设数据
    qDebug()<<list<<list.length();
    QVector<double> time(21), value(21);//给数组赋值，时间和数值 7*3=21个数据
    for (int i=0; i<21; ++i)
    {
        time[i] = QDateTime::fromString(list[2*i],"yyyy-MM-dd hh:mm:ss").toTime_t();
        value[i] = list.at(2*i+1).toInt();
    }
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 200));
    ui->dataWidget->graph(0)->setLineStyle(QCPGraph::lsLine);//设置数据点由一条直线连接
    ui->dataWidget->graph(0)->setPen(pen);
    ui->dataWidget->graph(0)->setData(time, value);//设置数据
    ui->dataWidget->graph(0)->rescaleValueAxis();

    ui->dataWidget->graph(1)->setPen(QPen(Qt::red));
    ui->dataWidget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->dataWidget->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->dataWidget->graph(1)->addData(time, value);//设置点

    ui->dataWidget->xAxis2->setVisible(true);
    ui->dataWidget->yAxis2->setVisible(true);//坐标轴是否可见
    ui->dataWidget->xAxis2->setTicks(false);//刻度是否可见
    ui->dataWidget->yAxis2->setTicks(false);
    ui->dataWidget->xAxis2->setTickLabels(false);//轴标签是否可见
    ui->dataWidget->yAxis2->setTickLabels(false);
    ui->dataWidget->legend->setVisible(true);
    // 设置轴范围和显示全部数据
    ui->dataWidget->xAxis->setRange(time[0],time[0]+24*3600*7);
    ui->dataWidget->yAxis->setRange(30, 45);
    // 显示图例
    ui->dataWidget->graph(0)->setName("心率");
    ui->dataWidget->graph(1)->setName("具体数值");
}

void MainWindow::drawLine(curveInfo curveData)
{
    ui->dataWidget->graph(curveData.curveIndex)->setVisible(true);
    //            if(curveInfos[i].y.count())
    //    qDebug()<<"datas "<<curveData.x.count()<<curveData.y.count()<<curveData.x<<curveData.y;
    //            ui->dataWidget->graph(curveInfos[i].curveIndex)->setData(curveInfos[i].x,curveInfos[i].y);
    ui->dataWidget->graph(curveData.curveIndex)->setData(curveData.x,curveData.y);
    ui->dataWidget->xAxis->setRange(curveData.x.at(0),curveData.x.at(curveData.x.count()-1));
}
void MainWindow::uiInitial(void)
{
    //设置默认界面
    //    ui->checkBox_2->setChecked(true);
    //    this->setWindowTitle(QString::fromWCharArray(L"高压线路在线检测智能预警系统V1.1-四川信达轨道交通设备有限责任公司"));
    //    this->setWindowTitle(QString::fromWCharArray(L"高压线路在线检测智能预警系统V1.2-1009-四川信达轨道交通设备有限责任公司"));
    this->setWindowTitle(QString::fromWCharArray(L"高速铁路供电安全监测系统-C6"));
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

    ui->startDate->setDate(QDate::currentDate().addDays(-2));
    ui->endDate->setDate(QDate::currentDate().addDays(1));

    timer=new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_updateData()));

    timer->start(updateInterval*60*1000);//s

    //1表格
    pbtnTable=new QPushButton;
    pbtnTable->setFixedSize(pbtn_width,pbtn_height);
    pbtnTable->setIconSize(pbtnTable->size());
    pbtnTable->setIcon(QIcon("./images/datatable.png"));
    pbtnTable->setFlat(true);
    //2设备信息
    pbtnDevice=new QPushButton;
    pbtnDevice->setFixedSize(pbtn_width,pbtn_height);
    pbtnDevice->setIconSize(pbtnDevice->size());
    pbtnDevice->setIcon(QIcon("./images/device.png"));
    pbtnDevice->setFlat(true);
    //3刷新
    pbtnUpdate=new QPushButton;
    pbtnUpdate->setFixedSize(pbtn_width,pbtn_height);
    pbtnUpdate->setIconSize(pbtnUpdate->size());
    pbtnUpdate->setIcon(QIcon("./images/update.png"));
    pbtnUpdate->setFlat(true);
    //4曲线
    pbtnCurveUI=new QPushButton;
    pbtnCurveUI->setFixedSize(pbtn_width,pbtn_height);
    pbtnCurveUI->setIconSize(pbtnCurveUI->size());
    pbtnCurveUI->setIcon(QIcon("./images/dataCurve.png"));
    pbtnCurveUI->setFlat(true);
    //5超限
    pbtnOver=new QPushButton;
    pbtnOver->setFixedSize(pbtn_width,pbtn_height);
    pbtnOver->setIconSize(pbtnOver->size());
    pbtnOver->setIcon(QIcon("./images/errorData.png"));
    pbtnOver->setFlat(true);

    //5超限
    pbtnExit=new QPushButton;
    pbtnExit->setFixedSize(pbtn_width,pbtn_height);
    pbtnExit->setIconSize(pbtnOver->size());
    pbtnExit->setIcon(QIcon("./images/exit.png"));
    pbtnExit->setFlat(true);




    ui->pbtnExit->setIcon(QIcon("./images/exitWdg.png"));
    ui->pbtnExit->setIconSize(ui->pbtnExit->size());
    ui->pbtnExit->setFlat(true);
    ui->pbtnExit->setText("");



    ui->pbtnMin->setIcon(QIcon("./images/min.png"));
    ui->pbtnMin->setIconSize(ui->pbtnMin->size());
    ui->pbtnMin->setFlat(true);
    ui->pbtnMin->setText("");
    //    ui->toolBar->addWidget(pbtnTable);
    //    ui->toolBar->addWidget(pbtnOver);
    //    ui->toolBar->addWidget(pbtnDevice);
    //    ui->toolBar->addWidget(pbtnCurveUI);
    //    ui->toolBar->addWidget(pbtnUpdate);
    //    ui->toolBar->addWidget(pbtnExit);

    connect(pbtnDevice,SIGNAL(clicked()),this,SLOT(toolPbtnProcessing()));
    connect(pbtnUpdate,SIGNAL(clicked()),this,SLOT(toolPbtnProcessing()));
    connect(pbtnTable,SIGNAL(clicked()),this,SLOT(toolPbtnProcessing()));
    connect(pbtnOver,SIGNAL(clicked()),this,SLOT(toolPbtnProcessing()));
    connect(pbtnCurveUI,SIGNAL(clicked()),this,SLOT(toolPbtnProcessing()));
    connect(pbtnExit,SIGNAL(clicked()),this,SLOT(toolPbtnProcessing()));

    //    ui->toolBar->resize(ui->toolBar->width(),100);
    //    ui->toolBar->addWidget(ui->groupBox_3);

    //    QGridLayout mm(ui->groupBox_3);
    //    ui->toolBar->setLayout(&mm);
    //    ui->toolBar->setMovable(false);
    ui->lblEndDate->setAlignment(Qt::AlignRight);
    ui->lblOver->setAlignment(Qt::AlignRight);


    connect(ui->cb1,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb2,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));

    connect(ui->cb3,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb4,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb5,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));
    connect(ui->cb6,SIGNAL(pressed()),this,SLOT(slot_lineCurve()));

    //设置表格为只读模式
    ui->wdgOver->tableView->setEditTriggers(/*QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|*/QAbstractItemView::NoEditTriggers);
    ui->tbTableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tbTableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbTableInfo->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->pbtnDataFilter->setBitmap((QPixmap)("./images/query-focus.png"),(QPixmap)("./images/query.png"));
    ui->pbtnDataFilter->setText("");
    ui->pbtnDataFilter->setFlat(true);

    ui->pbtnUpdate->setBitmap((QPixmap)("./images/updateData-focus.png"),(QPixmap)("./images/updateData.png"));
    ui->pbtnUpdate->setText("");
    ui->pbtnUpdate->setFlat(true);


    ui->pbtnCurve->setBitmap((QPixmap)("./images/curve-focus.png"),(QPixmap)("./images/curve.png"));
    ui->pbtnCurve->setText("");
    ui->pbtnCurve->setFlat(true);

//    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    ui->pbtnExit->setVisible(false);
    ui->pbtnMin->setVisible(false);
    this->setWindowState(Qt::WindowMaximized);//
    ui->tabWidget->setCurrentWidget(ui->tabTable);
#if 0
    ui->lblLine->setAlignment(Qt::AlignRight);
    ui->cmbLine->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
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
        updateAllTable();
    }
    else
    {
        qDebug()<<"deviecestaturs is not ok";
    }
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
QString MainWindow::getDeviceNO(QString localPosition)
{
    QString strSql=QString("select deviceNo from %1 where localposition ='\%2\' and devicetype=\'%3\'")
            .arg(MeasureDB::local_deviceInfoName).arg(localPosition).arg(ui->cmbDeviceType->currentText());
    QSqlQuery query(localDb->currDatabase());
    bool bflag=query.exec(strSql);
    if(bflag)
    {
        qDebug()<<"devcie NO. ok,str="<<strSql<<bflag;
        while(query.next())
        {
            QString mm=query.value(0).toString();
            if(mm.isEmpty())
                return "" ;
            else
                return mm;
        }
    }
    else
    {
        qDebug()<<"devcie NO. error,str="<<strSql<<bflag;
        return "";
    }
}
void MainWindow::DrawCurve()
{
#if 1
    QString tmp("");

    for(int i=0;i<CURVE_NUMBERS;i++)
        curveInfos[i].clear();

    QString deviceNo=getDeviceNO(ui->cmbDeviceNo->currentText());
    qDebug()<<"device no"<<deviceNo<<deviceNo.count();
    if(deviceNo.isEmpty())
    {
        qDebug()<<"device no. is null";
        return;
    }

    tmp=QString(" tm between '%1%' and '\%2\' and deviceNO=\'%3\'")
            .arg(ui->startDate->dateTime().toString("yyyy-MM-dd")).arg(ui->endDate->dateTime().toString("yyyy-MM-dd"))
            .arg(deviceNo);

    QString strSql;
    if(curType.second==WIRE_TYPE)
    {
        strSql=QString("select lineNo,tm,current from %1 where %2 ")
                .arg(MeasureDB::local_wireDetailName).arg(tmp);
    }
    else if(curType.second==B_TYPE)
    {
        strSql=QString("select tm,b1,b2,humidityIn from %1 where %2 ")
                .arg(MeasureDB::local_bDetailName).arg(tmp);
    }
    QSqlQuery query(localDb->currDatabase());
    if(query.exec(strSql))
    {
        qDebug()<<"curve data ok,sql"<<strSql;
        if(curType.second==WIRE_TYPE)
        {
            while(query.next())
            {
                //                if(query.value(2).toFloat())
                {
                    //                    QDateTime temp = query.value(1).toDateTime();
                    //                    qint32 sCount = temp.time().msecsSinceStartOfDay()/1000;
                    double sCount = QDateTime::fromString( query.value(1).toString(),"yyyy-MM-dd hh:mm:ss").toTime_t();

                    //                qDebug()<<"time"<< query.value(1).toString()<<sCount;
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
            for(int i=0;i<CURVE_NUMBERS;i++)
            {
                drawLine(curveInfos[i]);
            }
        }
        else if(curType.second==B_TYPE)
        {
            while(query.next())
            {
                double sCount = QDateTime::fromString( query.value(0).toString(),"yyyy-MM-dd hh:mm:ss").toTime_t();
                //                tm,b1,b2,temperatureIn
                curveInfos[0].x<<sCount;
                float b1=query.value(1).toFloat();
                float b2=query.value(2).toFloat();
                float t=query.value(3).toFloat();
                if(b1)
                    curveInfos[0].y<<b1;
                if(b2)
                    curveInfos[1].y<<b2;
                if(t)
                    curveBTemperture.y<<t;
            }
            curveInfos[1].x=curveInfos[0].x;
            curveBTemperture.x=curveInfos[0].x;
            for(int i=0;i<B_CURVE_NUMBERS;i++)
            {
                drawLine(curveInfos[i]);
            }
            drawLine(curveBTemperture);
        }
        ui->dataWidget->replot();
    }
    else
    {
        qDebug()<<"curve,data error,sql"<<strSql;
    }

#else
    QString tmp("");
    if(!ui->cmbDeviceType->currentText().contains("ALL"))
    {
        for(int i=0;i<CURVE_NUMBERS;i++)
            curveInfos[i].clear();

        if(deviceNos.count())
        {
            int curIndex=0;
            for(int i=0;i<deviceNos.count();i++)
            {
                if(deviceNos.at(i).first.contains(ui->cmbDeviceType->currentText()))
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

            tmp.append(QString(" and tm like '%1%' ").arg(ui->startDate->dateTime().toString("yyyy-MM-dd")));


            QString strSql=QString("select lineNo,tm,current from %1 where %2").arg(MeasureDB::local_wireDetailName).arg(tmp);
            QSqlQuery query(localDb->currDatabase());
            qDebug()<<"string sql"<<strSql<<ui->startDate->dateTime().toString("yy-MM-dd")<<ui->endDate->dateTime().toString("yy-MM-dd");
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
#endif
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
        ui->statusbar->showMessage(QString::fromWCharArray(L"连接数据库成功......"));
    }
    else
    {
        remoteDbStatus->setCurStatus(DISCONNECTED);
        ui->statusbar->showMessage(QString::fromWCharArray(L"连接数据库失败请检查网络连接......")+db_mysql.lastError().text());
        qDebug()<<"k"<<db_mysql.isValid();
    }
#endif
}
void MainWindow::showTable( QTableView *tableview,QString filter)
{
    QTime timer;
    bool bExec;
    timer.start();
    QString field;
    QString title;
    QString tableName;
    if(tableview==ui->wdgTable->tableView||tableview==ui->wdgOver->tableView)
    {
        if(curType.second==WIRE_TYPE)
        {
            QPair<QString,QString> tmp =getShowTableInfo(MeasureDB::local_wireDetailField,MeasureDB::local_wireDetailTitle);
            field=tmp.first;
            title=tmp.second;
            tableName=MeasureDB::local_wireDetailName;
        }
        else if(curType.second==B_TYPE)
        {
            QPair<QString,QString> tmp =getShowTableInfo(MeasureDB::local_bDetailField,MeasureDB::local_bDetailTitle);
            field=tmp.first;
            title=tmp.second;
            tableName=MeasureDB::local_bDetailName;
        }
    }
    else if(tableview==ui->tbTableInfo)
    {
        QPair<QString,QString> tmp =getShowTableInfo(MeasureDB::local_deviceInfoField,MeasureDB::local_deviceInfoTitle);
        field=tmp.first;
        title=tmp.second;
        tableName=MeasureDB::local_deviceInfoName;
    }
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    QSqlQuery query(localDb->currDatabase());
    int tmIndex;
    QString strSql;
    if(filter.isNull())
    {
        strSql=QString("SELECT %1 from %2").arg(field).arg(tableName);
    }
    else
    {
        strSql=QString("SELECT %1 from %2 where %3").arg(field).arg(tableName).arg(filter);
    }
    //    QString strSql=QString::fromWCharArray(L"SELECT * from %1 where id>0").arg(tableName);
    bExec=query.exec(strSql);
    //    qDebug()<<"show sql"<<strSql<<bExec;
    tmIndex=query.record().indexOf("tm");
    queryModel->setQuery(query);
    for(int i=0;i<title.split(',').count();i++)
    {
        QString tmp=title.split(',').at(i);
        queryModel->setHeaderData(i,Qt::Horizontal, tmp);
        //        queryModel->setHeaderData(i,Qt::Horizontal, QString(tmp.left(tmp.length()-1)));
    }
    while (queryModel->canFetchMore())
        queryModel->fetchMore();
    tableview->setModel(queryModel);
    if(tmIndex!=-1)
        tableview->setColumnWidth(tmIndex,130);
}
QPair<QString,QString> MainWindow::getShowTableInfo(QString field,QString title)
{
    QStringList mm=title.split(",");//MeasureDB::local_wireDetailTitle;
    QString tmpField;
    QString tmpTitle;
    for(int i=0;i<mm.count();i++)
    {
        if(mm.at(i).right(1).toInt())
        {
            tmpField+=field.split(',').at(i)+",";
            tmpTitle+=mm.at(i).left(mm.at(i).length()-1)+",";
        }
    }
    if(tmpField.endsWith(","))
        tmpField=tmpField.left(tmpField.length()-1);
    if(tmpTitle.endsWith(","))
        tmpTitle=tmpTitle.left(tmpTitle.length()-1);
    //    qDebug()<<"cur field "<<tmpField<<tmpTitle;
    return QPair<QString,QString> (tmpField,tmpTitle);
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
        showTable(ui->tbTableInfo,MeasureDB::local_deviceInfoFilter);
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,QString::fromWCharArray(L"提示"),QString::fromWCharArray(L"您确定退出应用程序吗")) == QMessageBox::No)
        event->ignore();
}
//函数功能：数据筛选刷新
void MainWindow::on_pbtnDataFilter_clicked()
{
    //    qDebug()<<"cur device type"<<ui->cmbDeviceType->currentText()<<;
    if(ui->cmbDeviceType->currentText().isNull())
    {
        ui->statusbar->showMessage(QString::fromWCharArray(L"没有本地数据,先同步数据"),3000);
        setCursor(QCursor(Qt::WaitCursor));
        slot_updateData();
        setCursor(QCursor(Qt::ArrowCursor));
    }
    else
    {
        setCursor(QCursor(Qt::WaitCursor));
        updateDeviceLocal();
        updateAllTable();
        DrawCurve();
        setConfigure();
        setCursor(QCursor(Qt::ArrowCursor));
    }
}
QString MainWindow::getStrFilter(void)
{
    QString strFilter("");
    QDate d1=ui->startDate->date();
    QDate d2=ui->endDate->date();
    if(d1>d2)
    {
        ui->statusbar->showMessage(QString::fromWCharArray(L"结束时间大于起始时间，请重新设置..."));
    }
    else
    {
        //        qDebug()<<"d1<d2"<<d1.toString("yyyy-MM-dd")<<d2.toString("yyyy-MM-dd");
        strFilter=QString (" tm between \'%1\' and \'%2\'").arg(ui->startDate->dateTime().toString("yyyy-MM-dd")).arg(ui->endDate->dateTime().toString("yyyy-MM-dd"));
    }
    return strFilter;
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
            if(curType.second==WIRE_TYPE)
            {
                ui->dataWidget->graph(curveInfos[2].curveIndex)->setVisible(false);
            }
            else if(curType.second==B_TYPE)
            {
                ui->dataWidget->graph(curveBTemperture.curveIndex)->setVisible(false);
            }
        }
        else
        {
            if(curType.second==WIRE_TYPE)
            {
                ui->dataWidget->graph(curveInfos[2].curveIndex)->setVisible(true);
            }
            else if(curType.second==B_TYPE)
            {
                ui->dataWidget->graph(curveBTemperture.curveIndex)->setVisible(true);
            }
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

void MainWindow::on_cmbDeviceType_activated(const QString &arg1)
{
    //    qDebug()<<"cur "<<arg1;
    int curIndex;
    qDebug()<<"cur device type"<<arg1;
    setUI(arg1);
}
void MainWindow::setUI(QString arg1)
{
    if(arg1.contains(QString::fromWCharArray(L"电")))
    {
        ui->cb1->setText(QString::fromWCharArray(L"线路1"));
        ui->cb2->setText(QString::fromWCharArray(L"线路2"));
        ui->cb3->setText(QString::fromWCharArray(L"线路3"));
        ui->cb4->setText(QString::fromWCharArray(L"线路4"));
        ui->cb5->setText(QString::fromWCharArray(L"线路5"));
        ui->cb6->setText(QString::fromWCharArray(L"线路6"));

        ui->cb1->setVisible(true);
        ui->cb2->setVisible(true);
        ui->cb3->setVisible(true);
        ui->cb4->setVisible(true);
        ui->cb5->setVisible(true);
        ui->cb6->setVisible(true);
        ui->lblOverUnit->setText("A");

        ui->dataWidget->yAxis->setLabel(QString::fromWCharArray(L"电流大小"));
        ui->dataWidget->yAxis2->setTicks(false);
        ui->dataWidget->yAxis2->setTickLabels(false);
        MeasureDB::local_deviceInfoTitle=QString::fromWCharArray(L"ID0,设备编号1,类型1,所属路局1,安装位置1,安装时间1,线路11,线路21,线路31,线路41,线路51,线路61");
        ui->lnbOverValue->setText("1");
        curType=QPair<QString,DETECT_TYPE>(arg1,WIRE_TYPE);
    }
    else if(arg1.contains(QString::fromWCharArray(L"B值")))
    {
        ui->cb1->setText(QString::fromWCharArray(L"接触线B值"));
        ui->cb2->setText(QString::fromWCharArray(L"承力索B值"));
        ui->cb3->setText(QString::fromWCharArray(L"环境温度"));

        ui->cb1->setVisible(true);
        ui->cb2->setVisible(true);
        ui->cb3->setVisible(true);
        ui->cb4->setVisible(false);
        ui->cb5->setVisible(false);
        ui->cb6->setVisible(false);
        ui->lblOverUnit->setText("mm");
        ui->dataWidget->yAxis->setLabel(QString::fromWCharArray(L"B"));
        ui->dataWidget->yAxis2->setLabel(QString::fromWCharArray(L"温度"));
        ui->dataWidget->yAxis2->setTickLabels(true);
        ui->dataWidget->yAxis2->setRange(0,100);
        ui->dataWidget->yAxis->setRange(500,2500);
        ui->dataWidget->yAxis2->setTicks(true);

        MeasureDB::local_deviceInfoTitle=QString::fromWCharArray(L"ID0,设备编号1,类型1,所属路局1,安装位置1,安装时间1,线路10,线路20,线路30,线路40,线路50,线路60");
        ui->lnbOverValue->setText("2200");
        curType=QPair<QString,DETECT_TYPE>(arg1,B_TYPE);
    }
    qDebug()<<"cur axis"<<ui->dataWidget->yAxis->label()<<ui->dataWidget->yAxis2->label();
    update();
}
long MainWindow::mysql_recordCount(DETECT_TYPE flag)
{
    if(db_mysql.isOpen())
    {
        QSqlQuery query(db_mysql);
        QString strSql;

        if(flag==WIRE_TYPE)
        {
            strSql=QString("select count(*) from %1").arg(MeasureDB::mysql_wireDetailTable);
        }
        else if(flag==B_TYPE)
        {
            strSql=QString("select count(*) from %1").arg(MeasureDB::mysql_bDetailTable);
        }
        else if(flag==DEVICE_INFO)
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
    else
        return 0;
}
//函数功能：更新数据,将远程传感器数据同步到本地数据库.type,用于选择同步的传感器类型
long MainWindow::updateDatabase(DETECT_TYPE type )
{
    long localCount=localDb->recordCount(type);
    long remoteCount=mysql_recordCount(type);
    //    qDebug()<<"+++++++++++++++++++++++++++++";

    lblLocalRecordCounts->setText(QString::fromWCharArray(L"数据记录: %1 条 ").arg(localCount));
    if(localCount<remoteCount)
    {
        qDebug()<<"detail data record count,local database="<<localCount<<"remote database records="<<remoteCount<<"begin update data...";
        if(!db_mysql.isOpen())
            return 0;

        if(type==WIRE_TYPE)
        {
            updateWireDetailRecord(localCount);
        }
        else if(type==B_TYPE)
        {
            updateBDetailRecord(localCount);
        }
        //更新数据条数
        lblLocalRecordCounts->setText(QString::fromWCharArray(L"当前数据条数: %1").arg(localDb->recordCount(type)));
        return abs(remoteCount-localCount);
    }
    else
        return 0;
}
void  MainWindow::updateBDetailRecord(long localCount)
{
    QSqlQuery query(db_mysql);
    QString strSql;
    bool bflag=false;
    //                      0 1  2        3  4  5           6             7       8        9        10         11
    strSql=QString("select id,tm,deviceNo,b1,b2,temperature,temperatureIn,voltage,voltage2,humidity,humidityIn,remark from %1 where id>%2")
            .arg(MeasureDB::mysql_bDetailTable).arg(localCount);

    bflag=query.exec(strSql);
    qDebug()<<"b value,sql"<<strSql<<bflag;
    if(bflag)
    {
        db_mysql.transaction();
        localDb->Transaction();
        while(query.next())
        {

            //detail table
            B_Data dd;
            dd.id=query.value(0).toLongLong();
            dd.tm=query.value(1).toString();
            dd.deviceNo=query.value(2).toString();
            dd.b1=query.value(3).toFloat();
            dd.b2=query.value(4).toFloat();
            dd.temperature=query.value(5).toFloat();
            dd.temperatureIn=query.value(6).toFloat();
            dd.voltage=query.value(7).toFloat();
            dd.voltage2=query.value(8).toFloat();
            dd.humidity=query.value(9).toFloat();
            dd.humidityIn=query.value(10).toFloat();
            dd.remark=query.value(11).toString();
            localDb->insert_bDetailRecord(dd);
        }
        localDb->Commit();
        db_mysql.commit();
    }
}
void MainWindow::updateWireDetailRecord(long localCount)
{
    QSqlQuery query(db_mysql);
    QString strSql;

    strSql=QString("select id,tm,deviceNo,lineNo,voltage,current,temperature,humidity from %1 where id>%2").arg(MeasureDB::mysql_wireDetailTable).arg(localCount);
    if(query.exec(strSql))
    {
        db_mysql.transaction();
        localDb->Transaction();
        while(query.next())
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
            localDb->insert_wireDetailRecord(dd);
        }
        localDb->Commit();
        db_mysql.commit();
    }
}
void MainWindow::slot_updateData(void)
{

    //    updateDeviceType();
    //    qDebug()<<"first show,begin----------------------------------";
    //    updateDatabase(curType.second);
    //    updateAllTable();
    localDb->updateDeviceInfo(db_mysql);
    //    qDebug()<<"first show,end----------------------------------";
    QTime cc;
    cc.start();
    this->statusBar()->showMessage(curType.first+" "+QString::fromWCharArray(L"数据刷新中..."));
    qDebug()<<"update data...";
    updateDeviceType();
    long updateCount=updateDatabase(curType.second);
    updateAllTable();
    ui->statusbar->showMessage(QString::fromWCharArray(L"数据更新：%1 条,时间:%2,%3")
                               .arg(updateCount)
                               .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"))
                               .arg(cc.elapsed()));
    DrawCurve();
}
void MainWindow::updateAllTable(void)
{
    QString strFilter=getStrFilter();
    QString over;
    if(strFilter.isNull())
    {
        if(curType.second==WIRE_TYPE)
        {
            over=QString("current >%1").arg(ui->lnbOverValue->text());
        }
        else if(curType.second==B_TYPE)
        {
            over=QString("b1>%1 or b2>%2 ").arg(ui->lnbOverValue->text()).arg(ui->lnbOverValue->text());
        }
    }
    else
    {
        if(curType.second==WIRE_TYPE)
        {
            over=QString("%1 and current >%2").arg(strFilter).arg(ui->lnbOverValue->text());
        }
        else if(curType.second==B_TYPE)
        {
            over=QString("%1 and (b1>%2 or b2>%3 )").arg(strFilter).arg(ui->lnbOverValue->text()).arg(ui->lnbOverValue->text());
        }
    }
    //    qDebug()<<"filter data string="<<strFilter;
    showTable(ui->wdgTable->tableView,strFilter);
    showTable(ui->wdgOver->tableView,over);
    showTable(ui->tbTableInfo,MeasureDB::local_deviceInfoFilter);
}
void MainWindow::toolPbtnProcessing(void)
{
    //    qDebug()<<"tool run here";
    QPushButton *pbtn=(QPushButton *)this->sender();
    //1超限
    if(pbtn==pbtnOver)
    {
        ui->tabWidget->setCurrentWidget(ui->tabOver);
    }
    //2表格
    else if(pbtn==pbtnTable)
    {
        ui->tabWidget->setCurrentWidget(ui->tabTable);
    }
    //3设备信息
    else if(pbtn==pbtnDevice)
    {
        ui->tabWidget->setCurrentWidget(ui->tabDevice);
    }
    //4曲线
    else if(pbtn==pbtnCurveUI)
    {
        ui->tabWidget->setCurrentWidget(ui->tabCurve);
    }
    //5刷新
    else if(pbtn==pbtnUpdate)
    {
        slot_updateData();
    }
    //6退出
    else if(pbtn==pbtnExit)
    {
        close();
    }
}
void MainWindow::on_pbtnCurve_clicked()
{
    DrawCurve();
}
void MainWindow::on_pbtnUpdate_clicked()
{
    slot_updateData();
}
void MainWindow::on_pbtnExit_clicked()
{
    close();
}
void MainWindow::resizeEvent(QResizeEvent *)
{
    QSize pSize=ui->widget_2->size();
    qDebug()<<"ui size"<<pSize<<ui->pbtnExit->size();
    ui->pbtnExit->move(pSize.width()-ui->pbtnExit->width()-30,(pSize.height()-ui->pbtnExit->height())/2);
    ui->pbtnMin->move(ui->pbtnExit->x()-ui->pbtnMin->width()-30,(pSize.height()-ui->pbtnMin->height())/2);
}

void MainWindow::on_pbtnMin_clicked()
{
    setWindowState(Qt::WindowMinimized);
}
