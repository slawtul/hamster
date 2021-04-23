/*
 *  _____ _____ _____ _____ _____ _____ _____
 * |  |  |  _  |     |   __|_   _|   __| __  |
 * |     |     | | | |__   | | | |   __|    -|
 * |__|__|__|__|_|_|_|_____| |_| |_____|__|__|
 *
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

#include <ui/window/MainWindow.h>

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("com.github.slawtul.hamster");

    MainWindow win {};
    win.stick();
    win.present();

    return app->run(win, argc, argv);
}
