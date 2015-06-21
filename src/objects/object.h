#ifndef OBJECT_H
#define OBJECT_H

#include "../tracer/ray.h"
#include "../util/color.h"


namespace objects
{

class Object;
typedef util::Color Color;


class Intersect
{
public:
    Intersect(Object* object, bool intersects, double distance,
        const util::Vector3& position, const util::Vector3& normal)
        :
        object_ptr(object),
        intersects(intersects),
        distance(distance),
        position(position),
        normal(normal)
    {
    }

    Object* object_ptr;
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
    double reflect, refract, diffract;
};


class Object
{
public:
    Object();
    virtual ~Object();

    virtual Intersect intersects(const tracer::Ray& ray) = 0;

    Material* material;
};

}

#endif // OBJECT_H
