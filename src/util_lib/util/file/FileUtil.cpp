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
#include "FileUtil.h"

using json = nlohmann::json;

//--------------------------------
std::string FileUtil::config_dir()
{
    return std::string(getenv("HOME")) + "/.config/hamster/";
}

//-----------------------------------
std::string FileUtil::autostart_dir()
{
    return std::string(getenv("HOME")) + "/.config/autostart/";
}

//-----------------------------------------
std::string FileUtil::items_json_filepath()
{
    return config_dir() + "items.json";
}

//----------------------------------------------------------------------------------------
void FileUtil::write_items_to_file(std::vector <std::map<std::string, std::string>> items)
{
    const auto json_file = items_json_filepath();
    mkdir(config_dir().c_str(), 0775); // Create dir or do nothing...
    std::remove(json_file.c_str());   // Always write items to new file

    std::fstream fs{};
    fs.open(json_file, std::ios::in | std::ios::out | std::ios::app);

    json j{};
    j["items"] = items;

    fs << j;
    fs.close();
}

//-----------------------------------
json FileUtil::read_items_from_file()
{
    const auto json_file = items_json_filepath();

    std::ifstream ifs(json_file);
    json j{};
    ifs >> j;

    ifs.close();

    return j;
}
