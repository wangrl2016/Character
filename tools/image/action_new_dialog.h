//
// Created by wangrl2016 on 2023/8/29.
//

#ifndef CHARACTER_ACTION_NEW_DIALOG_H
#define CHARACTER_ACTION_NEW_DIALOG_H

#include <QDialog>
#include <QLabel>

namespace app {
    class ActionNewDialog : public QDialog {
    Q_OBJECT
    public:
        explicit ActionNewDialog(QWidget* parent = nullptr);

    private:
        QLabel* width_label_;
        QLabel* height_label_;
    };
}


#endif //CHARACTER_ACTION_NEW_DIALOG_H
