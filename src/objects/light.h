#ifndef LIGHT_H
#define LIGHT_H

#include "../util/vector3.h"
#include "../util/color.h"

namespace objects
{

class Light
{
public:
    Light(util::Color color);
    virtual util::Vector3 get_light_vec(util::Vector3 position) = 0;
    util::Color get_color() { return color; }
private:
    util::Color color;
};

}


#endif // LIGHT_H
