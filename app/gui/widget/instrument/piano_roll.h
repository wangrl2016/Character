//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_PIANO_ROLL_H
#define CHARACTER_PIANO_ROLL_H

#include <QWidget>
#include <QScrollBar>
#include "app/gui/widget/instrument/piano.h"

namespace app {
    class PianoRoll : public QWidget {
    Q_OBJECT
    public:
        PianoRoll(QWidget* parent = nullptr);

        ~PianoRoll() override;

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

        void BaseNoteChanged();

    private slots:
        void PianoScrolled(int new_pos);

    private:
        int GetKeyFromMouse(const QPoint& point) const;

        Piano* piano_;

        QScrollBar* piano_scroll_;

        // record keystrokes starting at the leftmost
        int start_key_;
        // record the most recently pressed key
        int last_key_;
    };
}

#endif //CHARACTER_PIANO_ROLL_H
