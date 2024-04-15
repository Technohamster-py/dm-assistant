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
    entityCount = encounter->getModel()->rowCount();

    CustomSortFilterProxyModel* initiativeProxyModel = new CustomSortFilterProxyModel();
    initiativeProxyModel->setSourceModel(encounter->getModel());
    initiativeProxyModel->setDynamicSortFilter(true);

    ui->encounterView->setModel(initiativeProxyModel);
    initiativeProxyModel->sort(0, Qt::AscendingOrder);

    ui->encounterView->setColumnWidth(0, 20);
    ui->encounterView->setColumnWidth(2, 20);
    ui->encounterView->setColumnWidth(3, 60);

    selectRow(0);
}

void QInitiativeTrackerWidget::clear() {

}

void QInitiativeTrackerWidget::selectRow(int row) {
    currentIndex = row;

    QItemSelectionModel *selectionModel = ui->encounterView->selectionModel();
    QItemSelection selection;
    QModelIndex topLeft = ui->encounterView->model()->index(row, 0);
    QModelIndex bottomRight = ui->encounterView->model()->index(row, 3);
    selection.select(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::ClearAndSelect);
}

void QInitiativeTrackerWidget::on_nextButton_clicked() {
    if(currentIndex+1 < entityCount)
        selectRow(currentIndex+1);
    else
        selectRow(0);
}

void QInitiativeTrackerWidget::on_backButton_clicked() {
    if(currentIndex-1 >= 0)
        selectRow(currentIndex-1);
    else
        selectRow(entityCount-1);
}
