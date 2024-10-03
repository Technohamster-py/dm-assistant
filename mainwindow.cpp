//
// Created by akhomchenko on 25.03.24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    initiativeWidget = new QInitiativeTrackerWidget(ui->rightAsideWidget);
    ui->rightAsideLayout->addWidget(initiativeWidget);
    connect(initiativeWidget, SIGNAL(share(Encounter *)), this, SLOT(slotShareTracker(Encounter *)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotShareTracker(Encounter *encounter) {
    qDebug() << "slotShareTracker";
    //playerInitiativeView = new qPlayerInitiativeView();
}
