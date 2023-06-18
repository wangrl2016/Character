//
// Created by wangrl2016 on 2023/6/18.
//

#ifndef CHARACTER_PLUGIN_H
#define CHARACTER_PLUGIN_H

#include "ui/model/model.h"

namespace ui {
    class Plugin : public Model {
    Q_OBJECT
    public:
        enum PluginType {
            kImportFilter,  // filter for importing a file
            kExportFilter,  // filter for exporting a file
        };

        struct Descriptor {
            const char* name;
            const char* display_name;
            const char* description;
            const char* author;
            int version;
            PluginType type;
            const char* supported_file_types;   // csv list of extensions
        };
    };
}

#endif //CHARACTER_PLUGIN_H
