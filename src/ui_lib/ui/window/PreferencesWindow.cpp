/*
 * Copyright (c) 2021 Slawek Tuleja
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
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

#include "PreferencesWindow.h"

PreferencesWindow::PreferencesWindow()
{
    set_title(_("Preferences"));
    set_default_size(-1, -1);
    set_resizable(false);
    set_decorated(true);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ON_PARENT);
    this->signal_key_press_event().connect(sigc::mem_fun(*this, &PreferencesWindow::on_key_press));

    ref_settings = Gio::Settings::create("com.github.slawtul.hamster");

    // APPLICATION PREFERENCES
    app_label.set_markup(_("<b>Application</b>"));
    app_label.set_halign(Gtk::ALIGN_START);
    app_label.set_margin_bottom(6);
    app_label.set_margin_left(12);
    app_label.set_margin_top(6);

    run_automatically_check.set_label(_("Run automatically on system startup"));
    run_automatically_check.set_active(ref_settings->get_boolean("run-automatically"));
    run_automatically_check.signal_toggled().connect(sigc::mem_fun(*this, &PreferencesWindow::on_run_automatically_click));

    run_minimize_check.set_label(_("Run minimize"));
    run_minimize_check.set_active(ref_settings->get_boolean("run-minimize"));
    run_minimize_check.signal_toggled().connect(sigc::mem_fun(*this, &PreferencesWindow::on_run_minimize_click));

    focus_search_input_check.set_label(_("Set focus on a search input after pasting"));
    focus_search_input_check.set_active(ref_settings->get_boolean("set-focus-on-search-input"));
    focus_search_input_check.signal_toggled().connect(sigc::mem_fun(*this, &PreferencesWindow::on_focus_search_input_click));

    clear_search_input_check.set_label(_("Clear a search input after pasting"));
    clear_search_input_check.set_active(ref_settings->get_boolean("clear-search-input"));
    clear_search_input_check.signal_toggled().connect(sigc::mem_fun(*this, &PreferencesWindow::on_clear_search_input_click));

    delay_pasting_label.set_label(_("Delay pasting [ms]"));
    delay_pasting_label.set_margin_top(6);

    delay_pasting_scale.set_digits(0);
    delay_pasting_scale.set_range(100, 1000);
    delay_pasting_scale.add_mark(100, Gtk::POS_TOP, "");
    delay_pasting_scale.add_mark(200, Gtk::POS_TOP, "");
    delay_pasting_scale.add_mark(400, Gtk::POS_TOP, "");
    delay_pasting_scale.add_mark(600, Gtk::POS_TOP, "");
    delay_pasting_scale.add_mark(800, Gtk::POS_TOP, "");
    delay_pasting_scale.add_mark(1000, Gtk::POS_TOP, "");
    delay_pasting_scale.set_value(ref_settings->get_double("delay-pasting"));
    delay_pasting_scale.signal_value_changed().connect(sigc::mem_fun(*this, &PreferencesWindow::on_delay_pasting_change));

    app_box.set_margin_left(30);
    app_box.set_margin_right(30);
    app_box.set_spacing(6);
    app_box.pack_start(run_automatically_check);
    app_box.pack_start(run_minimize_check);
    app_box.pack_start(focus_search_input_check);
    app_box.pack_start(clear_search_input_check);
    app_box.pack_start(delay_pasting_label);
    app_box.pack_start(delay_pasting_scale);
    app_box.show_all();

    // ITEMS PREFERENCES
    items_label.set_markup(_("<b>Text items</b>"));
    items_label.set_halign(Gtk::ALIGN_START);
    items_label.set_margin_top(24);
    items_label.set_margin_bottom(6);
    items_label.set_margin_left(12);

    eliminate_spaces_check.set_label(_("Eliminate leading and trailing spaces"));
    eliminate_spaces_check.set_active(ref_settings->get_boolean("eliminate-spaces"));
    eliminate_spaces_check.signal_toggled().connect(sigc::mem_fun(*this, &PreferencesWindow::on_eliminate_spaces_click));

    save_list_check.set_label(_("Save list to a file"));
    save_list_check.set_active(ref_settings->get_boolean("save-list"));
    save_list_check.signal_toggled().connect(sigc::mem_fun(*this, &PreferencesWindow::on_save_list_click));

    set_size_label.set_markup(_("Item list size"));
    set_size_label.set_margin_top(6);

    item_list_size_scale.set_digits(0);
    item_list_size_scale.set_range(32, 1024);
    item_list_size_scale.add_mark(32, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(64, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(128, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(256, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(512, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(768, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(1024, Gtk::POS_TOP, "");
    item_list_size_scale.set_value(ref_settings->get_double("item-list-size"));
    item_list_size_scale.signal_value_changed().connect(sigc::mem_fun(*this, &PreferencesWindow::on_item_list_size_change));

    items_box.set_margin_left(30);
    items_box.set_margin_right(30);
    items_box.set_spacing(6);
    items_box.pack_start(eliminate_spaces_check);
    items_box.pack_start(save_list_check);
    items_box.pack_start(set_size_label);
    items_box.pack_start(item_list_size_scale);
    items_box.show_all();

    // ITEM PREFERENCES
    item_label.set_markup(_("<b>Paste selected items with:</b>"));
    item_label.set_halign(Gtk::ALIGN_START);
    item_label.set_margin_top(24);
    item_label.set_margin_bottom(12);
    item_label.set_margin_left(12);
    item_prefix.set_margin_bottom(6);
    item_prefix.set_margin_left(24);
    item_prefix.property_text().set_value(ref_settings->get_string("item-prefix"));
    item_prefix.set_width_chars(32);
    item_prefix.set_max_length(128);
    item_prefix.signal_changed().connect(sigc::mem_fun(*this, &PreferencesWindow::on_item_prefix_change));

    prefix_label.set_label(_("Prefix:"));
    suffix_label.set_label(_("Suffix:"));

    prefix_box.set_halign(Gtk::ALIGN_START);
    prefix_box.pack_start(prefix_label);
    prefix_box.pack_end(item_prefix);
    prefix_box.show_all();

    item_suffix.property_text().set_value(ref_settings->get_string("item-suffix"));
    item_suffix.set_width_chars(32);
    item_suffix.set_max_length(128);
    item_suffix.signal_changed().connect(sigc::mem_fun(*this, &PreferencesWindow::on_item_suffix_change));
    item_suffix.set_margin_left(24);

    suffix_box.set_halign(Gtk::ALIGN_START);
    suffix_box.pack_start(suffix_label);
    suffix_box.pack_start(item_suffix);
    suffix_box.show_all();

    item_box.set_margin_left(30);
    item_box.set_margin_right(30);
    item_box.pack_start(prefix_box);
    item_box.pack_start(suffix_box);
    item_box.show_all();

    // MAIN BOX
    v_box.set_margin_top(12);
    v_box.set_margin_right(12);
    v_box.set_margin_bottom(24);
    v_box.set_margin_left(12);
    v_box.pack_start(app_label);
    v_box.pack_start(app_box);
    v_box.pack_start(items_label);
    v_box.pack_start(items_box);
    v_box.pack_start(item_label);
    v_box.pack_start(item_box);

    v_box.show_all();

    add(v_box);
}

bool PreferencesWindow::on_key_press(GdkEventKey* key_event)
{
    if (key_event == nullptr) {
        return false;
    }
    if (key_event->keyval == GDK_KEY_Escape) {
        hide();
        return true;
    }
    return false;
}

void PreferencesWindow::on_run_automatically_click()
{
    const auto run_automatically = run_automatically_check.get_active();
    ref_settings->set_boolean("run-automatically", run_automatically);
    FileUtil fu {};
    if (run_automatically)
    {
        std::ifstream src {fu.user_apps_dir + fu.desktop_filename};
        std::ofstream dst {fu.autostart_dir() + fu.desktop_filename};
        dst << src.rdbuf();
        src.close();
        dst.close();
    }
    else
    {
        const auto desktop_filepath = fu.autostart_dir() + fu.desktop_filename;
        std::remove(desktop_filepath.c_str());
    }
}

void PreferencesWindow::on_run_minimize_click()
{
    ref_settings->set_boolean("run-minimize", run_minimize_check.get_active());
}

void PreferencesWindow::on_focus_search_input_click()
{
    ref_settings->set_boolean("set-focus-on-search-input", focus_search_input_check.get_active());
}

void PreferencesWindow::on_clear_search_input_click()
{
    ref_settings->set_boolean("clear-search-input", clear_search_input_check.get_active());
}

void PreferencesWindow::on_delay_pasting_change()
{
    ref_settings->set_double("delay-pasting", delay_pasting_scale.get_value());
}

void PreferencesWindow::on_eliminate_spaces_click()
{
    ref_settings->set_boolean("eliminate-spaces", eliminate_spaces_check.get_active());
}

void PreferencesWindow::on_save_list_click()
{
    ref_settings->set_boolean("save-list", save_list_check.get_active());
    if (!save_list_check.get_active()) {
        FileUtil fu {};
        std::remove(fu.items_json_filepath().c_str());
    }
}

void PreferencesWindow::on_item_list_size_change()
{
    ref_settings->set_double("item-list-size", item_list_size_scale.get_value());
}

void PreferencesWindow::on_item_prefix_change() const
{
    ref_settings->set_string("item-prefix", item_prefix.get_text());
}

void PreferencesWindow::on_item_suffix_change() const
{
    ref_settings->set_string("item-suffix", item_suffix.get_text());
}
