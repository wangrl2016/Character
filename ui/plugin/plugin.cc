//
// Created by wangrl2016 on 2023/6/18.
//

#include "ui/plugin/plugin.h"

namespace ui {
    Plugin::Plugin(const Descriptor* descriptor, Model* parent) :
            Model(parent),
            descriptor_(descriptor) {

    }

    void Plugin::LoadFile(const QString& file) {

    }
}
