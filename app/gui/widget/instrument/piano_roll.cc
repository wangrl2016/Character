//
// Created by wangrl2016 on 2023/6/26.
//

#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include "app/gui/widget/instrument/piano_roll.h"

namespace app {
    constexpr int kInvalidKey = -1;

    // The scale of C Major - white keys only.
    auto kWhiteKeys = std::array{
            kKeyC, kKeyD, kKeyE, kKeyF, kKeyG, kKeyA, kKeyH
    };

    const int kPianoBase = 16;      // the height of the root note display
    const int kWhiteKeyWidth = 24;  // the width of a white key
    const int kBlackKeyWidth = 16;   // the width of black key
    const int kWhiteKeyHeight = 64; // the height of a white key
    const int kBlackKeyHeight = 40; // the height of a black key

    // Create a new keyboard display view.
    //
    // @param parent the parent instrument plugin window
    PianoRoll::PianoRoll(QWidget* parent) :
            QWidget(parent),
            piano_(std::make_unique<Piano>()),
            start_key_(kKeyC), /* the first key displayed? */
            last_key_(kInvalidKey) {

        setAttribute(Qt::WA_OpaquePaintEvent, true);
        // listen keyboard is pressed
        setFocusPolicy(Qt::StrongFocus);

        // create scrollbar at the bottom
        piano_scroll_ = new QScrollBar(Qt::Horizontal, this);
        piano_scroll_->setValue(kOctave3 * Piano::kWhiteKeysPerOctave);

        // and connect it to this widget
        connect(piano_scroll_, SIGNAL(valueChanged(int)),
                this, SLOT(PianoScrolled(int)));

        // create a layout for ourselves
        auto layout = new QVBoxLayout(this);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(piano_scroll_);
        setLayout(layout);
    }

    PianoRoll::~PianoRoll() = default;

    void PianoRoll::keyPressEvent(QKeyEvent* key) {
        int key_num = GetKeyFromKeyEvent(key);
        piano_->SetKeyState(key_num, true);
        update();
    }

    void PianoRoll::keyReleaseEvent(QKeyEvent* key) {
        int key_num = GetKeyFromKeyEvent(key);
        piano_->SetKeyState(key_num, false);
        update();
    }

    int PianoRoll::GetKeyFromKeyEvent(QKeyEvent* event) {
        return event->key();
    }

