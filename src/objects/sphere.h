#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "../util/vector3.h"
#include "../tracer/ray.h"

namespace objects
{

class Sphere : public Object
{
public:
    Sphere(const util::Vector3& center, double radius);
    ~Sphere();

    Intersect intersects(const tracer::Ray& ray);

private:
    util::Vector3 center;
    double radius;
};

}

#endif // SPHERE_H
