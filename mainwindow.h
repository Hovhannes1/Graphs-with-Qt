#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void startVertexDeletion();
    void cancelVertexDeletion();
    void deleteVertexActionCreation();

    void cancelEdgeCreation();
    void startEdgeDeletion();
    void cancelEdgeDeletion();
    void deleteEdgeActionCreation();
    void cancelEdgeActionCreation();

    void updateStatusbar();

    void showEvent(QShowEvent *e);

private slots:
    void on_actionVertex_triggered();

    void on_actionEdge_triggered();

//    void on_actionSave_triggered();

    void on_actionLoad_triggered();

private:
    Ui::MainWindow *ui;

    QAction *cancelAction;
    QAction *deleteVertexAction;
    QAction *deleteEdgeAction;
    QMenuBar *bar;
    QLabel *statusInfo = new QLabel();

    bool edgeCreationStarted = false;
};
#endif // MAINWINDOW_H
