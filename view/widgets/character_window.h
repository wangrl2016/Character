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

    private:
        QMdiArea* mdi_area_;
    };
}


#endif //CHARACTER_CHARACTER_WINDOW_H
