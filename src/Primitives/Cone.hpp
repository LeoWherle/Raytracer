/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** Cone
*/

#pragma once

#include "IPrimitive.hpp"
#include "Materials/IMaterial.hpp"

class Cone : public IPrimitive {
    public:
        ~Cone();

        Cone(
            const Point3D &tip, const Point3D &surface, const Vector3D &axis, IMaterial *material,
            const float &radius
        );

        bool hits(const Ray &r, Interval ray_max, HitRecord &rec) const override;

        void translate(const Point3D &trans);

        void rotate(const Point3D &trans);
    protected:
    private:
        Point3D _tip;
        Point3D _surface;
        Vector3D _axis;

        IMaterial *_material;
        
        float _radius;
};
