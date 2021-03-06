#include "arealight.h"

#include <cstdlib>


namespace objects
{

using util::Vector3;
using util::Color;
using std::vector;

AreaLight::AreaLight(Vector3 position, Vector3 normal, double dx, double dy, Vector3 Dx, Color color, int grid)
    : Light(color), position(position), normal(normal.normalize()), dx(dx), dy(dy), Dx(Dx.normalize()), grid(grid)
{
}


AreaLight::~AreaLight()
{
}


vector<Vector3> AreaLight::get_light_vec(Vector3 position) const
{
    Vector3 Dy = (normal * Dx).normalize();
    Vector3 start = this->position - Dx * dx / 2 - Dy * dy / 2;

    vector<Vector3> res;
    for (int i = 0; i < grid; i++) {
        for (int j = 0; j < grid; j++) {
            double x = rand() / 32768.0, y = rand() / 32768.0;
            Vector3 point = start + Dx * dx / grid * (i + x) + Dy * dy / grid * (j + y);
            res.push_back(point - position);
        }
    }
    return res;
}


objects::Intersect AreaLight::intersects(const tracer::Ray& ray) const
{
    return Intersect::noHit;
}

}
