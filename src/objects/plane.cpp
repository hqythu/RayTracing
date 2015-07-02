#include "plane.h"

namespace objects
{

using util::Vector3;
using objects::Intersect;

Plane::Plane(Vector3 normal, Vector3 point, Vector3 dx)
    : normal(normal.normalize()), point(point), dx(dx)
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


Color Plane::get_color(Intersect intersect)
{
    if (material->texture) {
        Vector3 dy = dx * intersect.normal;
        double u = dx.dot(intersect.position) / dx.module_square();
        double v = dy.dot(intersect.position) / dy.module_square();
        return material->texture->get_relative_color(u, v);
    } 
    else {
        return material->color;
    }
}

}
