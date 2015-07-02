#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "../util/vector3.h"


namespace objects
{

class Plane : public Object
{
public:
    Plane(util::Vector3 normal, util::Vector3 point, util::Vector3 dx);
    ~Plane();

    Intersect intersects(const tracer::Ray& ray);
    Color get_color(Intersect intersect);

private:
    util::Vector3 normal, point, dx;
};

}


#endif // PLANE_H
