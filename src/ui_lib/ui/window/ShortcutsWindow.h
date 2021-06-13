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

#ifndef HAMSTER_SHORTCUTS_WINDOW_H
#define HAMSTER_SHORTCUTS_WINDOW_H

#include <gtkmm-3.0/gtkmm.h>
#include <glibmm/i18n.h>

struct ShortcutsWindow:public Gtk::Window
{
    ShortcutsWindow();

    Gtk::ShortcutsSection section;
    Gtk::ShortcutsGroup app_group;
    Gtk::ShortcutsGroup items_group;

    Gtk::ShortcutsShortcut show_settings_shortcut;
    Gtk::ShortcutsShortcut show_key_bindings_shortcut;
    Gtk::ShortcutsShortcut quit_app_shortcut;

    Gtk::ShortcutsShortcut paste_item_shortcut;
    Gtk::ShortcutsShortcut select_items_shortcut;
    Gtk::ShortcutsShortcut item_prefix_suffix_shortcut;
    Gtk::ShortcutsShortcut lowercase_shortcut;
    Gtk::ShortcutsShortcut uppercase_shortcut;
    Gtk::ShortcutsShortcut starmask_shortcut;
    Gtk::ShortcutsShortcut details_shortcut;
    Gtk::ShortcutsShortcut delete_item_shortcut;

    Gtk::VBox v_box;

    bool on_key_press(GdkEventKey* key_event);
};

#endif //HAMSTER_SHORTCUTS_WINDOW_H
