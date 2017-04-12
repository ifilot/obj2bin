/**************************************************************************
 *   mesh.h  --  This file is part of OBJ2BIT.                            *
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

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Mesh {
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<uint32_t> indices;

public:
    Mesh() {}

    void add_vertex_pn(uint32_t idx, const glm::vec3& pos, const glm::vec3& normal);

    inline unsigned int get_nr_vertices() const {
        return this->vertices.size();
    }

    inline const std::vector<glm::vec3>& get_vertices() const {
        return this->vertices;
    }

    inline const std::vector<glm::vec3>& get_normals() const {
        return this->normals;
    }

    inline const std::vector<uint32_t>& get_indices() const {
        return this->indices;
    }

    ~Mesh() {}

private:
};
