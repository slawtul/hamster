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

#include "AboutDialog.h"

AboutDialog::AboutDialog()
{
    set_program_name(_("Hamster"));
    set_comments(_("Clipboard manager"));
    set_version("1.0.0");
    set_copyright("Slawek Tuleja");
    set_website("https://github.com/slawtul/hamster");
    set_website_label("https://github.com/slawtul/hamster");
    set_logo(Gdk::Pixbuf::create_from_file("/usr/share/icons/hicolor/128x128/apps/com.github.slawtul.hamster.svg"));
}
