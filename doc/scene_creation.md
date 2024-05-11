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
- `Brightness`: The brightness of the received light. 1 is the default value. (optional)

## Scenes

The `scenes` array contains objects with a `path` variables that leads to another scene JSON file. The scenes are loaded in the order they appear in the array.

## Primitives

### Spheres

Each sphere object contains:

- `radius`: The radius of the sphere.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the sphere's position.
- `material`: An object that contains the `material` type and `color` or `texture` of the sphere.
- `transformations`: An object that contains the `rotation` and `translation` of the sphere.

### Planes

Each plane object contains:

- `normal`: An object that contains the `x`, `y`, and `z` coordinates of the plane's normal vector.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the plane's position.
- `material`: An object that contains the `material` type and `color` or `texture` of the plane.
- `transformations`: An object that contains the `rotation` and `translation` of the plane.

### Triangles

Each triangle object contains:

- 3 `vertices`: An array of objects, each containing the `x`, `y`, and `z` coordinates of a vertex.
- `material`: An object that contains the `material` type and `color` or `texture` of the triangle.
- `transformations`: An object that contains the `rotation` and `translation` of the triangle.

### Cylinders

Each cylinder object contains:

- `radius`: The radius of the cylinder.
- `height`: The height of the cylinder. (-1 for infinite cylinder)
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the cylinder's position.
- `material`: An object that contains the `material` type and `color` or `texture` of the cylinder.
- `transformations`: An object that contains the `rotation` and `translation` of the cylinder.

### Cones

Each cone object contains:

- `radius`: The radius of the cone.
- `height`: The height of the cone. (-1 for infinite cone)
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the cone's position.
- `material`: An object that contains the `material` type and `color` or `texture` of the cone.
- `transformations`: An object that contains the `rotation` and `translation` of the cone.

## Objects

Each object in the `objects` array represents a 3D model in the scene. 

- `filename`: The path to the 3D model file.
- `position`: An object that contains the `x`, `y`, and `z` coordinates of the model's position.
- `scale`: The scale of the model. A scale of 1 means the model is at its original size.
- `material`: An object that contains the `material` type and `color` or `texture` of the model.

## Transformations

The `transformations` object can contain `rotation` and `translation` objects. 
- `rotation`: An object that contains the `x`, `y`, and `z` rotation angles.
- `translation`: An object that contains the `x`, `y`, and `z` translation distances.

## Material

The `material` object contains the type of the material and its color. Some materials may have additional properties, like `fuzz` for `MetalMaterial`.

## Texture

The `texture` object contains a type of texture that can be applied to a primitive or object. The texture can be a `color` or a `checker`. For `checker` textures, there are `oddTexture` and `evenTexture` objects that contain the color of the odd and even squares of the checker pattern. A scale can be applied to the texture.

## Color

The `color` object contains `r`, `g`, and `b` values representing the color in RGB format. Each value ranges from 0 to 1.
