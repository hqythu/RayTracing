#include "plane.h"

namespace objects
{

using util::Vector3;
using objects::Intersect;

Plane::Plane(Vector3 normal, Vector3 point)
    : normal(normal), point(point)
{
}


Plane::~Plane()
{
}


Intersect Plane::intersects(const tracer::Ray& ray)
{
    double D = -point.dot(normal);
    double t = -(D + ray.start.dot(normal)) / (ray.direction.dot(normal));
    if (t > EPSILON) {
        Vector3 pos = ray.start + ray.direction * t;
        return Intersect(this, true, t, pos, normal);
    }
    return Intersect::noHit;
}

}
