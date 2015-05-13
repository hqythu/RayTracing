#include "object.h"

namespace objects
{

Object::Object()
{

}


Object::~Object()
{

}

Intersect Object::intersects(const tracer::Ray& ray)
{
    return Intersect::noHit;
}

}
