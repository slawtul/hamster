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

#include "ItemDetailsWindow.h"

ItemDetailsWindow::ItemDetailsWindow()
{
    set_title(_("Item details"));
    set_default_size(640, 520);
    set_resizable(true);
    set_decorated(true);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ON_PARENT);

    this->signal_key_press_event().connect(sigc::mem_fun(*this, &ItemDetailsWindow::on_key_press));

    ref_text_buffer = Gtk::TextBuffer::create();

    text_view.set_editable(false);
    text_view.set_cursor_visible(false);
    text_view.set_buffer(ref_text_buffer);
    text_view.set_wrap_mode(Gtk::WrapMode::WRAP_WORD);

    scrolled_win.add(text_view);

    // MAIN BOX
    v_box.set_margin_top(12);
    v_box.set_margin_right(12);
    v_box.set_margin_bottom(12);
    v_box.set_margin_left(12);
    v_box.pack_start(scrolled_win);
    v_box.show_all();

    add(v_box);
}

void ItemDetailsWindow::set_text(const Glib::ustring& text) const
{
    ref_text_buffer->set_text(text);
}

bool ItemDetailsWindow::on_key_press(GdkEventKey* key_event)
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
