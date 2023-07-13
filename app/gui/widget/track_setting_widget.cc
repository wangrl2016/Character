//
// Created by wr on 2023/6/22.
//

#include <QStandardItem>
#include "app/gui/widget/track_setting_widget.h"

namespace app {
    TrackSettingWidget::TrackSettingWidget(QWidget* parent) :
            QTableView(parent) {

        setStyleSheet("QWidget {"
                      "    border: none;"
                      "}");



        auto* standard_model = new QStandardItemModel(this);
        const int col_count = 5;
        standard_model->setColumnCount(col_count);
        standard_model->setHeaderData(0, Qt::Horizontal, "Bool");
        standard_model->setHeaderData(1, Qt::Horizontal, "Int");
        standard_model->setHeaderData(2, Qt::Horizontal, "Double");
        standard_model->setHeaderData(3, Qt::Horizontal, "List");
        standard_model->setHeaderData(4, Qt::Horizontal, "String");

        const int row_count=10;
        standard_model->setRowCount(row_count);
        //设置数据
        for(int row=0;row<row_count;row++)
        {
            for(int col=0;col<col_count;col++)
            {
                QStandardItem *new_item=new QStandardItem;

                switch(col)
                {
                    default: break;
                        //checkbox bool
                    case 0:
                        new_item->setData(row%2?true:false,Qt::DisplayRole);
                        break;
                        //spinbox int
                    case 1:
                        new_item->setData(row,Qt::DisplayRole);
                        break;
                        //doublespinbox double
                    case 2:
                        new_item->setData(row*3.1415926,Qt::DisplayRole);
                        break;
                        //combobox list
                    case 3:
                        new_item->setData(QStringList{"A","B","C"},Qt::DisplayRole);
                        //这里使用userrole来保存列表的下标
                        new_item->setData(row%3,Qt::UserRole);
                        break;
                        //linedit string
                    case 4:
                        new_item->setData(QString("String %1").arg(row),Qt::DisplayRole);
                        break;
                }
                standard_model->setItem(row, col, new_item);
            }
        }

        setModel(standard_model);

        track_delegate_ = new TrackDelegate;

        setItemDelegate(track_delegate_);
    }
}
