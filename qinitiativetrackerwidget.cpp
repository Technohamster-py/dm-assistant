//
// Created by arseniy on 27.03.2024.
//
#include <QItemSelectionModel>

#include "qinitiativetrackerwidget.h"

#include "ui_qinitiativetrackerwidget.h"
#include "ui_qdndinitiativeentityeditwidget.h"
#include "ui_qplayerinitiativeview.h"


#include <qdebug.h>

QInitiativeTrackerWidget::QInitiativeTrackerWidget(QWidget *parent, bool playerViewMode) :
        QWidget(parent), ui(new Ui::QInitiativeTrackerWidget) {
    ui->setupUi(this);
}

QInitiativeTrackerWidget::~QInitiativeTrackerWidget() {
    delete ui;
}

void QInitiativeTrackerWidget::loadEncounter(Encounter *encounter) {
    ui->titleLabel->setText(encounter->getTitle());
    m_entityCount = encounter->getModel()->rowCount();
    m_encounter = encounter;

    CustomSortFilterProxyModel* initiativeProxyModel = new CustomSortFilterProxyModel();
    initiativeProxyModel->setSourceModel(encounter->getModel());
    initiativeProxyModel->setDynamicSortFilter(true);

    ui->encounterView->setModel(initiativeProxyModel);
    initiativeProxyModel->sort(0, Qt::AscendingOrder);

    ui->encounterView->setColumnWidth(0, 20);
    ui->encounterView->setColumnWidth(1, 190);
    ui->encounterView->setColumnWidth(2, 20);
    ui->encounterView->setColumnWidth(3, 60);

    ui->encounterView->hideColumn(4);
    ui->encounterView->hideColumn(5);
    ui->encounterView->hideColumn(6);

    selectRow(0);

    emit encounterLoaded();
}

void QInitiativeTrackerWidget::clear() {

}

void QInitiativeTrackerWidget::selectRow(int row) {
    m_currentIndex = row;

    QItemSelectionModel *selectionModel = ui->encounterView->selectionModel();
    QItemSelection selection;
    QModelIndex topLeft = ui->encounterView->model()->index(row, 0);
    QModelIndex bottomRight = ui->encounterView->model()->index(row, 3);
    selection.select(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::ClearAndSelect);

    m_currentEntityIndex = ui->encounterView->model()->index(row, 6).data().toInt();

    ui->nameLabel->setText(ui->encounterView->model()->index(row, 1).data().toString());
    ui->acLabel->setText("AC " + ui->encounterView->model()->index(row, 2).data().toString());

    ui->hpSpinBox->setMaximum(ui->encounterView->model()->index(row, 5).data().toInt());
    ui->hpSpinBox->setValue(ui->encounterView->model()->index(row, 4).data().toInt());
    ui->maxHpLabel->setText(ui->encounterView->model()->index(row, 5).data().toString());

    emit currentEntityChanged(m_currentIndex);
}

void QInitiativeTrackerWidget::on_nextButton_clicked() {
    if(m_currentIndex + 1 < m_entityCount)
        selectRow(m_currentIndex + 1);
    else
        selectRow(0);
}

void QInitiativeTrackerWidget::on_backButton_clicked() {
    if(m_currentIndex - 1 >= 0)
        selectRow(m_currentIndex - 1);
    else
        selectRow(m_entityCount - 1);
}

void QInitiativeTrackerWidget::on_hpSpinBox_valueChanged(int value) {
    m_encounter->entities.at(m_currentEntityIndex)->setHp(ui->hpSpinBox->value());
}

void QInitiativeTrackerWidget::on_shareButton_clicked() {
    emit share(m_encounter);
}


////////////////////////////////////////////////////
//          qDndInitiativeEntityEditWidget        //
////////////////////////////////////////////////////
qDndInitiativeEntityEditWidget::qDndInitiativeEntityEditWidget(EncounterEntity *entity, QWidget *parent) :
        QWidget(parent), ui(new Ui::qDndInitiativeEntityEditWidget) {
    ui->setupUi(this);

    ui->nameLabel->setText(entity->getTitle());
    ui->acLabel->setText(QString::number(entity->getAC()));
    ui->hpSpinBox->setValue(entity->getHP());
    ui->hpSpinBox->setMaximum(entity->getMaxHp());
}

qDndInitiativeEntityEditWidget::~qDndInitiativeEntityEditWidget() {
    delete ui;
}


////////////////////////////////////////////////////
//           qPlayerInitiativeView                //
////////////////////////////////////////////////////

qPlayerInitiativeView::qPlayerInitiativeView(QInitiativeTrackerWidget *parentTracker, QWidget *parent) :
        QWidget(parent), ui(new Ui::qPlayerInitiativeView) {
    ui->setupUi(this);

    loadEncounter(parentTracker->getEncounter());

    //connect(parentTracker, SIGNAL(currentEntityChanged), this, )
}

qPlayerInitiativeView::~qPlayerInitiativeView() {
    delete ui;
}

void qPlayerInitiativeView::loadEncounter(Encounter *encounter) {
    m_entityCount = encounter->getModel()->rowCount();
    m_encounter = encounter;

    CustomSortFilterProxyModel* initiativeProxyModel = new CustomSortFilterProxyModel();
    initiativeProxyModel->setSourceModel(encounter->getModel());
    initiativeProxyModel->setDynamicSortFilter(true);

    ui->encounterView->setModel(initiativeProxyModel);
    initiativeProxyModel->sort(0, Qt::AscendingOrder);

    ui->encounterView->setColumnWidth(0, 20);
    ui->encounterView->setColumnWidth(2, 20);
    ui->encounterView->setColumnWidth(3, 60);

    ui->encounterView->hideColumn(4);
    ui->encounterView->hideColumn(5);
    ui->encounterView->hideColumn(6);

    selectRow(0);
}

void qPlayerInitiativeView::selectRow(int row) {
    m_currentIndex = row;

    QItemSelectionModel *selectionModel = ui->encounterView->selectionModel();
    QItemSelection selection;
    QModelIndex topLeft = ui->encounterView->model()->index(row, 0);
    QModelIndex bottomRight = ui->encounterView->model()->index(row, 3);
    selection.select(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::ClearAndSelect);
}

void qPlayerInitiativeView::changeActiveEntity(int index) {
    selectRow(index);
}

void qPlayerInitiativeView::setParentTracker(QInitiativeTrackerWidget *tracker) {
    m_parentTracker = tracker;
    connect(m_parentTracker, SIGNAL(currentEntityChanged(int)), SLOT(changeActiveEntity(int)));
}
