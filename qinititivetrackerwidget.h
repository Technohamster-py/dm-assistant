//
// Created by arseniy on 27.03.2024.
//

#ifndef DM_ASSIST_QINITITIVETRACKERWIDGET_H
#define DM_ASSIST_QINITITIVETRACKERWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class QInititiveTrackerWidget; }
QT_END_NAMESPACE

class QInititiveTrackerWidget : public QWidget {
Q_OBJECT

public:
    explicit QInititiveTrackerWidget(QWidget *parent = nullptr);

    ~QInititiveTrackerWidget() override;

private:
    Ui::QInititiveTrackerWidget *ui;
};


#endif //DM_ASSIST_QINITITIVETRACKERWIDGET_H
