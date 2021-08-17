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

#include "WindowBody.h"

WindowBody::WindowBody()
        : item_list(1, false, Gtk::SELECTION_MULTIPLE), //Where '1' means: show one column only (column name: 'item_display_value')
          selection_order{SelectionOrder::SHIFT_DOWN},
          store_type{StoreType::PRIMARY}
{
    ref_clipboard = Gtk::Clipboard::get();
    ref_clipboard->signal_owner_change().connect(sigc::mem_fun(*this, &WindowBody::on_clipboard_change));

    ref_settings = Gio::Settings::create("com.github.slawtul.hamster");

    search_entry.signal_search_changed().connect(sigc::mem_fun(*this, &WindowBody::on_search_change));
    search_entry.signal_event().connect(sigc::mem_fun(*this, &WindowBody::on_search_entry_event));
    search_entry.set_margin_top(3);
    search_entry.set_margin_right(3);
    search_entry.set_margin_bottom(3);
    search_entry.set_margin_left(3);
    search_entry.show();
    se_separator.show();

    prefix_label.set_label(_("Prefix:"));
    prefix_label.show();
    prefix_entry.set_width_chars(30);
    prefix_entry.set_max_length(128);
    prefix_entry.show();
    suffix_label.set_label(_("Suffix:"));
    suffix_label.show();
    suffix_entry.set_width_chars(30);
    suffix_entry.set_max_length(128);
    suffix_entry.show();

    prefix_h_box.pack_start(prefix_label);
    prefix_h_box.pack_start(prefix_entry);
    prefix_h_box.set_margin_bottom(4);
    prefix_h_box.show();

    suffix_h_box.pack_start(suffix_label);
    suffix_h_box.pack_start(suffix_entry);
    suffix_h_box.show();

    prefix_suffix_form.signal_event().connect(sigc::mem_fun(*this, &WindowBody::on_prefix_suffix_form_event));
    prefix_suffix_form.pack_start(prefix_h_box);
    prefix_suffix_form.pack_start(suffix_h_box);
    prefix_suffix_form.set_border_width(4);
    prefix_suffix_form.hide();
    ps_separator.hide();

    pack_start(search_entry);
    pack_start(se_separator);
    pack_start(scrolled_win);
    pack_start(ps_separator);
    pack_start(prefix_suffix_form);

    scrolled_win.set_size_request(-1, 640);
    scrolled_win.add(item_list);
    scrolled_win.show();

    ref_primary_item_store = Gtk::ListStore::create(columns);
    ref_secondary_item_store = Gtk::ListStore::create(columns);

    auto ref_tree_model = (Glib::RefPtr<Gtk::TreeModel>) ref_primary_item_store;
    ref_tree_model->signal_row_inserted().connect(sigc::mem_fun(*this, &WindowBody::on_row_inserted));
    ref_tree_model->signal_row_deleted().connect(sigc::mem_fun(*this, &WindowBody::on_row_deleted));
    ref_tree_model->signal_rows_reordered().connect(sigc::mem_fun(*this, &WindowBody::on_rows_reordered));

    item_list.set_model(ref_primary_item_store);
    item_list.set_headers_visible(false);
    item_list.set_enable_search(false);
    item_list.set_search_entry(search_entry);
    item_list.signal_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_event));
    item_list.signal_key_press_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_key_press));
    item_list.signal_focus_in_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_focus_in));
    item_list.show();

    if (ref_settings->get_boolean("first-run")) {
        append_welcome_items();
        ref_settings->set_boolean("first-run", false);
    }
    else if (ref_settings->get_boolean("save-list")) {
        FileUtil fu{};
        LogUtil lu{};

        std::fstream fs{};
        fs.open(fu.items_json_filepath(), std::ios::in | std::ios::out | std::ios::app);

        if (fs.is_open()) {
            fs.close();
            lu.log_if_debug("\nFile found: " + fu.items_json_filepath());

            ItemUtil iu{};
            const auto items_vec = iu.json_items_to_vec(fu.read_items_from_file());

            UIUtil ui_util{};
            ui_util.append_to_store(ref_primary_item_store, items_vec);
        }
        else {
            lu.log_if_debug("\nFile NOT found: " + fu.items_json_filepath());
        }
    }

    selection_counter = 0;

    show();
}

