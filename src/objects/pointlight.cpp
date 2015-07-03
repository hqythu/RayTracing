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

}
