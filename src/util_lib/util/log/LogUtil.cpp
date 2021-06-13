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
#include "LogUtil.h"

void LogUtil::log_if_debug([[maybe_unused]] const std::string& log_text)
{
#ifdef DEBUG
    g_print("%s",log_text.c_str());
#endif
}

void LogUtil::log_if_debug([[maybe_unused]] const std::string& log_text,[[maybe_unused]] size_t num)
{
#ifdef DEBUG
    g_print(log_text.c_str(),num);
#endif
}
