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

#include "SettingsPopover.h"

SettingsPopover::SettingsPopover()
{
    pref_btn.property_text().set_value(_("Preferences"));
    shortcuts_btn.property_text().set_value(_("Shortcuts"));
    about_btn.property_text().set_value(_("About"));
    quit_btn.property_text().set_value(_("Quit"));

    v_box.set_margin_top(12);
    v_box.set_margin_bottom(12);
    v_box.set_margin_left(12);
    v_box.set_margin_right(12);
    v_box.pack_start(pref_btn);
    v_box.pack_start(shortcuts_btn);
    v_box.pack_start(separator);
    v_box.pack_start(about_btn);
    v_box.pack_start(quit_btn);

    v_box.show_all();

    add(v_box);
}
