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

#include "ShortcutsWindow.h"

ShortcutsWindow::ShortcutsWindow()
{
    set_title(_("Shortcuts"));
    set_default_size(520, 540);
    set_resizable(false);
    set_decorated(true);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ON_PARENT);

    this->signal_key_press_event().connect(sigc::mem_fun(*this, &ShortcutsWindow::on_key_press));

    section.property_visible().set_value(true);

    // APPLICATION SHORTCUTS
    show_settings_shortcut.property_title().set_value(_("Open preferences window"));
    show_settings_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    show_settings_shortcut.property_accelerator().set_value("<Control>P");

    show_key_bindings_shortcut.property_title().set_value(_("Open shortcuts window"));
    show_key_bindings_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    show_key_bindings_shortcut.property_accelerator().set_value("<Control>S");

    quit_app_shortcut.property_title().set_value(_("Quit application"));
    quit_app_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    quit_app_shortcut.property_accelerator().set_value("<Control>Q");

    app_group.add(show_settings_shortcut);
    app_group.add(show_key_bindings_shortcut);
    app_group.add(quit_app_shortcut);

    app_group.property_title().set_value(_("Application"));
    section.add(app_group);

    // TEXT ITEMS SHORTCUTS
    paste_item_shortcut.property_title().set_value(_("Paste item"));
    paste_item_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    paste_item_shortcut.property_accelerator().set_value("Return");

    select_items_shortcut.property_title().set_value(_("Select items"));
    select_items_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    select_items_shortcut.property_accelerator().set_value("<Shift>Up Down");

    item_prefix_suffix_shortcut.property_title().set_value(_("Set item prefix and suffix before pasting"));
    item_prefix_suffix_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    item_prefix_suffix_shortcut.property_accelerator().set_value("<Shift>Return");

    details_shortcut.property_title().set_value(_("Show item details"));
    details_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    details_shortcut.property_accelerator().set_value("<Alt>D");

    lowercase_shortcut.property_title().set_value(_("Change to lowercase"));
    lowercase_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    lowercase_shortcut.property_accelerator().set_value("<Alt>L");

    uppercase_shortcut.property_title().set_value(_("Change to uppercase"));
    uppercase_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    uppercase_shortcut.property_accelerator().set_value("<Alt>U");

    starmask_shortcut.property_title().set_value(_("Mask with *********"));
    starmask_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    starmask_shortcut.property_accelerator().set_value("<Alt>M");

    delete_item_shortcut.property_title().set_value(_("Delete item"));
    delete_item_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    delete_item_shortcut.property_accelerator().set_value("Delete");

    items_group.add(paste_item_shortcut);
    items_group.add(select_items_shortcut);
    items_group.add(item_prefix_suffix_shortcut);
    items_group.add(details_shortcut);
    items_group.add(lowercase_shortcut);
    items_group.add(uppercase_shortcut);
    items_group.add(starmask_shortcut);
    items_group.add(delete_item_shortcut);

    items_group.property_title().set_value(_("Text items"));
    section.add(items_group);

    // MAIN BOX
    v_box.pack_start(section);
    v_box.show_all();

    add(v_box);
}

bool ShortcutsWindow::on_key_press(GdkEventKey* key_event)
{
    if (key_event == nullptr)
    {
        return false;
    }

    if (key_event->keyval == GDK_KEY_Escape)
    {
        hide();
        return true;
    }

    return false;
}
