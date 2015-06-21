#include "pointlight.h"

using util::Vector3;

namespace objects
{
PointLight::PointLight(util::Vector3 position, util::Color color)
    : Light(color), position(position)
{
}


Vector3 PointLight::get_light_vec(Vector3 position)
{
    return this->position - position;
}

}
