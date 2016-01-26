#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comminterfacejson.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mApi = new CommInterfaceJson(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::debug(QString msg)
{
    ui->log->appendPlainText(msg);
}

void MainWindow::on_query_button_clicked()
{
    mApi->getAccount();
}
