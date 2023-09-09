//
// Created by wr on 2023/9/9.
//

#ifndef CHARACTER_LAYER_TOOL_H
#define CHARACTER_LAYER_TOOL_H

#include <QWidget>
#include <QPushButton>

namespace app {
    class LayerTool : public QWidget {
    Q_OBJECT
    public:
        LayerTool(QWidget* parent = nullptr);

    private:
        QPushButton* add_layer_btn_;
        QPushButton* adjust_layer_btn_;
        QPushButton* effect_layer_btn_;
        QPushButton* mask_layer_btn_;
        QPushButton* cut_mask_layer_btn_;
        QPushButton* arrange_layer_btn_;
        QPushButton* delete_layer_btn_;
    };
}


#endif //CHARACTER_LAYER_TOOL_H
