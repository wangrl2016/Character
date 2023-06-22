//
// Created by wangrl2016 on 2023/6/1.
//

#include <QApplication>
#include "app/gui/main_window.h"
#include "ui/view/widget/widget_constant.h"
#include "ui/view/setting/audio_device_selector.h"
#include "module/audio_graph/audio_bridge.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    app::MainWindow window;
    window.setMinimumSize(kDefaultWindowWidth, kDefaultWindowHeight);
    window.show();
    return QApplication::exec();
}