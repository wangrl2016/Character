//
// Created by wangrl2016 on 2023/6/1.
//

#include <memory>
#include <glog/logging.h>
#include <QApplication>
#include "app/gui/main_window.h"
#include "app/model/project_model.h"
#include "app/presenter/project_presenter.h"

constexpr int kDefaultWindowWidth = 1280;
constexpr int kDefaultWindowHeight = 720;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    auto* project_model = new app::ProjectModel();
    project_model->CreateNewProject();
    app::ProjectPresenter::Instance()->SetModel(project_model);

    app::MainWindow window;

    window.setMinimumSize(kDefaultWindowWidth, kDefaultWindowHeight);
    window.show();

    window.Subscribe(app::ProjectPresenter::Instance()->play_progress_presenter());

    return QApplication::exec();
}
