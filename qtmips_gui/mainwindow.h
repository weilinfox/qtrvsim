#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "ui_MainWindow.h"
#include "newdialog.h"
#include "coreview.h"
#include "cachecontent.h"
#include "cachestatistics.h"
#include "registersdock.h"

#include "qtmipsmachine.h"
#include "machineconfig.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void start();
    void create_core(MachineConfig *config);

public slots:
    void new_machine();

    void show_cache_content();
    void show_cache_statictics();
    void show_registers();

    bool configured();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    NewDialog *ndialog;

    CoreView *coreview;

    CacheContentDock *cache_content;
    CacheStatisticsDock *cache_statictics;
    RegistersDock *registers;

    QSettings  *settings;

    QtMipsMachine *machine; // Current simulated machine

    void show_dockwidget(QDockWidget *w);
};

#endif // MAINWINDOW_H