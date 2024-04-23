#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>
#include <stdexcept>

class Vector3D {
public:
    Vector3D() = default;
    Vector3D(double x, double y, double z):
        _x(x),
        _y(y),
        _z(z) {};
    ~Vector3D() = default;

    double _x = 0;
    double _y = 0;
    double _z = 0;

    double length() const { return std::sqrt(_x * _x + _y * _y + _z * _z); }
    double length_squared() const { return _x * _x + _y * _y + _z * _z; }

    double dot(const Vector3D &other) const { return _x * other._x + _y * other._y + _z * other._z; }

    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(_x + other._x, _y + other._y, _z + other._z);
    }

    Vector3D &operator+=(const Vector3D &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(_x - other._x, _y - other._y, _z - other._z);
    }

    Vector3D &operator-=(const Vector3D &other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    Vector3D operator*(const Vector3D &other) const
    {
        return Vector3D(
            _y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x
        );
    }

    Vector3D &operator*=(const Vector3D &other)
    {
        _x = _y * other._z - _z * other._y;
        _y = _z * other._x - _x * other._z;
        _z = _x * other._y - _y * other._x;
        return *this;
    }

    Vector3D operator*(double scalar) const { return Vector3D(_x * scalar, _y * scalar, _z * scalar); }

    Vector3D &operator*=(double scalar)
    {
        _x *= scalar;
        _y *= scalar;
        _z *= scalar;
        return *this;
    }

    Vector3D operator/(double scalar) const { return Vector3D(_x / scalar, _y / scalar, _z / scalar); }

    Vector3D &operator/=(double scalar)
    {
        _x /= scalar;
        _y /= scalar;
        _z /= scalar;
        return *this;
    }

protected:
private:
};

class Point3D {
public:
    double _x = 0;
    double _y = 0;
    double _z = 0;

    Point3D() = default;
    Point3D(double x, double y, double z):
        _x(x),
        _y(y),
        _z(z) {};

    Point3D operator+(const Vector3D &vector) const
    {
        return Point3D(_x + vector._x, _y + vector._y, _z + vector._z);
    }

    Vector3D operator-(const Point3D &point) const
    {
        return Vector3D(_x - point._x, _y - point._y, _z - point._z);
    }
};

class Ray {
public:
    Point3D _origin;
    Vector3D _direction;
    Point3D _color;

    Ray() = default;
    Ray(const Point3D &origin, const Vector3D &direction):
        _origin(origin),
        _direction(direction)
    {
    }
};

class Sphere {
public:
    Point3D _center;
    double _radius;

    Sphere(const Point3D &center, double radius):
        _center(center),
        _radius(radius)
    {
    }

    bool hits(const Ray &ray) const
    {
        Vector3D oc = ray._origin - _center;
        double a = ray._direction.dot(ray._direction);
        double b = 2.0 * oc.dot(ray._direction);
        double c = oc.dot(oc) - _radius * _radius;
        double discriminant = b * b - 4 * a * c;
        return discriminant > 0;
    }
};

class Rectangle3D {
public:
    Point3D _origin;
    Vector3D _bottom_side;
    Vector3D _left_side;

    Rectangle3D(const Point3D &origin, const Vector3D &bottom_side, const Vector3D &left_side):
        _origin(origin),
        _bottom_side(bottom_side),
        _left_side(left_side)
    {
    }

    Point3D pointAt(double u, double v) const
    {
        if (u < 0 || u > 1 || v < 0 || v > 1) {
            throw std::runtime_error(
                "u and v must be between 0 and 1 but: " + std::to_string(u) + " " + std::to_string(v)
            );
        }

        return _origin + _bottom_side * u + _left_side * v;
    }
};

class Camera {
public:
    Camera():
        _origin(Point3D(0, 0, 0)),
        _screen(Rectangle3D(Point3D(0, 0, 1), Vector3D(1, 0, 0), Vector3D(0, 1, 0)))
    {
    }
    Camera(const Point3D &origin, const Rectangle3D &screen):
        _origin(origin),
        _screen(screen)
    {
    }

    Ray ray(double u, double v) const
    {
        Point3D point = _screen.pointAt(u, v);
        Vector3D direction = point - _origin;
        return Ray(_origin, direction);
    }

private:
    Point3D _origin;
    Rectangle3D _screen;
};

#endif /* !MATH_HPP_ */
