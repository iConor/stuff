#  TODO

---

## Short Term

---

### Shape Generators

- Sphere (UV)
-- Mesh generation works. 
- Cylinder
-- Single radius generation works.
- Cone
- Plane
- Cube
- Torus
- Sphere (Ico)

### Lighting

- One directional light (draw as cylinder of light color)
- Array of point lights (draw as sphere of light color)
- Array of spot lights (draw as cone of light color)

### Test Models

Do the donut tutorial then export models from Blender to be rendered:

- Suzanne
- Donut

### Math

- Deg2Rad
- Rad2Deg
- Doom invsqrt?

### Vector & Matrix

- Check my implementations against reference implementations
- Add support for m3 and m3
- Consider moving types to separate headers from engine_types (probably?)
- Add missing functions and operator overloads
- Add a string conversion or printing and a debug section
- Comment up the math


---

## Long Term

---

### Logging

- Replace iostream/cout with stdio/printf
- Replace stdio/printf with LOG_WHATEVS

### Camera

- Make a generic camera that follows some object?
- Separate camera for top-down and first person?
- Watch out for gimbal lock on that WSN-7
