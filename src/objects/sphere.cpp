#include "sphere.h"

#include <cmath>

namespace objects
{

using util::Vector3;

Sphere::Sphere(util::Vector3& center, double radius) :
    center(center), radius(radius)
{
}


Sphere::~Sphere()
{
}

Intersect Sphere::intersects(const tracer::Ray& ray)
{
    Vector3 v = ray.start - this->center;
    Vector3 a0 = v.module_square() - (this->radius * this->radius);
    double DdotV = ray.direction.dot(v);

    if (DdotV <= 0) {
        double discr = DdotV * DdotV - a0;
        if (discr >= 0) {
            double dist = - DdotV - sqrt(discr);
            Vector3 pos = ray.start + ray.direction * dist;
            return Intersect(this,
                             true,
                             dist,
                             pos,
                             (pos - this->center).normalize());
        }
    }

    return Intersect::noHit;
}

}
