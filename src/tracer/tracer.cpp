#include "tracer.h"

namespace tracer
{

using util::Color;


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


void Tracer::set_scene(Scene* scene)
{
    this->scene = scene;
}


void Tracer::run()
{
    int width = camera->get_width();
    int height = camera->get_height();

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Color color = raytrace(camera->emit(i, j), 0);
            camera->set_color(i, j, color);
        }
    }
}


Color Tracer::raytrace(Ray ray, int depth)
{
    return Color(0, 0, 1);
}

}
