//
// Created by wangrl2016 on 2023/6/21.
//

#include <QActionGroup>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include "app/gui/toolbar/top_tool_bar.h"
#include "app/gui/main_window.h"

namespace app {
    constexpr int kToolBarFixedHeight = 24;

    TopToolBar::TopToolBar(QWidget* parent) :
            QToolBar(parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setFixedHeight(kToolBarFixedHeight);
        // setContentsMargins(0,0,0,0);
        setMovable(false);
//        setStyleSheet("QToolBar QToolButton:hover {"
//                      "    background-color: rgba(255, 255, 255, 0.1);"
//                      "}");

        // fast rewind
        fast_rewind_action_ = new QAction(
                QIcon(tr(":toolbar/fast_rewind")),
                tr("Fast Rewind"),
                this);
        addAction(fast_rewind_action_);

        // fast-forward
        fast_forward_action_ = new QAction(
                QIcon(tr(":toolbar/fast_forward")),
                tr("Fast Forward"),
                this);
        addAction(fast_forward_action_);

        // skip previous
        skip_previous_action_ = new QAction(
                QIcon(tr(":toolbar/skip_previous")),
                tr("Skip Previous"),
                this);
        addAction(skip_previous_action_);

        // play or pause
        play_arrow_action_ = new QAction(
                QIcon(tr(":toolbar/play_arrow")),
                tr("Play"),
                this);
        play_arrow_action_->setShortcut(Qt::Key_Space);
        play_arrow_action_->setVisible(true);
        connect(play_arrow_action_, &QAction::triggered,
                [this]() {
                    play_arrow_action_->setVisible(!play_arrow_action_->isVisible());
                    pause_action_->setVisible(!play_arrow_action_->isVisible());
                    dynamic_cast<MainWindow*>(parentWidget())->PlayOrPause();
                });
        addAction(play_arrow_action_);

        pause_action_ = new QAction(
                QIcon(tr(":toolbar/pause")),
                tr("Pause"),
                this);
        pause_action_->setShortcut(Qt::Key_Space);
        pause_action_->setVisible(false);
        connect(pause_action_, &QAction::triggered,
                [this]() {
                    play_arrow_action_->setVisible(!play_arrow_action_->isVisible());
                    pause_action_->setVisible(!play_arrow_action_->isVisible());
                    dynamic_cast<MainWindow*>(parentWidget())->PlayOrPause();
                });
        addAction(pause_action_);

        auto* spacer = new QWidget(this);
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        addWidget(spacer);

        export_action_ = new QAction(
                QIcon(tr(":toolbar/export")),
                tr("Export"),
                this);
        addAction(export_action_);

        account_circle_action_ = new QAction(
                QIcon(tr(":toolbar/account_circle")),
                tr("Account"),
                this);
        addAction(account_circle_action_);
    }
}
