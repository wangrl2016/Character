//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_PIANO_VIEW_H
#define CHARACTER_PIANO_VIEW_H

#include <QDockWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include "ui/model/piano.h"

namespace ui {
    constexpr int kInvalidKey = -1;

    class PianoView: public QWidget {
        Q_OBJECT
    public:
        PianoView(QWidget* parent = nullptr);

        ~PianoView();

    public:
        void keyPressEvent(QKeyEvent* key) override;

        void keyReleaseEvent(QKeyEvent* key) override;

        static int GetKeyFromKeyEvent(QKeyEvent* event);

    protected:
        void paintEvent(QPaintEvent* event) override;

        void mousePressEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void focusInEvent(QFocusEvent* event) override;

        void focusOutEvent(QFocusEvent* event) override;

        void resizeEvent(QResizeEvent* event) override;

    signals:
        void KeyPressed(int);

    private:
        int GetKeyFromMouse(const QPoint& point) const;

        Piano* piano_;

        // record keystrokes starting at the leftmost
        int start_key_;
        // record the most recently pressed key
        int last_key_;

        static QPixmap* white_key_pixmap_;
        static QPixmap* black_key_pixmap_;
    };
}


#endif //CHARACTER_PIANO_VIEW_H
