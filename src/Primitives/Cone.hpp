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

        Cone(const Point3D &tip, const float &height, const Vector3D &direction,
            IMaterial *material, const float &angle);

        bool hits(const Ray &r, Interval ray_max, HitRecord &rec) const override;

        void translate(const Point3D &trans);

        void rotate(const Point3D &trans);
    protected:
    private:
        Point3D _tip;
        float _height;
        Vector3D _direction;

        IMaterial *_material;
        
        float _angle;
};
