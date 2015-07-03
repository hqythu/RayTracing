#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"


namespace objects
{

class Triangle : public Object
{
public:
    Triangle(Vector3 p0, Vector3 p1, Vector3 p2);
    ~Triangle();

    Intersect intersects(const tracer::Ray& ray) const;
    Color get_color(Intersect intersect) const;

    double max_x() const;
    double min_x() const;
    double max_y() const;
    double min_y() const;
    double max_z() const;
    double min_z() const;

private:
    Vector3 p0, p1, p2;
};

}


#endif // TRIANGLE_H