    // Paint the piano display view in response to an event.
    //
    // This method draws the piano and the 'root note' base. It draws
    // the base first, then all the white keys, then all the black keys.
    void PianoRoll::paintEvent(QPaintEvent* event) {
        QPainter painter(this);

        // Draw bar above the keyboard (there will be the labels for all C's).
        painter.fillRect(QRect(0, 0, width(), kPianoBase), painter.background());

        // draw the line above the keyboard
        painter.setPen(Qt::black);
        painter.drawLine(0, 0, width(), 0);
        painter.drawLine(0, kPianoBase - 1, width(), kPianoBase - 1);

        int cur_key = start_key_;

        // Draw all white keys...
        for (int x = 0; x < width();) {
            while (Piano::IsBlackKey(cur_key)) {
                cur_key++;
            }

            // Draw normal, pressed or disabled key, depending on
            // state and position of current key.
            if (piano_->IsKeyPressed(cur_key)) {
                painter.setBrush(Qt::red);
            } else {
                painter.setBrush(Qt::white);
            }
            painter.drawRect(x, kPianoBase, kWhiteKeyWidth, kWhiteKeyHeight);

            x += kWhiteKeyWidth;

            if ((Keys) (cur_key % kKeysPerOctave) == kKeyC) {
                // Label key of note C with "C" and number of current octave.
                painter.drawText(x - kWhiteKeyWidth,
                                 (kPianoBase + painter.font().pointSize()) / 2 - 1,
                                 QString("C") + QString::number(kFirstOctave + cur_key / kKeysPerOctave));
            }
            cur_key++;
        }

        // Reset all values, because now we're going to draw all black keys.
        cur_key = start_key_;
        int white_cnt = 0;

        // now draw all black keys...
        for (int x = 0; x < width();) {
            if (Piano::IsBlackKey(cur_key)) {
                // Draw normal, pressed or disabled key, depending on state and position of current key.
                if (piano_->IsKeyPressed(cur_key)) {
                    painter.setBrush(Qt::red);
                } else {
                    painter.setBrush(QBrush(Qt::black));
                }
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

    void PianoRoll::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            // get pressed key
            int key_num = GetKeyFromMouse(event->pos());
            piano_->SetKeyState(key_num, true);
            last_key_ = key_num;

            emit KeyPressed(key_num);

            update();
        }
    }

    void PianoRoll::mouseMoveEvent(QMouseEvent* event) {
        int key_num = GetKeyFromMouse(event->pos());

        if (key_num != last_key_) {
            if (last_key_ != kInvalidKey) {
                piano_->SetKeyState(last_key_, false);
                last_key_ = kInvalidKey;
            }
            if (event->buttons() & Qt::LeftButton) {
                if (event->pos().y() > kPianoBase) {
                    piano_->SetKeyState(key_num, true);
                    last_key_ = key_num;
                }
            }

            update();
        }
    }

    void PianoRoll::mouseReleaseEvent(QMouseEvent* event) {
        if (last_key_ != kInvalidKey) {
            piano_->SetKeyState(last_key_, false);

            // and let the user see that he released a key
            update();
            last_key_ = kInvalidKey;
        }
    }

    void PianoRoll::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);
        piano_scroll_->setRange(0, Piano::kNumWhiteKeys -
                                   static_cast<int>(floor(static_cast<float>(width()) / kWhiteKeyWidth)));
    }

    void PianoRoll::PianoScrolled(int new_pos) {
        start_key_ = kWhiteKeys[uint64_t(new_pos % Piano::kWhiteKeysPerOctave)] +
                     (new_pos / Piano::kWhiteKeysPerOctave) * kKeysPerOctave;
        update();
    }

    // Get the key from the mouse position in the piano display.
    //
    // First we determine it roughly by the position of the point given in
    // white key widths from our start.  We then add in any black keys that
    // might have been skipped over (they take a key number, but no 'white
    // key' space).  We then add in our starting key number.
    //
    // We then determine whether it was a black key that was pressed by
    // checking whether it was within the vertical range of black keys.
    // Black keys sit exactly between white keys on this keyboard, so
    // we then shift the note down or up if we were in the left or right
    // half of the white note.  We only do this, of course, if the white
    // note has a black key on that side, so to speak.
    //
    // This function returns const because there is a linear mapping from
    // the point given to the key returned that never changes.
    //
    // @param point The point that the mouse was pressed
    int PianoRoll::GetKeyFromMouse(const QPoint& point) const {
        int offset = point.x() % kWhiteKeyWidth;

        if (offset < 0)
            offset += kWhiteKeyWidth;

        int key_num = (point.x() - offset) / kWhiteKeyWidth;

        for (int i = 0; i <= key_num; i++) {
            if (Piano::IsBlackKey(start_key_ + i)) {
                key_num++;
            }
        }

        for (int i = 0; i >= key_num; i--) {
            if (Piano::IsBlackKey(start_key_ + i)) {
                key_num--;
            }
        }

        key_num += start_key_;

        // Is it a black key?
        if (point.y() < kPianoBase + kBlackKeyHeight) {
            // then do extra check whether the mouse-cursor is over
            // a black key
            if (key_num > 0 && Piano::IsBlackKey(key_num - 1) &&
                offset <= (kWhiteKeyWidth / 2) - (kBlackKeyWidth / 2)) {
                key_num--;
            }
            if (key_num < kNumKeys - 1 && Piano::IsBlackKey(key_num + 1) &&
                offset >= (kWhiteKeyWidth - kBlackKeyWidth / 2)) {
                key_num++;
            }
        }

        return qBound(0, key_num, kNumKeys - 1);
    }
}
