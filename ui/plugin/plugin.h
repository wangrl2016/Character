//
// Created by wangrl2016 on 2023/6/18.
//

#ifndef CHARACTER_PLUGIN_H
#define CHARACTER_PLUGIN_H

#include "ui/model/model.h"

namespace ui {
    // Abstract representation of a plugin. such a plugin can be an
    // Instrument, Effect, Tool plugin etc.
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

        Plugin(const Descriptor* descriptor,
               Model* parent);

        inline PluginType type() const {
            return descriptor_->type;
        }

        inline const Descriptor* descriptor() const {
            return descriptor_;
        }

        virtual void LoadFile(const QString& file);

    private:
        const Descriptor* descriptor_;
    };
}

#endif //CHARACTER_PLUGIN_H
