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

#include <tclap/CmdLine.h>

#include "mesh_parser.h"

int main(int argc, char* argv[]) {

    std::cout << "------------------------------------------"   << std::endl;
    std::cout << "OBJ2BIN (C) 2017" << std::endl;
    std::cout << "Ivo Filot <ivo@ivofilot.nl>"  << std::endl;
    std::cout << "------------------------------------------"  << std::endl;

    try {
        TCLAP::CmdLine cmd("Converts Blender OBJ file to a binary file.", ' ', "1.0");

        //**************************************
        // declare values to be parsed
        //**************************************

        // input file
        TCLAP::ValueArg<std::string> arg_input_filename("i","input","Input file (i.e. sphere.obj)",true,"__NONE__","filename");
        cmd.add(arg_input_filename);

        TCLAP::ValueArg<std::string> arg_output_filename("o","output","Output file (i.e. sphere.mesh)",true,"__NONE__","filename");
        cmd.add(arg_output_filename);

        cmd.parse(argc, argv);

        MeshParser mp;

        std::cout << "Opening: " << arg_input_filename.getValue() << std::endl;

        MeshBase* mesh = mp.read_obj(arg_input_filename.getValue());

        std::cout << "Reading " << mesh->get_nr_vertices() << " vertices..." << std::endl;

        std::cout << "Writing to: " << arg_output_filename.getValue() << std::endl;

        mp.write_bz2(arg_output_filename.getValue(), mesh);

        std::cout << "------------------------------------------"  << std::endl;
        std::cout << "Done" << std::endl;

        delete mesh;

    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() <<
                     " for arg " << e.argId() << std::endl;
        return -1;
    }
}
