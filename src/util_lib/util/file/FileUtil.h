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
#ifndef HAMSTER_FILE_UTIL_H
#define HAMSTER_FILE_UTIL_H

#include <gtkmm-3.0/gtkmm.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <util/json/json.hpp>

struct FileUtil
{
    std::string desktop_filename="com.github.slawtul.hamster.desktop";
    std::string user_apps_dir="/usr/share/applications/";

    std::string config_dir();
    std::string autostart_dir();
    std::string items_json_filepath();
    void write_items_to_file(std::vector<std::map<std::string,std::string>> items);
    nlohmann::json read_items_from_file();
};

#endif //HAMSTER_FILE_UTIL_H
