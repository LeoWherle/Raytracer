/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Camera
*/

#include "Math/MathsUtils.hpp"
#include "Camera.hpp"

void Camera::update()
{
    image_height = uint32_t((float) image_width / (float) aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    pixel_samples_scale = 1.0f / (float) samples_per_pixel;
    center = origin;
    // Determine viewport dimensions.
    auto theta = mathsUtils::degrees_to_radians(vfov);
    auto h = tan(theta / 2);
    auto viewport_height = 2 * h * focus_dist;
    auto viewport_width = viewport_height * (float(image_width) / (float) image_height);
    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    auto w = Vector3D::unit(origin - lookat);
    auto u = Vector3D::unit(vup.cross(w));
    auto v = w.cross(u);
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3D viewport_u = u * viewport_width; // Vector across viewport horizontal edge
    Vector3D viewport_v = -v * viewport_height; // Vector down viewport vertical edge
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / (float) image_width;
    pixel_delta_v = viewport_v / (float) image_height;
    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        center - (w * static_cast<float>(focus_dist)) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;
    // Calculate the camera defocus disk basis vectors.
    // from
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
    auto defocus_radius = focus_dist * tan(mathsUtils::degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

void Camera::move(const Vector3D &direction)
{
    origin = origin + direction;
}

void Camera::rotate(const Vector3D &axis, float angle)
{
    auto rotation = Matrix3D::rotation(axis, angle);
    lookat = rotation * lookat;
    vup = rotation * vup;
}

Ray Camera::new_ray(float u, float v) const
{
    auto offset = Vector3D(Random::gen_float() - 0.5f, Random::gen_float() - 0.5f, 0);
    auto pixel_sample =
        pixel00_loc + (pixel_delta_u * (u + offset._x)) + (pixel_delta_v * (v + offset._y));
    auto ray_direction = pixel_sample - center;
    return Ray(center, ray_direction);
}

Color Camera::ray_color(const Ray &r, int depth, const World &world) const
{
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0, 0, 0);
    HitRecord rec;
    // If the ray hits nothing, return the background color.
    if (!world.hits(r, Interval(0.001f, std::numeric_limits<float>::infinity()), rec))
        return background;
    Ray scattered;
    Color attenuation;
    Color color_from_emission = rec.material->emitted(rec.u, rec.v, rec.p);
    // If the ray is scattered, modify the color by the attenuation and recurse.
    if (!rec.material->scatter(r, rec, attenuation, scattered))
        return color_from_emission;
    // Recurse with the new scattered ray, and multiply the result by the attenuation.
    Color color_from_scatter = ray_color(scattered, depth - 1, world) * attenuation;
    return color_from_emission + color_from_scatter;
}
