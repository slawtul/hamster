gtkmm_dep=dependency('gtkmm-3.0')
x11_dep  =dependency('x11')
xtst_dep =dependency('xtst')
xext_dep =dependency('xext')

ui=static_library('ui',dependencies:[gtkmm_dep,x11_dep,xtst_dep,xext_dep,util_dep],
    sources:[
        'ui/window/MainWindow.h','ui/window/MainWindow.cpp',
        'ui/window/WindowBody.h','ui/window/WindowBody.cpp',
        'ui/window/PreferencesWindow.h','ui/window/PreferencesWindow.cpp',
        'ui/window/ShortcutsWindow.h','ui/window/ShortcutsWindow.cpp',
        'ui/window/ItemDetailsWindow.h','ui/window/ItemDetailsWindow.cpp',
        'ui/popover/SettingsMenuButton.h','ui/popover/SettingsMenuButton.cpp',
        'ui/popover/SettingsPopover.h','ui/popover/SettingsPopover.cpp',
        'ui/dialog/AboutDialog.h','ui/dialog/AboutDialog.cpp',
    ]
)

ui_dep=declare_dependency(
    dependencies:[gtkmm_dep],
    include_directories:include_directories('.'),
    link_with:ui
)
