//
// Created by wr on 2023/6/21.
//

#ifndef CHARACTER_SELECTABLE_OBJECT_H
#define CHARACTER_SELECTABLE_OBJECT_H

#include <QWidget>

namespace ui {
    class SelectableObject : public QWidget {
    Q_OBJECT
    public:
        SelectableObject(QWidget* parent) : QWidget(parent), selected_(false) {}

        ~SelectableObject() override = default;

        inline void set_selected(bool selected) {
            if (selected_ != selected) {
                selected_ = selected;
                Update();
            }
        }

        inline bool is_selected() const {
            return selected_;
        }

    public slots:

        virtual void Update() {
            QWidget::update();
        }


    private:
        bool selected_;
    };
}

#endif //CHARACTER_SELECTABLE_OBJECT_H
