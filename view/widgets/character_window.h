//
// Created by wangrl2016 on 2023/6/2.
//

#ifndef CHARACTER_CHARACTER_WINDOW_H
#define CHARACTER_CHARACTER_WINDOW_H

#include <QMainWindow>
#include <QMdiArea>

namespace view {
    class CharacterWindow : public QMainWindow {
    Q_OBJECT
    public:
        CharacterWindow();

        ~CharacterWindow() override;

    public:
        bool NewFile();

        bool OpenFile();

    private:
        void CreateActions();

        void CreateMenus();

        QAction* file_new_action_;
        QAction* file_open_action_;

    private:
        QMdiArea* mdi_area_;
    };
}


#endif //CHARACTER_CHARACTER_WINDOW_H
