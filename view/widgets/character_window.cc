//
// Created by wangrl2016 on 2023/6/2.
//

#include "view/widgets/character_window.h"

namespace view {
    CharacterWindow::CharacterWindow() : mdi_area_(new QMdiArea) {
        mdi_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mdi_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setCentralWidget(mdi_area_);


        // setUnifiedTitleAndToolBarOnMac(true);
    }

    CharacterWindow::~CharacterWindow() {

    };
}
