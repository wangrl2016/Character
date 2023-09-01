//
// Created by admin on 2023/9/1.
//

#ifndef CHARACTER_ACTION_EXPORT_DIALOG_H
#define CHARACTER_ACTION_EXPORT_DIALOG_H

#include <QDialog>

namespace app {
    class ActionExportDialog : public QDialog {
    Q_OBJECT
    public:
        ActionExportDialog(QWidget* parent = nullptr);
    };
}

#endif //CHARACTER_ACTION_EXPORT_DIALOG_H
