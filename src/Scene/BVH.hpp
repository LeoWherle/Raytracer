/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** BVH
*/

#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "Math/AABB.hpp"
#include "Primitives/IPrimitive.hpp"

class BVH {
private:
    struct Node {

        AABB bounds;
        std::uint32_t first = 0;
        std::uint32_t count = 0;
        inline bool isLeaf() const { return count > 0; }
    };

private:
    std::vector<BVH::Node> bvh_nodes;
    std::vector<std::uint32_t> prim_indices;
    std::uint32_t root_node_index = 0, nodes_used = 1;

public:
    BVH() = default;
    ~BVH() = default;

    virtual auto get_triangles() const -> const std::vector<std::unique_ptr<IPrimitive>> & = 0;

    void build()
    {
        bvh_nodes.resize(get_triangles().size() * 2);
        prim_indices.resize(get_triangles().size());
        for (std::uint32_t i = 0; i < get_triangles().size(); ++i) {
            prim_indices[i] = i;
        }

        BVH::Node &root = bvh_nodes[root_node_index];
        root.first = 0;
        root.count = static_cast<uint32_t>(get_triangles().size());
        update_bounds(root_node_index);

        subdivide(root_node_index);
    }

    void update_bounds(std::uint32_t node_index)
    {
        BVH::Node &node = bvh_nodes[node_index];
        node.bounds.m_min = Point3D(1e30f, 1e30f, 1e30f);
        node.bounds.m_max = Point3D(-1e30f, -1e30f, -1e30f);
        for (std::uint32_t first = node.first, i = 0; i < node.count; i++) {
            std::uint32_t leaf_index = prim_indices[first + i];
            IPrimitive &leaf_primitive = *get_triangles()[leaf_index];
            node.bounds.m_min = Vector3D::min(node.bounds.m_min, leaf_primitive.boundingBox().m_min);
            node.bounds.m_max = Vector3D::min(node.bounds.m_max, leaf_primitive.boundingBox().m_max);
        }
    }

    void subdivide(std::uint32_t node_index)
    {
        BVH::Node &node = bvh_nodes[node_index];
        if (node.count <= 2) {
            return;
        }

        Point3D extent = node.bounds.m_max - node.bounds.m_min;
        int axis = 0;
        if (extent._y > extent._x) {
            axis = 1;
        }
        if (extent._z > extent[axis]) {
            axis = 2;
        }
        float splitPos = node.bounds.m_min[axis] + extent[axis] * 0.5f;

        std::int32_t i = node.first;
        std::int32_t j = i + node.count - 1;
        while (i <= j) {
            if (get_triangles()[prim_indices[i]]->centroid()[axis] < splitPos) {
                i++;
            } else {
                std::swap(prim_indices[i], prim_indices[j--]);
            }
        }

        std::uint32_t left_count = i - node.first;
        if (left_count == 0 || left_count == node.count) {
            return;
        }

        std::uint32_t left_child_index = nodes_used++;
        std::uint32_t right_child_index = nodes_used++;
        BVH::Node &left_child = bvh_nodes[left_child_index];
        BVH::Node &right_child = bvh_nodes[right_child_index];
        left_child.first = node.first;
        left_child.count = left_count;
        right_child.first = i;
        right_child.count = node.count - left_count;
        node.first = left_child_index;
        node.count = 0;
        update_bounds(left_child_index);
        update_bounds(right_child_index);

        subdivide(left_child_index);
        subdivide(right_child_index);
    }

    bool hits_bvh(const Ray &r, Interval ray_d, HitRecord &rec, std::uint32_t node_index) const
    {
        auto &node = bvh_nodes[node_index];
        if (!node.bounds.hits(r, rec)) {
            return false;
        }

        bool hitAnything = false;
        HitRecord tempRec;
        float closest = ray_d.max;

        if (node.isLeaf()) {
            for (std::uint32_t i = 0; i < node.count; ++i) {
                std::uint32_t triIdx = prim_indices[node.first + i];
                if (get_triangles()[triIdx]->hits(r, Interval(ray_d.min, closest), tempRec)) {
                    hitAnything = true;
                    closest = tempRec.t;
                    rec = tempRec;
                }
            }
        } else {
            hitAnything |= hits_bvh(r, ray_d, rec, node.first);
            hitAnything |= hits_bvh(r, ray_d, rec, node.first + 1);
        }

        return hitAnything;
    }

    bool hits(const Ray &r, Interval ray_d, HitRecord &rec) const
    {
        return hits_bvh(r, ray_d, rec, root_node_index);
    }

    AABB boundingBox() const { return bvh_nodes[root_node_index].bounds; }

    Point3D centroid() const { return bvh_nodes[root_node_index].bounds.centroid(); }
};