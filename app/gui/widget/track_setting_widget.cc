//
// Created by wr on 2023/6/22.
//

#include <glog/logging.h>
#include <QStandardItem>
#include "app/presenter/track_container_presenter.h"
#include "app/gui/widget/track_setting_widget.h"
#include "app/presenter/project_presenter.h"

namespace app {
    TrackSettingWidget::TrackSettingWidget(QWidget* parent) :
            QTableView(parent) {

        setStyleSheet("QWidget {"
                      "    border: none;"
                      "}");

        Subscribe(ProjectPresenter::Instance()->track_container_presenter());

        auto* standard_model = new QStandardItemModel(this);
        standard_model->setColumnCount(1);

        const int row_count = track_container_presenter_->TrackSize();
        standard_model->setRowCount(row_count);
        //设置数据
        for (int row = 0; row < row_count; row++) {
            auto* new_item = new QStandardItem;
            new_item->setData("HelloWorld", Qt::DisplayRole);
            standard_model->setItem(row, 0, new_item);
        }

        setModel(standard_model);

        track_delegate_ = new TrackDelegate;

        setItemDelegate(track_delegate_);
    }
}
