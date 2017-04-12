/**************************************************************************
 *   mesh_parser.cpp  --  This file is part of OBJ2BIT.                   *
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

Mesh* MeshParser::read_obj(const std::string& filename, Mesh* mesh) {
    std::ifstream f(filename);
    if(f.is_open()) {

        // set regex patterns
        static const boost::regex v_line("v\\s+([0-9.-]+)\\s+([0-9.-]+)\\s+([0-9.-]+).*");
        static const boost::regex vn_line("vn\\s+([0-9.-]+)\\s+([0-9.-]+)\\s+([0-9.-]+).*");
        static const boost::regex f_line("f\\s+([0-9]+)\\/\\/([0-9]+)\\s+([0-9]+)\\/\\/([0-9]+)\\s+([0-9]+)\\/\\/([0-9]+).*");

        // construct holders
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<uint32_t> position_indices;
        std::vector<uint32_t> normal_indices;

        // read file line-by-line
        std::string line;
        while(getline(f, line)) {
            boost::smatch what1;

            if (boost::regex_match(line, what1, v_line)) {
                glm::vec3 pos(boost::lexical_cast<float>(what1[1]),
                              boost::lexical_cast<float>(what1[2]),
                              boost::lexical_cast<float>(what1[3]));
                positions.push_back(pos);
            }

            if (boost::regex_match(line, what1, vn_line)) {
                glm::vec3 normal(boost::lexical_cast<float>(what1[1]),
                                 boost::lexical_cast<float>(what1[2]),
                                 boost::lexical_cast<float>(what1[3]));
                normals.push_back(normal);
            }

            if (boost::regex_match(line, what1, f_line)) {
                position_indices.push_back(boost::lexical_cast<uint32_t>(what1[1]) - 1);
                position_indices.push_back(boost::lexical_cast<uint32_t>(what1[3]) - 1);
                position_indices.push_back(boost::lexical_cast<uint32_t>(what1[5]) - 1);

                normal_indices.push_back(boost::lexical_cast<uint32_t>(what1[2]) - 1);
                normal_indices.push_back(boost::lexical_cast<uint32_t>(what1[4]) - 1);
                normal_indices.push_back(boost::lexical_cast<uint32_t>(what1[6]) - 1);
            }
        }

        // loop over all positions and place these into the mesh
        for(unsigned int i=0; i<position_indices.size(); i++) {
            mesh->add_vertex_pn(i, positions[position_indices[i]], normals[normal_indices[i]]);
        }

        return mesh;

    } else {
        std::cerr << "Cannot open file " << filename << std::endl;
        throw std::runtime_error("Could not open file");

        return nullptr;
    }
}

void MeshParser::write_bin(const std::string& filename, const Mesh* mesh) {
    std::ofstream f(filename, std::ios_base::binary);

    if(f.good()) {
        // write the number of positions
        const uint32_t nr_vertices = mesh->get_vertices().size();
        f.write((char*)&nr_vertices, sizeof(uint32_t));

        // write the number of normals
        const uint32_t nr_normals = mesh->get_normals().size();
        f.write((char*)&nr_normals, sizeof(uint32_t));

        // write the number of indices
        const uint32_t nr_indices = mesh->get_vertices().size();
        f.write((char*)&nr_indices, sizeof(uint32_t));

        // write the positions
        for(const auto& pos : mesh->get_vertices()) {
            f.write((char*)&pos, sizeof(float) * 3);
        }

        // write the normals
        for(const auto& normal : mesh->get_normals()) {
            f.write((char*)&normal, sizeof(float) * 3);
        }

        // write the indices
        for(const auto& idx : mesh->get_vertices()) {
            f.write((char*)&idx, sizeof(uint32_t));
        }

        f.close();

    } else {
        std::cerr << "Cannot write to file " << filename << std::endl;
        throw std::runtime_error("Could not write to file");
    }
}
