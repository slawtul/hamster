/*
 * Copyright (c) 2021 Slawek Tuleja
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HAMSTER_MAIN_WINDOW_H
#define HAMSTER_MAIN_WINDOW_H

#include <sys/stat.h>
#include <glibmm/i18n.h>
#include <gtkmm-3.0/gtkmm.h>
#include <thread>

#include <util/log/LogUtil.h>
#include <util/file/FileUtil.h>
#include <ui/window/WindowBody.h>
#include <ui/window/PreferencesWindow.h>
#include <ui/window/ShortcutsWindow.h>
#include <ui/dialog/AboutDialog.h>
#include <ui/popover/SettingsPopover.h>
#include <ui/popover/SettingsMenuButton.h>

struct MainWindow : public Gtk::ApplicationWindow
{
    MainWindow();

    Glib::RefPtr<Gio::Settings> ref_settings;

    Gtk::HeaderBar header_bar;
    SettingsMenuButton menu_btn;
    WindowBody win_body;
    AboutDialog about_dialog;
    ShortcutsWindow shortcuts_window;
    PreferencesWindow preferences_window;

    void show_about_dialog();
    void show_shortcuts_win();
    void show_preferences_win();
    void hide_about_dialog(int response_id);
    void close_app();

    bool on_delete_event(GdkEventAny* any_event) override;
    bool on_main_window_event(GdkEvent* gdk_event);
};

#endif //HAMSTER_MAIN_WINDOW_H
