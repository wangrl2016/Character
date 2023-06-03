//
// Created by wangrl2016 on 2023/6/1.
//

#include <QApplication>
#include "view/widgets/character_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    view::CharacterWindow window;
    window.show();
    return QApplication::exec();
}