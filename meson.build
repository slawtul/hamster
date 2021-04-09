project('com.github.slawtul.hamster', 'cpp', version: '1.0.1', default_options : ['warning_level=3', 'cpp_std=c++14'])

gnome = import('gnome')
i18n = import('i18n')

add_global_arguments('-DGETTEXT_PACKAGE="@0@"'.format (meson.project_name()), language:'cpp')

subdir('src/util_lib')
subdir('src/ui_lib')

executable(
    meson.project_name(),
    'src/hamster_run.cpp',
    dependencies : [util_dep, ui_dep],
    install: true
)

subdir('data')
subdir('po')

meson.add_install_script('meson/post_install.py')
