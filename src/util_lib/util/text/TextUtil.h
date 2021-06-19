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
#ifndef HAMSTER_TEXT_UTIL_H
#define HAMSTER_TEXT_UTIL_H

#include <regex>
#include <gtkmm-3.0/gtkmm.h>

struct TextUtil
{
    static const std::regex newlines_re;
    static const std::regex tabs_re;
    static const std::regex whitespaces_re;
    static const std::regex backslash_re;
    static const std::regex star_re;
    static const std::regex par_l_re;
    static const std::regex par_r_re;
    static const std::regex dot_re;
    static const std::regex plus_re;
    static const std::regex qmark_re;
    static const std::regex bird_re;
    static const std::regex dol_re;
    static const std::regex sbra_l_re;
    static const std::regex sbra_r_re;
    static const std::regex cbra_l_re;
    static const std::regex cbra_r_re;
    static const std::regex line_re;

    Glib::ustring join_lines(Glib::ustring& text, uint n_letters);
    Glib::ustring trim_str(const Glib::ustring& text);
    Glib::ustring sub_str(const Glib::ustring& text, uint n_letters, const Glib::ustring& end_text);
    Glib::ustring calculate_display_value(Glib::ustring& text);
    std::string mask_str(const Glib::ustring& text);

    std::string convert_to_newline_or_tab(std::string& text);
    std::string escape_nonalpha(const std::string& text);
    bool has_only_spaces(const Glib::ustring& text);
};

#endif //HAMSTER_TEXT_UTIL_H
