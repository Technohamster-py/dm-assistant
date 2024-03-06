//
// Created by arsen on 06.03.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QPlayer.h" resolved

#include "qplayer.h"
#include "ui_QPlayer.h"


QPlayer::QPlayer(QWidget *parent) :
        QWidget(parent), ui(new Ui::QPlayer) {
    ui->setupUi(this);
}

QPlayer::~QPlayer() {
    delete ui;
}
