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
#ifndef HAMSTER_ITEM_UTIL_H
#define HAMSTER_ITEM_UTIL_H

#include <gtkmm-3.0/gtkmm.h>
#include "util/json/json.hpp"
#include "util/ui/UIUtil.h"

struct ItemUtil
{
    std::vector<std::map<std::string,std::string>> items_to_vec(const Gtk::TreeModel::Children& rows);
    std::vector<std::map<std::string,std::string>> json_items_to_vec(const nlohmann::basic_json<>& j);
};

#endif //HAMSTER_ITEM_UTIL_H
