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

#ifndef HAMSTER_WINDOW_BODY_H
#define HAMSTER_WINDOW_BODY_H

#include <glibmm/i18n.h>
#include <gtkmm-3.0/gtkmm.h>
#include <X11/Intrinsic.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <algorithm>
#include <regex>
#include <chrono>
#include <thread>
#include <fstream>
#include <util/text/TextUtil.h>
#include <util/log/LogUtil.h>
#include <util/ui/UIUtil.h>
#include <util/file/FileUtil.h>
#include <util/item/ItemUtil.h>
#include <ui/window/ItemDetailsWindow.h>

enum struct SelectionOrder
{
    SHIFT_UP,
    SHIFT_DOWN,
    NO_SELECTION
};

enum struct StoreType
{
    PRIMARY,
    SECONDARY
};

struct WindowBody : public Gtk::VBox
{
    WindowBody();

    Gtk::SearchEntry search_entry;
    Gtk::Separator se_separator;
    Gtk::ScrolledWindow scrolled_win;

    Gtk::VBox prefix_suffix_form;
    Gtk::HBox prefix_h_box;
    Gtk::HBox suffix_h_box;
    Gtk::Label prefix_label;
    Gtk::Label suffix_label;
    Gtk::Entry prefix_entry;
    Gtk::Entry suffix_entry;
    Gtk::Separator ps_separator;

    ItemModelColumns columns;
    Gtk::ListViewText item_list;
    Glib::RefPtr <Gtk::ListStore> ref_primary_item_store;   // All items go here
    Glib::RefPtr <Gtk::ListStore> ref_secondary_item_store; // Only searched items go here
    Glib::RefPtr <Gtk::Clipboard> ref_clipboard;
    Glib::RefPtr <Gio::Settings> ref_settings;

    int selection_counter;
    SelectionOrder selection_order;
    StoreType store_type;

    ItemDetailsWindow item_details_window;

    static void send_ctrl_v_key_event();

    // EVENTS HANDLING
    void on_clipboard_change(GdkEventOwnerChange* event);
    void on_search_change();
    bool on_search_entry_event(GdkEvent* gdk_event);

    void on_row_inserted(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter) const;
    void on_row_deleted(const Gtk::TreeModel::Path& path) const;
    void on_rows_reordered(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter, int* new_order) const;

    bool on_item_list_key_press(GdkEventKey* key_event);
    bool on_item_list_event(GdkEvent* gdk_event);
    bool on_item_list_focus_in(GdkEventFocus* focus_event);

    bool on_prefix_suffix_form_event(GdkEvent* gdk_event);

    // ACTIONS
    void show_item_details_window(const Glib::ustring& text);
    void transform_to_lowercase(std::vector <Gtk::TreePath>&& paths);
    void transform_to_lowercase(std::vector <Gtk::TreeRow>&& rows) const;
    void transform_to_uppercase(std::vector <Gtk::TreePath>&& paths);
    void transform_to_uppercase(std::vector <Gtk::TreeRow>&& rows) const;
    void mask_with_stars(std::vector <Gtk::TreePath>&& paths);
    void mask_with_stars(std::vector <Gtk::TreeRow>&& rows) const;
    bool move_item_top(Gtk::TreeNodeChildren&& rows, const Glib::ustring& text) const;
    void delete_items(std::vector <Gtk::TreePath>&& paths);
    void delete_items(std::vector <Gtk::TreeRow>&& rows) const;
    void delete_last_items(int store_sz, int max_list_size) const;

    // HELPER METHODS
    Gtk::TreeRow get_row(const Gtk::TreeModel::Path& path);
    std::vector <Gtk::TreeModel::Path> get_selected_paths();
    std::vector <Gtk::TreeRow> find_primary_store_rows(std::vector <Gtk::TreePath>&& paths);
    std::vector <Gtk::TreeRow> convert_to_rows(std::vector <Gtk::TreePath>& paths);
    void past_items(const std::string& prefix, const std::string& suffix, bool decorate_any_item);
    void append_welcome_items() const;
};

#endif //HAMSTER_WINDOW_BODY_H
