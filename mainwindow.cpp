#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Stats: |V|=" +
                                   QString::number(ui->canvas->getVertexListLength())+
                                   "  |E|=" +
                                   QString::number(ui->canvas->getEdgeListLength())
                               );
}

MainWindow::~MainWindow()
{
    delete ui;
}

