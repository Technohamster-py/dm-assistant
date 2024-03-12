//
// Created by arseniy on 12.03.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QPlaylistEdit.h" resolved

#include "qplaylistedit.h"
#include "ui_QPlaylistEdit.h"


QPlaylistEdit::QPlaylistEdit(QWidget *parent) :
        QWidget(parent), ui(new Ui::QPlaylistEdit) {
    ui->setupUi(this);
}

QPlaylistEdit::~QPlaylistEdit() {
    delete ui;
}
