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

#include "MainWindow.h"

MainWindow::MainWindow()
{
    set_border_width(0);
    set_resizable(false);
    set_default_size(360, -1);

    ref_settings = Gio::Settings::create("com.github.slawtul.hamster");
    auto const x = ref_settings->get_int("window-x");
    auto const y = ref_settings->get_int("window-y");

    (x == -1 && y == -1) ? set_position(Gtk::WIN_POS_CENTER) : move(x, y);

    if (ref_settings->get_boolean("run-minimize"))
    {
        this->iconify();
    }

    FileUtil fu {};
    const auto desktop_filepath = fu.autostart_dir() + fu.desktop_filename;
    std::remove(desktop_filepath.c_str());

    if (ref_settings->get_boolean("run-automatically"))
    {
        std::ifstream src {fu.user_apps_dir + fu.desktop_filename};
        std::ofstream dst {fu.autostart_dir() + fu.desktop_filename};
        dst << src.rdbuf();
    }

    header_bar.set_show_close_button(true);
    header_bar.set_title(_("🐹 Hamster"));
    header_bar.set_has_subtitle(false);
    menu_btn.show();
    header_bar.pack_end(menu_btn);
    header_bar.show();
    set_titlebar(header_bar);

    add(win_body);

    this->signal_event().connect(sigc::mem_fun(*this, &MainWindow::on_main_window_event));

    // ABOUT DIALOG
    about_dialog.set_transient_for(*this);
    menu_btn.settings_popover.about_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::show_about_dialog));
    about_dialog.signal_response().connect(sigc::mem_fun(*this, &MainWindow::hide_about_dialog));

    // PREFERENCES WINDOW
    preferences_window.set_transient_for(*this);
    menu_btn.settings_popover.pref_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::show_preferences_win));

    // SHORTCUTS WINDOW
    shortcuts_window.set_transient_for(*this);
    menu_btn.settings_popover.shortcuts_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::show_shortcuts_win));

    // QUIT APP
    menu_btn.settings_popover.quit_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::close_app));
}

void MainWindow::show_about_dialog()
{
    about_dialog.present();
}

void MainWindow::hide_about_dialog(int response_id)
{
    if (response_id == Gtk::ResponseType::RESPONSE_DELETE_EVENT)
    {
        about_dialog.hide();
    }
}

void MainWindow::show_shortcuts_win()
{
    shortcuts_window.present();
}

void MainWindow::show_preferences_win()
{
    preferences_window.present();
}

void MainWindow::close_app()
{
    int win_x, win_y;
    this->get_position(win_x, win_y);

    // Save app current position
    ref_settings->set_int("window-x", win_x);
    ref_settings->set_int("window-y", win_y);

    // Write items to file
    if (ref_settings->get_boolean("save-list"))
    {
        ItemUtil iu {};
        const auto items_vec = iu.items_to_vec(win_body.ref_primary_item_store->children());

        FileUtil fu {};
        fu.write_items_to_file(items_vec);
    }

    LogUtil lu {};
    lu.log_if_debug("\nHamster says bye!\n");
    exit(0);
}

bool MainWindow::on_main_window_event(GdkEvent* gdk_event)
{
    if (gdk_event == nullptr)
    {
        return false;
    }

    const auto state = gdk_event->key.state;
    if (state == 4 || state == 6 || state == 20 || state == 22)
    {
        const auto key = gdk_event->key.keyval;

        // 'CTRL + P' show properties window
        if (key == GDK_KEY_p || key == GDK_KEY_P)
        {
            show_preferences_win();
            return true;
        }

        // 'CTRL + S' show shortcuts window
        if (key == GDK_KEY_s || key == GDK_KEY_S)
        {
            show_shortcuts_win();
            return true;
        }

        // 'CTRL + Q' quit application
        if (key == GDK_KEY_q || key == GDK_KEY_Q)
        {
            close_app();
            return true;
        }
    }

    return false;
}

bool MainWindow::on_delete_event(GdkEventAny* any_event)
{
    if (any_event == nullptr)
    {
        return false;
    }
    close_app();
    return true;
}
