//
// Created by wangrl2016 on 2023/8/28.
//

#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include "tools/image/main_window.h"

constexpr int kDefaultWidth = 1280;
constexpr int kDefaultHeight = 720;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    int width = QGuiApplication::primaryScreen()->geometry().width();
    int height = QGuiApplication::primaryScreen()->geometry().height();

    app::MainWindow main_window;
    main_window.setGeometry((width - kDefaultWidth) / 2,
                            (height - kDefaultHeight) / 2,
                            kDefaultWidth,
                            kDefaultHeight);
    main_window.show();

    return QApplication::exec();
}