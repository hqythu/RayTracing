#ifndef MATERIAL_H
#define MATERIAL_H

#include "../util/vector3.h"

namespace objects
{

typedef util::Vector3 Color;

class Material
{
public:
    Material();
    ~Material();

    Color color;
    double reflect, refract;
};

}

#endif
