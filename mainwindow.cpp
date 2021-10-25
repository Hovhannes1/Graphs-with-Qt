#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cancelEdgeActionCreation();
    deleteVertexActionCreation();
    deleteEdgeActionCreation();

    ui->canvas->setMainWindow(this);
}

void MainWindow::showEvent(QShowEvent *e)
{
    QMainWindow::showEvent(e);
    static bool firstStart = true;
    if (firstStart)
    {
        updateStatusbar();

        cancelAction->setVisible(edgeCreationStarted);
        deleteVertexAction->setVisible(false);
        deleteEdgeAction->setVisible(false);
        firstStart = false;
    }
}

void MainWindow::updateStatusbar() {
    statusInfo->setText("Stats: |V|=" +
                         QString::number(ui->canvas->getVertexListLength())+
                         "  |E|=" +
                       QString::number(ui->canvas->getEdgeListLength()));

    ui->statusBar->addWidget(statusInfo);
}

void MainWindow::cancelEdgeActionCreation()
{
    bar = new QMenuBar(ui->menubar);
    cancelAction = new QAction("Cancel", bar);

    connect(this->cancelAction,&QAction::triggered, [=]{
        this->cancelEdgeCreation();
    });
    bar->addAction(cancelAction);
    ui->menubar->setCornerWidget(bar);
}

void MainWindow::deleteVertexActionCreation()
{
    deleteVertexAction = new QAction("Delete", bar);

    connect(this->deleteVertexAction,&QAction::triggered, [=]{
        ui->canvas->deleteVertex();
        updateStatusbar();
        cancelVertexDeletion();
    });
    bar->addAction(deleteVertexAction);
}

void MainWindow::deleteEdgeActionCreation()
{
    deleteEdgeAction = new QAction("Delete", bar);

    connect(this->deleteEdgeAction,&QAction::triggered, [=]{
        ui->canvas->deleteEdge();
        updateStatusbar();
        cancelEdgeDeletion();
    });
    bar->addAction(deleteEdgeAction);
}


void MainWindow::on_actionVertex_triggered()
{
    ui->canvas->createVertex();
    updateStatusbar();
    this->update();
}

void MainWindow::on_actionEdge_triggered()
{
    edgeCreationStarted = !edgeCreationStarted;

    bar->setToolTip("Cancel Edge Creation");
    cancelAction->setVisible(edgeCreationStarted);

    ui->canvas->edgeCreationStarted = edgeCreationStarted;

    this->update();
}

void MainWindow::cancelEdgeCreation()
{
    edgeCreationStarted = false;

    cancelAction->setVisible(edgeCreationStarted);

    ui->canvas->edgeCreationStarted = edgeCreationStarted;
}

void MainWindow::startVertexDeletion()
{
    bar->setToolTip("Delete Selected Vertex");
    deleteVertexAction->setVisible(true);
}

void MainWindow::cancelVertexDeletion()
{
    deleteVertexAction->setVisible(false);
}

void MainWindow::startEdgeDeletion()
{
    bar->setToolTip("Delete Selected Edge");
    deleteEdgeAction->setVisible(true);
}

void MainWindow::cancelEdgeDeletion()
{
    deleteEdgeAction->setVisible(false);
}

//void MainWindow::on_actionSave_triggered()
//{
////    QString filename = QFileDialog::getSaveFileName();
////    QFile f(filename);
////    f.open( QIODevice::WriteOnly );
////    f.
////    // store data in f
////    f.close();
//}

void MainWindow::on_actionLoad_triggered()
{
    auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent) {
        if (fileName.isEmpty()) {
            qDebug() << "No file was selected";
        } else {
            ui->canvas->loadJSON(fileContent);
        }
    };

    QFileDialog::getOpenFileContent("(*.json)",  fileContentReady);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete cancelAction;
    delete deleteVertexAction;
    delete deleteEdgeAction;
    delete bar;
}
