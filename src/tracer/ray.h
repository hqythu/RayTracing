#ifndef RAY_H
#define RAY_h

#include "../util/vector3.h"

namespace tracer
{

class Ray
{
public:
    Ray(const util::Vector3& start, const util::Vector3& direction);
    ~Ray();

    util::Vector3 start, direction;
};

}

#endif // RAY_H
