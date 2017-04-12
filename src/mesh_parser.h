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

#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "mesh.h"

class MeshParser {
private:

public:
    MeshParser() {}

    Mesh* read_obj(const std::string& filename, Mesh* mesh);

    void write_bin(const std::string& filename, const Mesh* mesh);

private:

};
