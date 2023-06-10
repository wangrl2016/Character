//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_PIANO_VIEW_H
#define CHARACTER_PIANO_VIEW_H

#include <QDockWidget>

namespace ui {
    class PianoView: public QDockWidget {
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

    private:
        int start_key_;

        static QPixmap* white_key_pixmap_;
        static QPixmap* black_key_pixmap_;
    };
}


#endif //CHARACTER_PIANO_VIEW_H
