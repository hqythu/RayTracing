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
    double a0 = v.module_square() - (this->radius * this->radius);
    double DdotV = ray.direction.dot(v);

    if (DdotV > 0) {
        double discr = DdotV * DdotV - a0;
        if (discr >  EPSILON) {
            double dist = DdotV - sqrt(discr);
            Vector3 pos = ray.start + ray.direction * dist;
            Vector3 normal = (pos - this->center).normalize();
            return Intersect(this, true, dist, pos, normal);
        }
    }

    return Intersect::noHit;
}

}
