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

        QGraphicsScene* scene_;
        QGraphicsView* view_;
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
