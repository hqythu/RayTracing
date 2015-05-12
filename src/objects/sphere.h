#ifndef SPHERE_H
#define SPHERE_H

#include "../util/vector3.h"

namespace objects
{

class Sphere
{
public:
    Sphere(util::Vector3& center, double radius);
    ~Sphere();

private:
    util::Vector3 center;
    double radius;
};

}

#endif // SPHERE_H
