//
// Created by wangrl2016 on 2023/6/21.
//

#ifndef CHARACTER_ABOUT_DIALOG_H
#define CHARACTER_ABOUT_DIALOG_H

#include <QDialog>
#include <QLabel>

namespace app {
    class AboutDialog : public QDialog {
    Q_OBJECT
    public:
        AboutDialog(QWidget* parent = nullptr);

    private:
        QLabel* version_label_;
    };
}


#endif //CHARACTER_ABOUT_DIALOG_H
