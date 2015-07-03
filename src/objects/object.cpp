#include "object.h"

namespace objects
{

Intersect Intersect::noHit(nullptr, false, 0, Vector3(0, 0, 0), Vector3(0, 0, 0));

const double Object::EPSILON = 1e-6;


Object::Object()
{

}


Object::~Object()
{

}

Intersect Object::intersects(const tracer::Ray& ray) const
{
    return Intersect::noHit;
}

}
