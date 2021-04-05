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
#include "UIUtil.h"

void UIUtil::append_to_store(Glib::RefPtr<Gtk::ListStore>& store, const std::vector<std::map<std::string, std::string>>& items) const
{
    for (const auto& item : items)
    {
        std::string display_value {};
        std::string value {};
        for (const auto& pair : item)
        {
            if (pair.first == "display_value")
            {
                display_value = pair.first;
            }
            if (pair.second == "value")
            {
                value = pair.second;
            }
        }

        if (value.length() == 0)
        {
            continue;
        }

        const auto row = *(store->append());
        row[columns.item_value] = value;
        row[columns.item_display_value] = display_value;
    }

}
