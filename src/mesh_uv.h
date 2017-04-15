/**************************************************************************
 *   mesh_uv.h  --  This file is part of OBJ2BIT.                         *
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

#ifndef _MESH_UV
#define _MESH_UV

#include "mesh_base.h"

class MeshUV : public MeshBase {
private:
    std::vector<glm::vec2> uvs;

public:
    MeshUV();

    virtual void add_vertex_ptn(uint32_t idx, const glm::vec3& pos, const glm::vec2& uv, const glm::vec3& normal);

    virtual void add_content(const std::vector<glm::vec3>& _vertices,
                             const std::vector<glm::vec2>& _uvs,
                             const std::vector<glm::vec3>& _normals,
                             const std::vector<unsigned int>& _indices);

    inline const std::vector<glm::vec2>& get_uvs() const {
        return this->uvs;
    }

private:
};

#endif //_MESH_UV
