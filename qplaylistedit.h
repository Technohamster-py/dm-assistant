//
// Created by arseniy on 12.03.2024.
//

#ifndef DM_ASSIST_QPLAYLISTEDIT_H
#define DM_ASSIST_QPLAYLISTEDIT_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class QPlaylistEdit; }
QT_END_NAMESPACE

class QPlaylistEdit : public QWidget {
Q_OBJECT

public:
    explicit QPlaylistEdit(QWidget *parent = nullptr);

    ~QPlaylistEdit() override;

private:
    Ui::QPlaylistEdit *ui;
};


#endif //DM_ASSIST_QPLAYLISTEDIT_H
