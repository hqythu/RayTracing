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

    util::Vector3 position;
    util::Color color;
};

}


#endif // POINTLIGHT_H
