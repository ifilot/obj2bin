/**************************************************************************
 *   octree.h  --  This file is part of OBJ2BIT.                          *
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

#ifndef _OCTREE_H
#define _OCTREE_H

#include <vector>

/*
 * @class Octree
 *
 * @param T                Type of object to hold
 * @param F                Floating point type to measure length (float, double, ...)
 * @param COMP_FUNC        Comparison function to use
 * @param MAX_OBJ_NODE     Maximum number of objects in a single node
 *
 */
template <typename T, typename F, uint8_t (*COMP_FUNC)(const T&, F, F, F), size_t MAX_OBJ_NODE>
class Octree {

    /************
     * VEC3
     ************/

    class Vec3 {
        public:
            F x;
            F y;
            F z;

            Vec3() : x(0), y(0), z(0) {}

            Vec3(F _x, F _y, F _z) : x(_x), y(_y), z(_z) {}

            Vec3 operator+(const Vec3& rhs) const {
                return Vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
            }

            Vec3 operator-(const Vec3& rhs) const {
                return Vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
            }

            Vec3 operator*(F rhs) const {
                return Vec3(rhs * this->x, rhs * this->y, rhs * this->z);
            }

            Vec3 operator/(F rhs) const {
                const F val = (F)1.0 / rhs;
                return Vec3(val * this->x, val * this->y, val * this->z);
            }

        private:
            friend std::ostream & operator<<(std::ostream &os, const Vec3& v) {
                os << v.x << "," << v.y << "," << v.z;
            }
    };

    /************
     * BOUNDARY
     ************/

    class Boundary {
        public:
            Vec3 lower;    //!< lower limit
            Vec3 upper;    //!< upper limit

            Boundary(const Vec3& _lower, const Vec3& _upper) : lower(_lower), upper(_upper) {}
    };

    /************
     * NODE
     ************/

    class Node {
        private:
            Node* parent;               //!< parent nodes
            Node* children[8];          //!< child nodes

            std::vector<T> objects;     //!< vector holding objects in the node
            const Boundary boundary;    //!< boundary of the node
            const Vec3 center;

            static constexpr uint8_t (*comp_func)(const T&, F, F, F) = COMP_FUNC;

        public:
            Node(const Boundary& _boundary) :
                boundary(_boundary),
                center((boundary.upper + boundary.lower) / (F)2.0)
                {
                for(unsigned int i=0; i<8; i++) {
                    children[i] = nullptr;
                }
            }

            void insert(const T& obj) {
                this->objects.push_back(obj);

                if(this->objects.size() > MAX_OBJ_NODE) {
                    this->split_node();
                }
            }

            Node* find(const T& obj) {
                const uint8_t child_addr = this->comp_func(obj, this->center.x, this->center.y, this->center.z);

                if(children[child_addr] != nullptr) {
                    return this->children[child_addr]->find(obj);
                } else {
                    return this;
                }
            }

            size_t get_nr_obj() const {
                size_t count = 0;

                count += this->objects.size();

                for(unsigned int i=0; i<8; i++) {
                    if(this->children[i] != nullptr) {
                        count += this->children[i]->get_nr_obj();
                    }
                }

                return count;
            }

            inline const Boundary& get_boundary() const {
                return this->boundary;
            }

        private:
            void split_node() {
                this->create_child_nodes();

                //migrate objects
                for(auto& obj : this->objects) {
                    Node* node = this->find(obj);
                    node->insert(obj);
                }

                this->objects.clear();
            }

            void create_child_nodes() {
                const Vec3& l = this->boundary.lower;
                const Vec3& u = this->boundary.upper;
                const Vec3& c = this->center;

                for(uint8_t i=0; i<8; i++) {
                    const F lx = (i & (1 << 0)) ? c.x : l.x;
                    const F ly = (i & (1 << 1)) ? c.y : l.y;
                    const F lz = (i & (1 << 2)) ? c.z : l.z;

                    const F ux = (i & (1 << 0)) ? u.x : c.x;
                    const F uy = (i & (1 << 1)) ? u.y : c.y;
                    const F uz = (i & (1 << 2)) ? u.z : c.z;

                    const Vec3 nl(lx, ly, lz);
                    const Vec3 nu(ux, uy, uz);

                    const Boundary new_bound(nl, nu);

                    this->children[i] = new Node(new_bound);
                }
            }
    };

private:
    static constexpr uint8_t (*comp_func)(const T&, F, F, F) = COMP_FUNC;
    Node* root;

public:
    /*
     * Default constructor
     *
     * @param   Pointer to comparison function that compares two objects
     */
    Octree(F sz) {
        // construct boundary
        const Vec3 lower(-sz/(F)2.0, -sz/(F)2.0, -sz/(F)2.0);
        const Vec3 upper( sz/(F)2.0,  sz/(F)2.0,  sz/(F)2.0);
        const Boundary boundary(lower, upper);

        // create root node
        this->root = new Node(boundary);
    }

    size_t size() const {
        return this->root->get_nr_obj();
    }

    void insert(const T& obj) {
        Node* node = this->root->find(obj);

        if(is_inside_node(obj, node)) {
            node->insert(obj);
        } else {
            std::cerr << "Object lies outside octree boundaries" << std::endl;
        }
    }

private:
    bool is_inside_node(const T& obj, const Node* node) {
        const uint8_t lc = this->comp_func(obj, node->get_boundary().lower.x, node->get_boundary().lower.y, node->get_boundary().lower.z);
        const uint8_t uc = this->comp_func(obj, node->get_boundary().upper.x, node->get_boundary().upper.y, node->get_boundary().upper.z);

        return (lc == 0x07 && uc == 0x00);
    }
};

#endif //_OCTREE_H
