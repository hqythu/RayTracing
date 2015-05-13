#ifndef OBJECT_H
#define OBJECT_H

#include "intersect.h"
#include "../tracer/ray.h"

namespace objects
{

class Object
{
public:
    Object();
    virtual ~Object();

    Intersect intersects(const tracer::Ray& ray);
};

}

#endif // OBJECT_H
