/**************************************************************************
 *   mesh_base.cpp  --  This file is part of OBJ2BIT.                     *
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

#include "mesh_base.h"

MeshBase::MeshBase() {
    this->type = MESH_BASE;
}

void MeshBase::add_vertex_pn(unsigned int idx, const glm::vec3& pos, const glm::vec3& normal) {
    this->indices.push_back(idx);
    this->vertices.push_back(pos);
    this->normals.push_back(normal);
}

void MeshBase::add_content(const std::vector<glm::vec3>& _vertices,
                       const std::vector<glm::vec3>& _normals,
                       const std::vector<unsigned int>& _indices) {
    this->indices = _indices;
    this->vertices = _vertices;
    this->normals = _normals;
}