void WindowBody::append_welcome_items() const
{
    const auto row0 = *(ref_primary_item_store->append());
    row0[columns.item_value] = _("Welcome to Hamster !");
    row0[columns.item_display_value] = _("Welcome to Hamster !");

    const auto row1 = *(ref_primary_item_store->append());
    row1[columns.item_value] = "---";
    row1[columns.item_display_value] = "---";

    const auto row2 = *(ref_primary_item_store->append());
    row2[columns.item_value] = _("Press <Ctrl+S> to open shortcuts window");
    row2[columns.item_display_value] = _("Press <Ctrl+S> to open shortcuts window");

    const auto row3 = *(ref_primary_item_store->append());
    row3[columns.item_value] = _("Press <Ctrl+P> to open preferences window");
    row3[columns.item_display_value] = _("Press <Ctrl+P> to open preferences window");
}

bool WindowBody::move_item(Gtk::TreeNodeChildren&& rows, const Glib::ustring& text) const
{
    for (const auto& row:rows) {
        if (text.length() == row.get_value(columns.item_value).length() && text == row.get_value(columns.item_value)) {
            ref_primary_item_store->move(row, rows[0]);
            return true;
        }
    }
    return false;
}

void WindowBody::delete_items(std::vector<Gtk::TreePath>&& paths)
{
    //Rows can be deleted using TreeRowReference only
    std::vector<Gtk::TreeRowReference> row_refs{};
    row_refs.reserve(paths.size());
    for (const auto& path:paths) {
        row_refs.emplace_back(item_list.get_model(), path);
    }

    auto model = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(item_list.get_model());
    for (const auto& row_ref:row_refs) {
        auto iterator = model->get_iter(row_ref.get_path());
        model->erase(iterator);
    }
}

void WindowBody::delete_items(std::vector<Gtk::TreeRow>&& rows) const
{
    for (const auto& row:rows) {
        ref_primary_item_store->erase(row);
    }
}

void WindowBody::delete_last_items(int store_sz, int max_list_size) const
{
    const auto diff_sz = store_sz - max_list_size;
    if (diff_sz > 0) {
        for (int i = 1; i <= diff_sz; ++i) {
            ref_primary_item_store->erase(ref_primary_item_store->children()[store_sz - i]);
        }
    }
}

void WindowBody::transform_to_lowercase(std::vector<Gtk::TreePath>&& paths)
{
    transform_to_lowercase(convert_to_rows(paths));
}

void WindowBody::transform_to_lowercase(std::vector<Gtk::TreeRow>&& rows) const
{
    for (const auto& row:rows) {
        row[columns.item_display_value] = row.get_value(columns.item_display_value).lowercase();
        row[columns.item_value] = row.get_value(columns.item_value).lowercase();
    }
}

void WindowBody::transform_to_uppercase(std::vector<Gtk::TreePath>&& paths)
{
    transform_to_uppercase(convert_to_rows(paths));
}

void WindowBody::transform_to_uppercase(std::vector<Gtk::TreeRow>&& rows) const
{
    for (const auto& row:rows) {
        row[columns.item_display_value] = row.get_value(columns.item_display_value).uppercase();
        row[columns.item_value] = row.get_value(columns.item_value).uppercase();
    }
}

void WindowBody::mask_with_stars(std::vector<Gtk::TreePath>&& paths)
{
    mask_with_stars(convert_to_rows(paths));
}

void WindowBody::mask_with_stars(std::vector<Gtk::TreeRow>&& rows) const
{
    TextUtil tu{};
    for (const auto& row:rows) {
        row[columns.item_display_value] = tu.mask_str(row.get_value(columns.item_display_value));
        row[columns.item_value] = row.get_value(columns.item_value);
    }
}

void WindowBody::on_search_change()
{
    ref_secondary_item_store->clear();
    store_type = StoreType::PRIMARY;
    if (search_entry.get_text().length() >= 2) {
        TextUtil tu{};
        auto search_str = (std::string) search_entry.get_text();

        //Escape non-alpha chars because we want treat them as regular chars
        //Eg. user wants to use '.' as dot not as 'any' regexp char
        //Eg. user wants to use '*' as star not as 'zero or more' regexp character,etc...
        auto esc_str = tu.escape_nonalpha(search_str);
        const auto pattern = std::regex{esc_str, std::regex_constants::icase};
        std::smatch sm{};

        for (const auto& row:ref_primary_item_store->children()) {
            if (std::regex_search(row.get_value(columns.item_value).raw(), sm, pattern)) {
                const auto s_row = *(ref_secondary_item_store->append());
                s_row[columns.item_value] = row.get_value(columns.item_value);
                s_row[columns.item_display_value] = row.get_value(columns.item_display_value);
            }
        }
        item_list.set_model(ref_secondary_item_store);
        store_type = StoreType::SECONDARY;
    }
    else {
        store_type = StoreType::PRIMARY;
        item_list.set_model(ref_primary_item_store);
    }
}

