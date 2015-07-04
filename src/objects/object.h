#ifndef OBJECT_H
#define OBJECT_H

#include "../tracer/ray.h"
#include "../util/color.h"
#include "../util/vector3.h"
#include "../util/image.h"


namespace objects
{

class Object;
using util::Color;
using util::Vector3;


class Intersect
{
public:
    Intersect(const Object* object, bool intersects, double distance,
        const Vector3& position, const Vector3& normal)
        :
        object_ptr(object),
        intersects(intersects),
        distance(distance),
        position(position),
        normal(normal)
    {
    }

    const Object* object_ptr;
    bool intersects;
    double distance;
    util::Vector3 position;
    util::Vector3 normal;

    static Intersect noHit;
};


class Material
{
public:
    Color color;
    Color absorb;
    double reflect, refract, diffract, spec, specn;
    double rindex;
    double drefl;
    util::Image* texture;
};


class Object
{
public:
    Object();
    virtual ~Object();

    virtual Intersect intersects(const tracer::Ray& ray) const = 0;
    virtual Color get_color(Intersect intersect) const = 0;

    Material* material;
    const static double EPSILON;
};

}

#endif // OBJECT_H
