#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "../util/vector3.h"


namespace objects
{

class Plane : public Object
{
public:
    Plane(util::Vector3 normal, util::Vector3 point);
    ~Plane();

    Intersect intersects(const tracer::Ray& ray);

private:
    util::Vector3 normal, point;
};

}


#endif // PLANE_H