void WindowBody::on_clipboard_change(GdkEventOwnerChange* event)
{
    if (event == nullptr) {
        return;
    }

    //Waiting for new copied text...
    auto text = ref_clipboard->wait_for_text();

    TextUtil tu{};
    if (tu.has_only_spaces(text)) {
        return;
    }
    if (ref_settings->get_boolean("eliminate-spaces")) {
        text = tu.trim_str(text);
    }

    //If copied text already exists move it to the top and do nothing else...
    if (move_item(ref_primary_item_store->children(), text)) {
        return;
    }

    const auto row = *(ref_primary_item_store->prepend());
    row[columns.item_value] = text;                                     //Save in memory original text value
    row[columns.item_display_value] = tu.calculate_display_value(text); //Show short,one liner text value
    item_list.set_cursor(ref_primary_item_store->get_path(row));

    //Delete if too many...
    delete_last_items((int) ref_primary_item_store->children().size(), (int) ref_settings->get_double("item-list-size"));

    LogUtil lu{};
    lu.log_if_debug("\nStored items: %d", ref_primary_item_store->children().size());
}

void WindowBody::on_row_inserted([[maybe_unused]] const Gtk::TreeModel::Path& path, [[maybe_unused]] const Gtk::TreeModel::iterator& iter) const
{
    if (ref_settings->get_boolean("save-list")) {
        ItemUtil iu{};
        const auto items_vec = iu.items_to_vec(ref_primary_item_store->children());

        FileUtil fu{};
        fu.write_items_to_file(items_vec);
    }
}

void WindowBody::on_row_deleted([[maybe_unused]] const Gtk::TreeModel::Path& path) const
{
    if (ref_settings->get_boolean("save-list")) {
        ItemUtil iu{};
        const auto items_vec = iu.items_to_vec(ref_primary_item_store->children());

        FileUtil fu{};
        fu.write_items_to_file(items_vec);
    }
}

void WindowBody::on_rows_reordered([[maybe_unused]] const Gtk::TreeModel::Path& path, [[maybe_unused]] const Gtk::TreeModel::iterator& iter, [[maybe_unused]] int* new_order) const
{
    if (ref_settings->get_boolean("save-list")) {
        ItemUtil iu{};
        const auto items_vec = iu.items_to_vec(ref_primary_item_store->children());

        FileUtil fu{};
        fu.write_items_to_file(items_vec);
    }
}

bool WindowBody::on_item_list_focus_in(GdkEventFocus* focus_event)
{
    if (focus_event == nullptr) {
        return false;
    }

    //Select first row if no selected rows
    const auto ref_item_store = item_list.get_model();
    if (!ref_item_store->children().empty() && get_selected_paths().empty()) {
        item_list.set_cursor(ref_item_store->get_path(ref_item_store->children()[0]));
    }
    return true;
}

