# pb-pathtracer
Physically based path tracer running on CPU, made with
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

## Building
```git
- git clone https://github.com/KendySong/pb-pathtracer.git
- cd pb-pathtracer
- premake5 vs2026
```

<img src="https://github.com/KendySong/pb-pathtracer/tree/main/screenshots/final-max.png"></img>
<img src="https://github.com/KendySong/pb-pathtracer/tree/main/screenshots/glass.png"></img>

## Path tracer design
- normal points always against the ray
- traced rays are normalized
- materials are separated from hittable objects

### Used libraries
- SDL3
- glm
- ImGui