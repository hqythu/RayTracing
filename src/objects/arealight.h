#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "light.h"

#include <vector>

namespace objects
{

class AreaLight : public Light
{
public:
    AreaLight(util::Vector3 position, util::Vector3 normal, double dx, double dy,
        util::Vector3 Dx, util::Color color, int grid);
    ~AreaLight();

    std::vector<util::Vector3> get_light_vec(util::Vector3 position) const;

    Intersect intersects(const tracer::Ray& ray) const;

private:
    util::Vector3 position, Dx, normal;
    double dx, dy;
    int grid;
};

}

#endif // AREALIGHT_H
