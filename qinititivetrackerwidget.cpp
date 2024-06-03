//
// Created by arseniy on 27.03.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QInititiveTrackerWidget.h" resolved

#include "qinititivetrackerwidget.h"
#include "ui_qinititivetrackerwidget.h"


QInititiveTrackerWidget::QInititiveTrackerWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::QInititiveTrackerWidget) {
    ui->setupUi(this);
}

QInititiveTrackerWidget::~QInititiveTrackerWidget() {
    delete ui;
}
