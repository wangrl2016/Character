//
// Created by wangrl2016 on 2023/6/1.
//

#include <memory>
#include <QApplication>
#include "app/gui/main_window.h"
#include "app/model/play_progress_model.h"
#include "app/model/project_model.h"
#include "app/presenter/play_progress_presenter.h"
#include "app/presenter/project_presenter.h"

constexpr int kDefaultWindowWidth = 1280;
constexpr int kDefaultWindowHeight = 720;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    auto* project_model = new app::ProjectModel();
    auto* project_presenter = new app::ProjectPresenter(project_model);

    app::MainWindow window;

    window.setMinimumSize(kDefaultWindowWidth, kDefaultWindowHeight);
    window.show();

    window.Subscribe(project_presenter->play_progress_presenter());

    return QApplication::exec();
}
