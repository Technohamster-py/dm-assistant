//
// Created by arseniy on 27.03.2024.
//

#ifndef DM_ASSIST_QINITIATIVETRACKERWIDGET_H
#define DM_ASSIST_QINITIATIVETRACKERWIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
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
