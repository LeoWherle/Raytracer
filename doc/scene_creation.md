# Scene JSON Structure

## Camera

- `resolution`: An object that contains the `width` of the camera's resolution.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the camera's position.
- `rotation`: An object that contains the `x`, `y`, and `z` rotation angles of the camera.
- `fieldOfView`: The field of view of the camera.
- `RayPerPixel`: The number of rays per pixel.
- `MaxBounces`: The maximum number of bounces.
- `DefocusAngle`: The defocus angle of the camera.
- `BackgroundColor`: An object that contains the `r`, `g`, and `b` color values of the background.

## Primitives

### Spheres

Each sphere object contains:

- `radius`: The radius of the sphere.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the sphere's position.
- `material`: An object that contains the `material` type and `color` of the sphere.
- `transformations`: An object that contains the `rotation` and `translation` of the sphere.

### Planes

Each plane object contains:

- `normal`: An object that contains the `x`, `y`, and `z` coordinates of the plane's normal vector.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the plane's position.
- `material`: An object that contains the `material` type and `color` of the plane.
- `transformations`: An object that contains the `rotation` and `translation` of the plane.

### Triangles

Each triangle object contains:

- 3 `vertices`: An array of objects, each containing the `x`, `y`, and `z` coordinates of a vertex.
- `material`: An object that contains the `material` type and `color` of the triangle.
- `transformations`: An object that contains the `rotation` and `translation` of the triangle.

### Cylinders

Each cylinder object contains:

- `radius`: The radius of the cylinder.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the cylinder's position.
- `material`: An object that contains the `material` type and `color` of the cylinder.
- `transformations`: An object that contains the `rotation` and `translation` of the cylinder.

### Cones

Each cone object contains:

- `radius`: The radius of the cone.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the cone's position.
- `material`: An object that contains the `material` type and `color` of the cone.
- `transformations`: An object that contains the `rotation` and `translation` of the cone.

## Objects

Each object in the `objects` array represents a 3D model in the scene. 

- `filename`: The path to the 3D model file.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the model's position.
- `scale`: The scale of the model. A scale of 1 means the model is at its original size.
- `material`: An object that contains the `material` type and `color` of the model.

## Transformations

The `transformations` object can contain `rotation` and `translation` objects. 
- `rotation`: An object that contains the `x`, `y`, and `z` rotation angles.
- `translation`: An object that contains the `x`, `y`, and `z` translation distances.

## Color

The `color` object contains `r`, `g`, and `b` values representing the color in RGB format. Each value ranges from 0 to 1.

## Material

The `material` object contains the type of the material and its color. Some materials may have additional properties, like `fuzz` for `MetalMaterial`.