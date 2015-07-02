#include "sphere.h"

#include <cmath>
#include <algorithm>

namespace objects
{

using util::Vector3;

const double PI = 3.141592653589793238463;

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
            Vector3 normal = (pos - this->center).normalize() * (inside ? -1 : 1);
            return Intersect(this, true, dist, pos, normal);
        }
    }

    return Intersect::noHit;
}


Color Sphere::get_color(Intersect intersect)
{
    if (material->texture) {
        double a = acos(-intersect.normal.dot(Vector3(0, 0, 1)));
        double b = acos(std::min(std::max(intersect.normal.dot(Vector3(0, 1, 0)) / sin(a), -1.0), 1.0));
        double u = a / PI;
        double v = b / 2 / PI;
        return material->texture->get_relative_color(u, v);
    }
    else {
        return material->color;
    }
}

}
