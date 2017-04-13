/**************************************************************************
 *   mesh_parser.h  --  This file is part of OBJ2BIT.                     *
 *                                                                        *
 *   Copyright (C) 2017, Ivo Filot (ivo@ivofilot.nl)                      *
 *                                                                        *
 *   OBJ2BIT is free software:                                            *
 *   you can redistribute it and/or modify it under the terms of the      *
 *   GNU General Public License as published by the Free Software         *
 *   Foundation, either version 3 of the License, or (at your option)     *
 *   any later version.                                                   *
 *                                                                        *
 *   OBJ2BIT is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty          *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *   See the GNU General Public License for more details.                 *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.  *
 *                                                                        *
 **************************************************************************/

#ifndef _MESH_PARSER_H
#define _MESH_PARSER_H

#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

#include "mesh.h"

class MeshParser {
private:

public:
    MeshParser() {}

    Mesh* read_obj(const std::string& filename, Mesh* mesh);

    void write_bin(const std::string& filename, const Mesh* mesh);

    void write_bz2(const std::string& filename, const Mesh* mesh);

    Mesh* read_bz2(const std::string& filename, Mesh* mesh);

private:

};

// define comparison function for glm::vec3
static uint8_t comp_vec3(const glm::vec3& lhs, float x, float y, float z) {
    uint8_t result = 0;
    if(lhs.x > x) {
        result |= (1 << 0);
    }
    if(lhs.y > y) {
        result |= (1 << 1);
    }
    if(lhs.z > z) {
        result |= (1 << 2);
    }

    return result;
}

#endif //_MESH_PARSER_H
