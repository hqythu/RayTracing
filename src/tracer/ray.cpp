#include "ray.h"

namespace tracer
{

Ray::Ray(const util::Vector3& start, const util::Vector3& direction) :
    start(start), direction(direction.normalize())
{
}


Ray::~Ray()
{
}

}
