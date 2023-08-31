//
// Created by wangrl2016 on 2023/8/28.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "tools/image/cover_graphics_scene.h"
#include "tools/image/cover_graphics_view.h"
#include "tools/image/left_widget.h"
#include "tools/image/right_widget.h"

namespace app {
    class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow();

        void dragEnterEvent(QDragEnterEvent* event) override;

        void dropEvent(QDropEvent* event) override;

        void mousePressEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

    private:
        void SetupMenuBar();

        LeftWidget* left_widget_;
        RightWidget* right_widget_;

        CoverGraphicsScene* scene_;
        CoverGraphicsView* view_;
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
