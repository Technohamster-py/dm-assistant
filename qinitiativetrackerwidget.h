//
// Created by arseniy on 27.03.2024.
//

#ifndef DM_ASSIST_QINITIATIVETRACKERWIDGET_H
#define DM_ASSIST_QINITIATIVETRACKERWIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include "encounter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QInitiativeTrackerWidget; }
QT_END_NAMESPACE

class QInitiativeTrackerWidget : public QWidget {
Q_OBJECT

public:
    explicit QInitiativeTrackerWidget(QWidget *parent = nullptr);

    ~QInitiativeTrackerWidget() override;

    void loadEncounter(Encounter *encounter);
    void clear();

private:
    Ui::QInitiativeTrackerWidget *ui;
    void selectRow(int row);

    int m_currentIndex;
    int m_entityCount;
    int m_currentEntityIndex;

    Encounter *m_encounter;

private slots:
    void on_backButton_clicked();
    void on_nextButton_clicked();
    void on_hpSpinBox_valueChanged(int value);
};

class CustomSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
    {
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);

        if (leftData.isValid() && rightData.isValid()) {
            return leftData.toDouble() > rightData.toDouble();
        }

        return QSortFilterProxyModel::lessThan(left, right);
    }
};

#endif //DM_ASSIST_QINITIATIVETRACKERWIDGET_H
