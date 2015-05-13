#ifndef INTERSECT_H
#define INTERSECT_H

#include "object.h"
#include "../util/vector3.h"

namespace objects
{

class Intersect
{
public:
    Intersect(Object* object, bool intersects, double distance, util::Vector3 position, util::Vector3 normal);
    ~Intersect();

    Object* object_ptr;
    bool intersects;
    double distance;
    util::Vector3 position;
    util::Vector3 normal;

    static Intersect noHit;
};

}

#endif // INTERSECT_H