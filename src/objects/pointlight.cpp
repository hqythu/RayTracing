#include "pointlight.h"

#include <vector>

using util::Vector3;

namespace objects
{

using std::vector;


PointLight::PointLight(util::Vector3 position, util::Color color)
    : Light(color), position(position)
{
}


vector<Vector3> PointLight::get_light_vec(util::Vector3 position) const
{
    return vector<Vector3>(1, this->position - position);
}


objects::Intersect PointLight::intersects(const tracer::Ray& ray) const
{
    Vector3 v = this->position - ray.start;
    if (v.normalize().dot(ray.direction) > 1 - EPSILON) {
        return Intersect(this, true, v.module(), this->position, Vector3(0, 0, 0));
    }
    else {
        return Intersect::noHit;
    }
}

}
