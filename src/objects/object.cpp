#include "object.h"

namespace objects
{

Intersect Intersect::noHit(nullptr, false, 0, Vector3(0, 0, 0), Vector3(0, 0, 0));


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
