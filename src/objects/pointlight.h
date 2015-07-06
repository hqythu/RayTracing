#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"
#include "../util/color.h"
#include "../util/vector3.h"


namespace objects
{

class PointLight : public Light
{
public:
    PointLight(util::Vector3 position, util::Color color);

    std::vector<util::Vector3> get_light_vec(util::Vector3 position) const;

    Intersect intersects(const tracer::Ray& ray) const;

private:
    util::Vector3 position;
};

}


#endif // POINTLIGHT_H
