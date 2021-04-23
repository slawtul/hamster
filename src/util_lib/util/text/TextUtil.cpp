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
#include "TextUtil.h"

const std::regex TextUtil::newlines_re {"\\\\n+"};
const std::regex TextUtil::tabs_re {"\\\\t+"};
const std::regex TextUtil::whitespaces_re {"\\s+"};

const std::regex TextUtil::backslash_re {"\\\\"};
const std::regex TextUtil::star_re {"\\*"};
const std::regex TextUtil::par_l_re {"\\("};
const std::regex TextUtil::par_r_re {"\\)"};
const std::regex TextUtil::dot_re {"\\."};
const std::regex TextUtil::plus_re {"\\+"};
const std::regex TextUtil::qmark_re {"\\?"};
const std::regex TextUtil::bird_re {"\\^"};
const std::regex TextUtil::dol_re {"\\$"};
const std::regex TextUtil::sbra_l_re {"\\["};
const std::regex TextUtil::sbra_r_re {"\\]"};
const std::regex TextUtil::cbra_l_re {"\\{"};
const std::regex TextUtil::cbra_r_re {"\\}"};
const std::regex TextUtil::line_re {"\\|"};

Glib::ustring TextUtil::sub_str(const Glib::ustring& text, uint n_letters, const Glib::ustring& end)
{
    if (text.length() > n_letters) {
        return text.substr(0, n_letters).append(end);
    }
    return text;
}

bool TextUtil::has_only_spaces(const Glib::ustring& text)
{
    return text.find_first_not_of(" \t\n\v\f\r") == Glib::ustring::npos;
}

Glib::ustring TextUtil::join_lines(Glib::ustring& text, uint n_letters)
{
    return std::regex_replace(text.substr(0, n_letters).c_str(), whitespaces_re, " ");
}

Glib::ustring TextUtil::trim_str(const Glib::ustring& text)
{
    const auto whitespaces = " \t\n";
    const auto begin = text.find_first_not_of(whitespaces);
    if (begin == std::string::npos) {
        return ""; // No content
    }
    const auto end = text.find_last_not_of(whitespaces);
    const auto range = end - begin + 1;
    return text.substr(begin, range);
}

std::string TextUtil::mask_str(const Glib::ustring& text)
{
    if (text.empty()) {
        return "";
    }

    const auto str = (std::string) text;
    const auto str_sz = str.length();
    const auto first_letter = str.at(0);
    const auto last_letter = str.at(str_sz - 1);

    std::string masked_str = "";
    masked_str += first_letter;
    for (size_t i = 0; i < str_sz - 2; i++) {
        masked_str += '*';
    }
    masked_str += last_letter;
    return masked_str;
}

std::string TextUtil::convert_to_newline_or_tab(std::string& text)
{
    text = std::regex_replace(text, newlines_re, "\n");
    text = std::regex_replace(text, tabs_re, "\t");
    return text;
}

std::string TextUtil::escape_nonalpha(const std::string& text)
{
    std::string esc_str;
    esc_str = std::regex_replace(text, backslash_re, "\\\\");
    esc_str = std::regex_replace(esc_str, star_re, "\\*");
    esc_str = std::regex_replace(esc_str, par_l_re, "\\(");
    esc_str = std::regex_replace(esc_str, par_r_re, "\\)");
    esc_str = std::regex_replace(esc_str, dot_re, "\\.");
    esc_str = std::regex_replace(esc_str, plus_re, "\\+");
    esc_str = std::regex_replace(esc_str, qmark_re, "\\?");
    esc_str = std::regex_replace(esc_str, bird_re, "\\^");
    esc_str = std::regex_replace(esc_str, dol_re, "\\$");
    esc_str = std::regex_replace(esc_str, sbra_l_re, "\\[");
    esc_str = std::regex_replace(esc_str, sbra_r_re, "\\]");
    esc_str = std::regex_replace(esc_str, cbra_l_re, "\\{");
    esc_str = std::regex_replace(esc_str, cbra_r_re, "\\}");
    esc_str = std::regex_replace(esc_str, line_re, "\\|");
    return esc_str;
}

Glib::ustring TextUtil::calculate_display_value(Glib::ustring& text)
{
    text = join_lines(text, 48);
    text = trim_str(text);
    text = sub_str(text, 40, "...");
    return text;
}
