#ifndef TRACER_H
#define TRACER_H

#include "../objects/object.h"
#include "camera.h"
#include "ray.h"
#include "scene.h"

namespace tracer
{

typedef util::Vector3 Color;

class Tracer
{
public:
    Tracer();
    ~Tracer();

    void set_camera(Camera* camera);

    void run();

private:
    Color raytrace();

    Camera* camera;
    Scene* scene;
};

}

#endif // TRACER_H
