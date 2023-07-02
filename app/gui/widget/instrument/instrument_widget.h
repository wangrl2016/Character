//
// Created by wangrl2016 on 2023/6/25.
//

#ifndef CHARACTER_INSTRUMENT_WIDGET_H
#define CHARACTER_INSTRUMENT_WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "app/gui/widget/instrument/piano_roll.h"
#include "app/gui/widget/instrument/plucked_string.h"
#include "app/gui/toolbar/middle_tool_bar.h"

namespace app {
    class InstrumentWidget : public QWidget {
    Q_OBJECT
    public:
        explicit InstrumentWidget(QWidget* parent = nullptr);

    public slots:

        void CurrentInstrumentUpdate(int index);

    private:
        PianoRoll* piano_roll_;
        PluckedString* plucked_string_;

        MiddleToolBar* middle_tool_bar_;
        QStackedWidget* stacked_widget_;
    };
}

#endif //CHARACTER_INSTRUMENT_WIDGET_H
