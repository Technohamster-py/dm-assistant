//
// Created by arsen on 06.03.2024.
//

#ifndef DM_ASSIST_QPLAYER_H
#define DM_ASSIST_QPLAYER_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class QPlayer; }
QT_END_NAMESPACE

class QPlayer : public QWidget {
Q_OBJECT

public:
    explicit QPlayer(QWidget *parent = nullptr);

    ~QPlayer() override;

private:
    Ui::QPlayer *ui;
};


#endif //DM_ASSIST_QPLAYER_H
