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

#ifndef HAMSTER_PREFERENCES_WINDOW_H
#define HAMSTER_PREFERENCES_WINDOW_H

#include <sys/stat.h>
#include <glibmm/i18n.h>
#include <gtkmm-3.0/gtkmm.h>
#include <util/file/FileUtil.h>

struct PreferencesWindow : public Gtk::Window
{
    PreferencesWindow();

    Glib::RefPtr<Gio::Settings> ref_settings;

    Gtk::VBox v_box;

    Gtk::Label app_label;
    Gtk::Label items_label;
    Gtk::Label set_size_label;
    Gtk::Label item_label;

    Gtk::VBox app_box;
    Gtk::VBox items_box;
    Gtk::VBox item_box;

    Gtk::CheckButton run_automatically_check;
    Gtk::CheckButton run_minimize_check;
    Gtk::CheckButton focus_search_input_check;
    Gtk::Label delay_pasting_label;
    Gtk::Scale delay_pasting_scale;

    Gtk::CheckButton eliminate_spaces_check;
    Gtk::CheckButton save_list_check;
    Gtk::Scale item_list_size_scale;

    Gtk::Box prefix_box;
    Gtk::Box suffix_box;
    Gtk::Label prefix_label;
    Gtk::Label suffix_label;
    Gtk::Entry item_prefix;
    Gtk::Entry item_suffix;

    bool on_key_press(GdkEventKey* key_event);
    void on_run_automatically_click();
    void on_run_minimize_click();
    void on_focus_search_input_click();
    void on_delay_pasting_change();
    void on_eliminate_spaces_click();
    void on_save_list_click();
    void on_item_list_size_change();
    void on_item_prefix_change() const;
    void on_item_suffix_change() const;
};

#endif //HAMSTER_PREFERENCES_WINDOW_H
