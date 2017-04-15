/**************************************************************************
 *   main.cpp  --  This file is part of OBJ2BIT.                          *
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

#include "mesh_parser.h"

int main(int argc, char* argv[]) {
    MeshParser mp;
    MeshBase* mesh = mp.read_obj(argv[1]);

    mp.write_bin("test.bin", mesh);
    mp.write_bz2("test.bz2", mesh);
    MeshBase* mesh2 = mp.read_bz2("test.bz2");

    std::cout << mesh->get_type() << std::endl;
    std::cout << mesh2->get_type() << std::endl;

    delete mesh, mesh2;
}
