//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_PIANO_VIEW_H
#define CHARACTER_PIANO_VIEW_H

#include <QWidget>

namespace ui {
    class PianoView: public QWidget {
        Q_OBJECT
    public:
        PianoView(QWidget* parent = nullptr);

        ~PianoView() = default;

    public:
        void keyPressEvent(QKeyEvent* key) override;

        void keyReleaseEvent(QKeyEvent* key) override;

    protected:
        void paintEvent(QPaintEvent* event) override;

        void mousePressEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void focusInEvent(QFocusEvent* event) override;

        void focusOutEvent(QFocusEvent* event) override;

        void resizeEvent(QResizeEvent* event) override;
    };
}


#endif //CHARACTER_PIANO_VIEW_H
