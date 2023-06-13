//
// Created by wangrl2016 on 2023/6/1.
//

#include <QApplication>
#include "ui/view/widget/main_window.h"
#include "ui/view/widget/widget_constant.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    ui::MainWindow window;
    window.setMinimumSize(kDefaultWindowWidth, kDefaultWindowHeight);
    window.show();
    return QApplication::exec();
}