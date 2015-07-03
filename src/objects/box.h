#ifndef BOX_H
#define BOX_H

#include "object.h"

namespace objects
{

class Box : public Object
{
public:
    Box(double x1 = 0, double x2 = 0, double y1 = 0, double y2 = 0, double z1 = 0, double z2 = 0);
    ~Box();

    Intersect intersects(const tracer::Ray& ray);
    Color get_color(Intersect intersect);

private:
    bool at_surface(Vector3 pos);

    double x1, x2, y1, y2, z1, z2;
};

}

#endif // BOX_H
