#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CommInterfaceJson;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void debug(QString msg);

private:
    Ui::MainWindow *ui;
    CommInterfaceJson *mApi;

private slots:
    void on_query_button_clicked();
};

#endif // MAINWINDOW_H
