#ifndef LIGHT_H
#define LIGHT_H

#include "../util/vector3.h"
#include "../util/color.h"
#include "object.h"

#include <vector>

namespace objects
{

class Light : public Object
{
public:
    Light(util::Color color);
    virtual std::vector<util::Vector3> get_light_vec(util::Vector3 position) const = 0;
    util::Color get_color(Intersect intersect) const { return color; }
    util::Color get_color() const { return color; }
private:
    util::Color color;
};

}


#endif // LIGHT_H
