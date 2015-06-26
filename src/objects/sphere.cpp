#include "sphere.h"

#include <cmath>

namespace objects
{

using util::Vector3;

Sphere::Sphere(const util::Vector3& center, double radius) :
    center(center), radius(radius)
{
}


Sphere::~Sphere()
{
}

Intersect Sphere::intersects(const tracer::Ray& ray)
{
    Vector3 v = this->center - ray.start;
    double DdotV = ray.direction.dot(v);

    bool inside;

    if (v.module_square() > (radius * radius) + EPSILON) {
        inside = false;
    }
    else {
        inside = true;
    }

    if (DdotV > EPSILON) {
        double discr = v.module_square() - DdotV * DdotV;
        double a0 = radius * radius - discr;
        double dist;
        if (a0 > EPSILON) {
            if (inside) {
                dist = DdotV + sqrt(a0);
            }
            else {
                dist = DdotV - sqrt(a0);
            }
            Vector3 pos = ray.start + ray.direction * dist;
            Vector3 normal = (pos - this->center).normalize();
            return Intersect(this, true, dist, pos, normal);
        }
    }

    return Intersect::noHit;
}

}
