gtkmm_dep=dependency('gtkmm-3.0')

util=static_library('util',dependencies:[gtkmm_dep],
    sources:[
        'util/json/json.hpp',
        'util/file/FileUtil.h','util/file/FileUtil.cpp',
        'util/item/ItemUtil.h','util/item/ItemUtil.cpp',
        'util/log/LogUtil.h','util/log/LogUtil.cpp',
        'util/text/TextUtil.h','util/text/TextUtil.cpp',
        'util/ui/UIUtil.h','util/ui/UIUtil.cpp',
    ]
)

util_dep=declare_dependency(
    include_directories:include_directories('.'),
    link_with:util
)
