//
// Created by wangrl2016 on 2023/7/13.
//

#ifndef CHARACTER_EXPORT_DIALOG_H
#define CHARACTER_EXPORT_DIALOG_H

#include <QDialog>

namespace app {
    class ExportDialog : public QDialog {
    public:
        explicit ExportDialog(QWidget* parent = nullptr);

        ~ExportDialog();

    public slots:

        void Export();

    private:
        QPushButton* export_button_;
    };
}

#endif //CHARACTER_EXPORT_DIALOG_H
