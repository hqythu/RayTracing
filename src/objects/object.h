#ifndef OBJECT_H
#define OBJECT_H

#include "intersect.h"
#include "material.h"
#include "../tracer/ray.h"

namespace objects
{

class Object;
typedef util::Vector3 Color;

class Object
{
public:
    Object();
    virtual ~Object();

    virtual Intersect intersects(const tracer::Ray& ray);

    Material* material;
};

}

#endif // OBJECT_H
