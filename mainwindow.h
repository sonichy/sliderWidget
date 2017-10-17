#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QTimeLine>
#include <QListWidgetItem>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton *pushButton;
    QWidget *widget1;
    QScrollArea *scrollArea;
    bool showed;
    QTimeLine *timeLine1,*timeLine2;
    QListWidget *listWidget1,*listWidget2;

private slots:    
    void frameChange(int f);
    void timeLineFinish();
    void frameChange1(int f);
    void frameChange2(int f);
    void itemClick1(QListWidgetItem* item);
    void itemClick2(QListWidgetItem* item);
};

#endif // MAINWINDOW_H
