#include "tracer.h"

namespace tracer
{

Tracer::Tracer()
{

}

Tracer::~Tracer()
{

}

void Tracer::set_camera(Camera* camera)
{
    this->camera = camera;
}

void Tracer::run()
{

}

Color Tracer::raytrace(Ray ray, int depth)
{
    return Color(0, 0, 0);
}

}
