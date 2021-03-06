// colormap -- color palettes, map iterators, grids, and PPM export
// Copyright (C) 2018  Jonas Greitemann
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "colormap.hpp"
#include "grid.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int main () {
    size_t M = 25;
    std::vector<std::string> names;
    std::vector<decltype(color::palettes)::mapped_type> pals;
    for (auto pair : color::palettes) {
        names.push_back(pair.first);
        pals.push_back(pair.second);
        std::cout << names.back() << std::endl;
    }

    grid<2, major_order::col> g {
        {400, {0., 1.}},
        {M * names.size(), {0., names.size() - 1e-6}}
    };

    auto lamb = [&] (auto coord) {
        size_t i = size_t(coord[1]);
        return pals[i](coord[0]);
    };
    auto pix = itadpt::map(g, lamb);

    color::pixmap<decltype(pix.begin())> pmap(pix.begin(), g.shape());
    std::ofstream os("palettes." + pmap.file_extension());
    pmap.write_binary(os);
}
