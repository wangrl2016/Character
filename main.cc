//
// Created by wangrl2016 on 2023/6/1.
//

#include <QApplication>
#include "ui/view/widget/main_window.h"
#include "ui/view/widget/widget_constant.h"
#include "ui/view/setting/audio_device_selector.h"
#include "module/audio_graph/audio_bridge.h"

int main(int argc, char* argv[]) {
    audio_graph::AudioBridge::Create();
    audio_graph::AudioBridge::Start();

    QApplication app(argc, argv);
    ui::AudioDeviceSelector selector;
    selector.setMinimumSize(800, 600);
    selector.show();
    int ret =  QApplication::exec();

    audio_graph::AudioBridge::Stop();
    audio_graph::AudioBridge::Destroy();

    return ret;
    // ui::MainWindow window;
    // window.setMinimumSize(kDefaultWindowWidth, kDefaultWindowHeight);
    // window.show();
    // return QApplication::exec();
}