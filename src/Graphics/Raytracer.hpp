#pragma once
#include <vector>

#include "Ray.hpp"
#include "Color.hpp"
#include "Math.hpp"
#include "Sphere.hpp"

class Raytracer
{
public :
	static glm::vec3 trace(const Ray& ray, const std::vector<Hittable*>& world);
};