bool WindowBody::on_item_list_event(GdkEvent* gdk_event)
{
    //Events with 'Enter' key cannot be fetched with 'signal_key_press_event' in ListTextView widget
    //In this widget 'Enter' means: row edit mode
    if (gdk_event == nullptr) {
        return false;
    }

    const auto key = gdk_event->key.keyval;
    const auto type = gdk_event->type;
    const auto state = gdk_event->key.state;

    LogUtil lu{};

    const auto is_SHIFT_pressed = (state == 1 || state == 3 || state == 17 || state == 19);

    //ROWS SELECTION HANDLING
    if (get_selected_paths().size() == 1) {
        selection_counter = 0;
        selection_order = SelectionOrder::NO_SELECTION;
    }

    //'SHIFT+UP' select up
    if (type == GDK_KEY_PRESS && key == GDK_KEY_Up && is_SHIFT_pressed) {
        lu.log_if_debug("\nSelection order up");
        selection_order = SelectionOrder::SHIFT_UP;
        ++selection_counter;
    }

    //'SHIFT+DOWN' select down
    if (type == GDK_KEY_PRESS && key == GDK_KEY_Down && is_SHIFT_pressed) {
        lu.log_if_debug("\nSelection order down");
        selection_order = SelectionOrder::SHIFT_DOWN;
        --selection_counter;
    }

    selection_order = selection_counter < 0 ? SelectionOrder::SHIFT_DOWN : SelectionOrder::SHIFT_UP;

    //'SHIFT+ENTER' paste but before show prefix and suffix entry fields
    if (type == GDK_KEY_PRESS && key == GDK_KEY_Return && is_SHIFT_pressed) {
        lu.log_if_debug("\nOpen prefix/suffix form");
        ps_separator.show();
        prefix_suffix_form.show();
        prefix_entry.grab_focus();
        return true;
    }

    //'ENTER' paste items
    if (type == GDK_KEY_PRESS && key == GDK_KEY_Return) {
        if (ref_settings->get_boolean("set-focus-on-search-input")) {
            search_entry.grab_focus();
        }
        ps_separator.hide();
        prefix_suffix_form.hide();
        this->get_window()->iconify();

        auto prefix = (std::string) ref_settings->get_string("item-prefix");
        auto suffix = (std::string) ref_settings->get_string("item-suffix");

        TextUtil tu{};
        prefix = tu.convert_to_newline_or_tab(prefix);
        suffix = tu.convert_to_newline_or_tab(suffix);

        past_items(prefix, suffix, false); //'false'-do not add prefix and suffix when one item selected only

        if (ref_settings->get_boolean("clear-search-input")) {
            search_entry.set_text("");
        }
        return true;
    }

    return false;
}

bool WindowBody::on_prefix_suffix_form_event(GdkEvent* gdk_event)
{
    if (gdk_event == nullptr) {
        return false;
    }

    const auto key = gdk_event->key.keyval;
    const auto type = gdk_event->type;
    const auto state = gdk_event->key.state;

    //'ESCAPE' close widget
    if (type == GDK_KEY_RELEASE && key == GDK_KEY_Escape) {
        ps_separator.hide();
        prefix_suffix_form.hide();
        item_list.grab_focus();
        return true;
    }

    //'ENTER' paste items
    if (type == GDK_KEY_RELEASE && key == GDK_KEY_Return && (state == 0 || state == 2 || state == 16 || state == 18)) {
        item_list.grab_focus();
        if (ref_settings->get_boolean("set-focus-on-search-input")) {
            search_entry.grab_focus();
        }

        ps_separator.hide();
        prefix_suffix_form.hide();
        this->get_window()->iconify();

        auto prefix = (std::string) prefix_entry.get_text();
        auto suffix = (std::string) suffix_entry.get_text();

        TextUtil tu{};
        prefix = tu.convert_to_newline_or_tab(prefix);
        suffix = tu.convert_to_newline_or_tab(suffix);

        past_items(prefix, suffix, true); //'true'-add prefix and suffix even if one item selected

        if (ref_settings->get_boolean("clear-search-input")) {
            search_entry.set_text("");
        }
        return true;
    }

    return false;
}

bool WindowBody::on_item_list_key_press(GdkEventKey* key_event)
{
    if (key_event == nullptr) {
        return false;
    }

    const auto key = key_event->keyval;

    //'ESCAPE' OR 'TAB' move to search entry
    if (key == GDK_KEY_Escape || key == GDK_KEY_Tab || key == GDK_KEY_slash) {
        search_entry.grab_focus();
        return true;
    }

    //'DELETE' item
    if (key == GDK_KEY_Delete) {
        if (store_type == StoreType::SECONDARY) {
            delete_items(find_primary_store_rows(get_selected_paths())); //secondary store selected paths
        }
        delete_items(get_selected_paths());
        return true;
    }

    const auto state = key_event->state;
    if (state == 8 || state == 10 || state == 24 || state == 26) {
        //'ALT+D' show item details window
        if (key == GDK_KEY_d || key == GDK_KEY_D) {
            show_item_details_window(get_row(get_selected_paths()[0]).get_value(columns.item_value));
            return true;
        }

        //'ALT+L' transform to lowercase
        if (key == GDK_KEY_l || key == GDK_KEY_L) {
            if (store_type == StoreType::SECONDARY) {
                transform_to_lowercase(find_primary_store_rows(get_selected_paths())); //secondary store selected paths
            }
            transform_to_lowercase(get_selected_paths());
            return true;
        }

        //'ALT+U' transform to uppercase
        if (key == GDK_KEY_u || key == GDK_KEY_U) {
            if (store_type == StoreType::SECONDARY) {
                transform_to_uppercase(find_primary_store_rows(get_selected_paths())); //secondary store selected paths
            }
            transform_to_uppercase(get_selected_paths());
            return true;
        }

        //'ALT+M' mask with *********
        if (key == GDK_KEY_m || key == GDK_KEY_M) {
            if (store_type == StoreType::SECONDARY) {
                mask_with_stars(find_primary_store_rows(get_selected_paths())); //secondary store selected paths
            }
            mask_with_stars(get_selected_paths());
            return true;
        }
    }

    return false;
}

