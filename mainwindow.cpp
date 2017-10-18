#include "mainwindow.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QScrollBar>
#include <QTimeLine>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet("QListWidget::item{padding:5px;}");
    showed = false;
    resize(600,400);
    pushButton = new QPushButton("设置",this);
    pushButton->resize(width(),30);
    pushButton->move(0,height()/2-pushButton->height()/2);

    widget1 = new QWidget(this);
    widget1->resize(400,height());
    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->setSpacing(0);
    hbox1->setContentsMargins(0,0,0,0);
    listWidget1 = new QListWidget;
    listWidget1->insertItem(0, new QListWidgetItem("设置1→"));
    listWidget1->item(0)->setTextAlignment(Qt::AlignCenter);
    for(int i=1; i<10; i++){
        listWidget1->insertItem(i, new QListWidgetItem("小项"+QString::number(i)));
    }
    listWidget1->resize(200,height());
    listWidget2 = new QListWidget;
    listWidget2->insertItem(0, new QListWidgetItem("←设置2"));
    listWidget2->item(0)->setTextAlignment(Qt::AlignCenter);
    for(int i=1; i<10; i++){
        listWidget2->insertItem(i, new QListWidgetItem("小项"+QString::number(i)));
    }
    listWidget2->resize(200,height());
    hbox1->addWidget(listWidget1);
    hbox1->addWidget(listWidget2);
    widget1->setLayout(hbox1);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(widget1);
    scrollArea->setGeometry(0,0,200,height());
    scrollArea->show();
    scrollArea->move(width(),0);
    connect(listWidget1, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClick1(QListWidgetItem*)));
    connect(listWidget2, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClick2(QListWidgetItem*)));

    QTimeLine *timeLine = new QTimeLine(300, this);
    timeLine->setFrameRange(0, 200);
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(frameChange(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(timeLineFinish()));
    connect(pushButton, SIGNAL(clicked()), timeLine, SLOT(start()));

    timeLine1 = new QTimeLine(300, this);
    timeLine1->setFrameRange(0, 200);
    connect(timeLine1, SIGNAL(frameChanged(int)), this, SLOT(frameChange1(int)));

    timeLine2 = new QTimeLine(300, this);
    timeLine2->setFrameRange(200,0);
    connect(timeLine2, SIGNAL(frameChanged(int)), this, SLOT(frameChange2(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::frameChange(int f)
{    
    if(!showed){
        scrollArea->move(width()-f,0);
        pushButton->resize(width() - f, pushButton->height());
    }else{
        scrollArea->move(scrollArea->x()+f,0);
        pushButton->resize(width() - 200 + f, pushButton->height());
    }
}

void MainWindow::timeLineFinish()
{
    showed = !showed;
}

void MainWindow::frameChange1(int f)
{
    scrollArea->horizontalScrollBar()->setValue(f);
}

void MainWindow::frameChange2(int f)
{
    scrollArea->horizontalScrollBar()->setValue(f);
}

void MainWindow::itemClick1(QListWidgetItem* item)
{
    Q_UNUSED(item);
    switch (listWidget1->currentRow()) {
    case 0:
        listWidget1->setCurrentRow(-1);
        timeLine1->start();
        break;
    default:
        break;
    }
}

void MainWindow::itemClick2(QListWidgetItem* item)
{
    Q_UNUSED(item);
    switch (listWidget2->currentRow()) {
    case 0:
        listWidget2->setCurrentRow(-1);
        timeLine2->start();
        break;
    default:
        break;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    pushButton->move(0, height()/2 - pushButton->height()/2);
    widget1->resize(400,height());
    listWidget1->resize(200,height());
    listWidget2->resize(200,height());
    scrollArea->setGeometry(0,0,200,height());
    if(showed){
        pushButton->resize(width()-200,30);
        scrollArea->move(width()-200, 0);
    }else{
        pushButton->resize(width(), 30);
        scrollArea->move(width(), 0);
    }
}
