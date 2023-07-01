//
// Created by wangrl2016 on 2023/6/1.
//

#include <memory>
#include <QApplication>
#include "app/gui/main_window.h"
#include "app/model/play_progress_model.h"
#include "app/model/project_model.h"
#include "app/presenter/play_progress_presenter.h"

constexpr int kDefaultWindowWidth = 1280;
constexpr int kDefaultWindowHeight = 720;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    auto* play_progress_model = new app::PlayProgressModel();
    auto* play_progress_presenter =
            new app::PlayProgressPresenter(play_progress_model);

    auto* project_model = new app::ProjectModel();


    app::MainWindow window;

    window.setMinimumSize(kDefaultWindowWidth, kDefaultWindowHeight);
    window.show();

    window.Subscribe(play_progress_presenter);

    return QApplication::exec();
}
