//
// Created by arseniy on 27.03.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QInititiveTrackerWidget.h" resolved

#include "qinitiativetrackerwidget.h"
#include "ui_QInitiativeTrackerWidget.h"


QInitiativeTrackerWidget::QInitiativeTrackerWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::QInitiativeTrackerWidget) {
    ui->setupUi(this);
}

QInitiativeTrackerWidget::~QInitiativeTrackerWidget() {
    delete ui;
}

void QInitiativeTrackerWidget::loadEncounter(Encounter *encounter) {
    ui->titleLabel->setText(encounter->getTitle());

    ui->encounterView->setModel(encounter->getModel());
    ui->encounterView->hideColumn(0);
    ui->encounterView->model()->sort(0);
}

void QInitiativeTrackerWidget::clear() {

}
