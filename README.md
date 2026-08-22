# pathtracer
Physically based path tracer running on CPU with multi-threading, made with
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

## Building
```git
- git clone https://github.com/KendySong/pb-pathtracer.git
- cd pb-pathtracer
- premake5 vs2026
```

<img src="https://raw.githubusercontent.com/KendySong/pb-pathtracer/main/screenshots/animation.gif"></img>
<img src="https://raw.githubusercontent.com/KendySong/pb-pathtracer/main/screenshots/final-max.png"></img>
<img src="https://raw.githubusercontent.com/KendySong/pb-pathtracer/main/screenshots/glass.png"></img>

## Path tracer design
- normal points always against the ray
- traced rays are normalized
- materials are separated from hittable objects
- thread pool system

### Used libraries
- SDL3
- glm
- ImGui
