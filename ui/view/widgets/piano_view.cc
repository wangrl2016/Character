//
// Created by wangrl2016 on 2023/6/10.
//

#include <array>
#include <glog/logging.h>
#include <QPainter>
#include <QVBoxLayout>
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
            QWidget(parent),
            start_key_(kKeyC), /* the first key displayed? */
            last_key_(kInvalidKey) {
        piano_ = new Piano(nullptr);

        setAttribute(Qt::WA_OpaquePaintEvent, true);
        // listen keyboard is pressed
        setFocusPolicy(Qt::StrongFocus);

        // create scrollbar at the bottom
        piano_scroll_ = new QScrollBar(Qt::Horizontal, this);
        piano_scroll_->setSingleStep(1);
        piano_scroll_->setPageStep(20);
        piano_scroll_->setValue(kOctave3 * Piano::kWhiteKeysPerOctave);

        // and connect it to this widget
        connect(piano_scroll_, SIGNAL(valueChanged(int)),
                this, SLOT(PianoScrolled(int)));

        // create a layout for ourselves
        auto layout = new QVBoxLayout(this);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addSpacing(kPianoBase + kWhiteKeyHeight);
        layout->addWidget(piano_scroll_);
    }

    PianoView::~PianoView() noexcept {
        delete piano_;
    }

    void PianoView::keyPressEvent(QKeyEvent* key) {
        int key_num = GetKeyFromKeyEvent(key);
        // LOG(INFO) << "Key num " << key_num;
        if (piano_) {
            piano_->SetKeyState(key_num, true);
            // key->accept();
            update();
        }
    }

    void PianoView::keyReleaseEvent(QKeyEvent* key) {
        int key_num = GetKeyFromKeyEvent(key);
        // LOG(INFO) << "Key num " << key_num;
        if (piano_) {
            piano_->SetKeyState(key_num, false);
            // key->accept();
            update();
        }
    }

    int PianoView::GetKeyFromKeyEvent(QKeyEvent* event) {
        return event->key();
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

        for (int x = 0; x < width();) {
            while (Piano::IsBlackKey(cur_key)) {
                cur_key++;
            }

            // Draw normal, pressed or disabled key, depending on
            // state and position of current key.
            if (piano_ && piano_->IsKeyPressed(cur_key)) {
                painter.setPen(Qt::red);
                painter.setBrush(Qt::red);
            } else {
                painter.setPen(Qt::black);
                painter.setBrush(Qt::white);
            }
            painter.drawRect(x, kPianoBase, kWhiteKeyWidth, kWhiteKeyHeight);

            x += kWhiteKeyWidth;

            if ((Keys) (cur_key % kKeysPerOctave) == kKeyC) {
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
        if (start_key > 0 && Piano::IsBlackKey(static_cast<Keys>(--start_key))) {

        }

        // now draw all black keys...

        for (int x = 0; x < width();) {
            if (Piano::IsBlackKey(cur_key)) {
                // Draw normal, pressed or disabled key, depending on state and position of current key.
                if (piano_ && piano_->IsKeyPressed(cur_key)) {
                    painter.setPen(Qt::red);
                    painter.setBrush(Qt::red);
                } else {
                    painter.setPen(QColor(Qt::black));
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

    void PianoView::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            // get pressed key
            int key_num = GetKeyFromMouse(event->pos());
            piano_->SetKeyState(key_num, true);
            last_key_ = key_num;

            emit KeyPressed(key_num);

            update();
        }
    }

    void PianoView::mouseMoveEvent(QMouseEvent* event) {
        int key_num = GetKeyFromMouse(event->pos());
        int y_diff = event->pos().y() - kPianoBase;

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

    void PianoView::mouseReleaseEvent(QMouseEvent* event) {
        if (last_key_ != kInvalidKey) {
            if (piano_) {
                piano_->SetKeyState(last_key_, false);
            }

            update();

            last_key_ = kInvalidKey;
        }
    }

    void PianoView::focusInEvent(QFocusEvent* event) {

    }

    void PianoView::focusOutEvent(QFocusEvent* event) {

    }

    void PianoView::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);
        piano_scroll_->setRange(0, Piano::kNumWhiteKeys -
                                   static_cast<int>(floor(static_cast<float>(width()) / kWhiteKeyWidth)));
    }

    void PianoView::PianoScrolled(int new_pos) {
        LOG(INFO) << __FUNCTION__ << ", new pos " << new_pos;
        start_key_ = kWhiteKeys[new_pos % Piano::kWhiteKeysPerOctave] +
                     (new_pos / Piano::kWhiteKeysPerOctave) * kKeysPerOctave;

        update();
    }

    // Get the key from the mouse position in the piano display.
    //
    //
    int PianoView::GetKeyFromMouse(const QPoint& point) const {
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
