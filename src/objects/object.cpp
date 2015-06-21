#include "object.h"

namespace objects
{

Object::Object()
{

}


Object::~Object()
{
    delete material;
}

Intersect Object::intersects(const tracer::Ray& ray)
{
    return Intersect::noHit;
}

}
