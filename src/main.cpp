#include <iostream>

#include "util/vector3.h"
#include "tracer/camera.h"
#include "objects/sphere.h"

using util::Vector3;
using namespace objects;


int main()
{
    tracer::Camera camera(Vector3(0, 0, 0),
                          Vector3(0, 0, 1),
                          Vector3(1, 0, 0),
                          256, 256, 1);

    return 0;
}
