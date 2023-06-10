//
// Created by wangrl2016 on 2023/6/10.
//

#include <array>
#include <QPainter>
#include "ui/view/widgets/piano_view.h"
#include "ui/model/note.h"
#include "ui/model/piano.h"

namespace ui {
    // The scale of C Major - white keys only.
    auto kWhiteKeys = std::array{
            kKeyC, kKeyD, kKeyE, kKeyF, kKeyG, kKeyA, kKeyH
    };

    const int kPianoBase = 11;      // the height of the root note display
    const int kWhiteKeyWidth = 18;  // the width of a white key
    const int kBlackKeyWidth = 12;   // the width of black key
    const int kWhiteKeyHeight = 57; // the height of a white key
    const int kBlackKeyHeight = 38; // the height of a black key
    const int kLabelTextSize = 7;   // the height of the key label text

    // Create a new keyboard display view.
    //
    // @param parent the parent instrument plugin window
    PianoView::PianoView(QWidget* parent) :
            QDockWidget(parent),
            start_key_(kKeyC) /* the first key displayed? */ {

    }

    void PianoView::keyPressEvent(QKeyEvent* key) {

    }

    void PianoView::keyReleaseEvent(QKeyEvent* key) {

    }

    // Paint the piano display view in response to an event.
    //
    // This method draws the piano and the 'root note' base. It draws
    // the base first, then all the white keys, then all the black keys.
    void PianoView::paintEvent(QPaintEvent* event) {
        QPainter painter(this);

        // set smaller font for printing number of every octave.

        painter.fillRect(QRect(0, 1, width(), kPianoBase - 2),
                         painter.background());

        painter.setPen(Qt::black);
        painter.drawLine(0, 0, width(), 0);
        painter.drawLine(0, kPianoBase - 1, width(), kPianoBase - 1);

        painter.setPen(Qt::white);

        int cur_key = start_key_;

        // Draw all white keys...
        painter.setPen(Qt::black);
        painter.setBrush(QBrush(Qt::white));
        for (int x = 0; x < width();) {
            while (Piano::IsBlackKey(cur_key)) {
                cur_key++;
            }

            // Draw normal, pressed or disabled key, depending on
            // state and position of current key.
            painter.drawRect(x, kPianoBase, kWhiteKeyWidth, kWhiteKeyHeight);

            x += kWhiteKeyWidth;

            if ((Keys)(cur_key % kKeysPerOctave) == kKeyC) {
                // Label key of note C with "C" and number of current octave.
                painter.drawText(x - kWhiteKeyWidth,
                                 kLabelTextSize + 2,
                                 QString("C") + QString::number(kFirstOctave + cur_key / kKeysPerOctave));
            }
            cur_key++;
        }

        // Reset all values, because now we're going to draw all black keys.
        cur_key = start_key_;
        int white_cnt = 0;
        int start_key = start_key_;
        if (start_key > 0 &&Piano::IsBlackKey(static_cast<Keys>(--start_key))) {

        }

        // now draw all black keys...
        painter.setPen(QColor(Qt::black));
        painter.setBrush(QBrush(Qt::black));
        for (int x = 0; x < width();) {
            if(Piano::IsBlackKey(cur_key)) {
                // Draw normal, pressed or disabled key, depending on state and position of current key.
                painter.drawRect(x + kWhiteKeyWidth / 2, kPianoBase, kBlackKeyWidth, kBlackKeyHeight);

                x += kWhiteKeyWidth;
                white_cnt = 0;
            } else {
                white_cnt++;
                if (white_cnt > 1) {
                    x += kWhiteKeyWidth;
                }
            }

            // Stop drawing when all keys are drawn, even if an extra black key fit.
            if (++cur_key == kNumKeys) {
                break;
            }

        }

    }

    void PianoView::mousePressEvent(QMouseEvent* event) {

    }

    void PianoView::mouseMoveEvent(QMouseEvent* event) {

    }

    void PianoView::mouseReleaseEvent(QMouseEvent* event) {

    }

    void PianoView::focusInEvent(QFocusEvent* event) {

    }

    void PianoView::focusOutEvent(QFocusEvent* event) {

    }

    void PianoView::resizeEvent(QResizeEvent* event) {

    }
}