bool WindowBody::on_search_entry_event(GdkEvent* gdk_event)
{
    if (gdk_event == nullptr) {
        return false;
    }

    const auto type = gdk_event->type;
    const auto key = gdk_event->key.keyval;

    //'DOWN' move to list
    if (type == GDK_KEY_PRESS && key == GDK_KEY_Down) {
        item_list.grab_focus();
        return true;
    }

    //'ESC' clear search entry or minimize application
    if (type == GDK_KEY_PRESS && key == GDK_KEY_Escape) {
        search_entry.get_text_length() == 0 ? this->get_window()->iconify() : search_entry.set_text("");
        search_entry.grab_focus();
        return true;
    }

    return false;
}

void WindowBody::send_ctrl_v_key_event()
{
    const auto display = XOpenDisplay(nullptr);
    const auto left_control_key = XKeysymToKeycode(display, XK_Control_L);
    const auto v_key = XKeysymToKeycode(display, XK_v);

    XTestGrabControl(display, True);
    XTestFakeKeyEvent(display, left_control_key, True, 0);
    XTestFakeKeyEvent(display, v_key, True, 0);  //True means key press
    XTestFakeKeyEvent(display, v_key, False, 0); //False means key release
    XTestFakeKeyEvent(display, left_control_key, False, 0);

    XSync(display, False);
    XTestGrabControl(display, False);
}

void WindowBody::show_item_details_window(const Glib::ustring& text)
{
    item_details_window.set_text(text);
    item_details_window.show_all();
    item_details_window.present();
}

void WindowBody::past_items(const std::string& prefix, const std::string& suffix, bool decorate_any_item)
{
    const auto path_list = get_selected_paths();
    auto selected_paths = path_list; //Reverse a copied vector

    if (selection_order == SelectionOrder::SHIFT_UP) {
        std::reverse(selected_paths.begin(), selected_paths.end());
    }

    Glib::ustring text_to_paste = "";
    for (const auto& path:selected_paths) {
        const auto row = get_row(path);
        const auto item_value = row.get_value(columns.item_value);

        if (decorate_any_item) {
            text_to_paste += prefix + item_value + suffix;
        }
        else {
            text_to_paste += path_list.size() == 1 ? item_value : prefix + item_value + suffix;
        }
    }

    ref_clipboard->set_text(text_to_paste); //Send text to clipboard...

    std::this_thread::sleep_for(std::chrono::milliseconds((short) ref_settings->get_double("delay-pasting")));
    send_ctrl_v_key_event();
}

//HELPER METHODS
std::vector<Gtk::TreeModel::Path> WindowBody::get_selected_paths()
{
    return item_list.get_selection()->get_selected_rows();
}

Gtk::TreeRow WindowBody::get_row(const Gtk::TreeModel::Path& path)
{
    return *(item_list.get_model()->get_iter(path));
}

std::vector<Gtk::TreeRow> WindowBody::convert_to_rows(std::vector<Gtk::TreePath>& paths)
{
    std::vector<Gtk::TreeRow> rows;
    rows.reserve(paths.size());

    for (const auto& path:paths) {
        rows.emplace_back(get_row(path));
    }
    return rows;
}

std::vector<Gtk::TreeRow> WindowBody::find_primary_store_rows(std::vector<Gtk::TreePath>&& secondary_store_paths)
{
    std::vector<Gtk::TreeRow> rows_to_update{};
    rows_to_update.reserve(secondary_store_paths.size());

    for (const auto& path:secondary_store_paths) {
        const auto s_row = get_row(path);
        for (const auto& row:ref_primary_item_store->children()) {
            const auto s_rv = s_row.get_value(columns.item_value);
            const auto rv = row.get_value(columns.item_value);
            if (s_rv.length() == rv.length() && s_rv == rv) {
                rows_to_update.emplace_back(row);
                break;
            }
        }
    }
    return rows_to_update;
}
