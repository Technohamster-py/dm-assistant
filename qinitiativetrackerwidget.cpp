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
    CustomSortFilterProxyModel* initiativeProxyModel = new CustomSortFilterProxyModel();
    initiativeProxyModel->setSourceModel(encounter->getModel());
    initiativeProxyModel->setDynamicSortFilter(true);

    ui->encounterView->setModel(initiativeProxyModel);
    initiativeProxyModel->sort(0, Qt::AscendingOrder);

    ui->encounterView->setColumnWidth(0, 20);
    ui->encounterView->setColumnWidth(2, 20);
    ui->encounterView->setColumnWidth(3, 60);
}

void QInitiativeTrackerWidget::clear() {

}
