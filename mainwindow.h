//
// Created by akhomchenko on 25.03.24.
//

#ifndef DM_ASSIST_MAINWINDOW_H
#define DM_ASSIST_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //DM_ASSIST_MAINWINDOW_H
