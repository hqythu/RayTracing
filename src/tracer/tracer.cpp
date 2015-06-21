#include "tracer.h"

#include <iostream>

using namespace std;

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
        cout << i + 1 << endl;
        for (int j = 0; j < height; j++) {
            Color color = raytrace(camera->emit(i, j), 0);
            int x = int(255 * color.get_r());
            camera->set_color(i, j, color);
        }
    }
}


Color Tracer::raytrace(Ray ray, int depth)
{
    using util::Vector3;
    objects::Intersect intersect = scene->find_nearest_object(ray);
    if (!intersect.intersects) {
        return Color(0, 0, 0);
    }
    objects::Object* object = intersect.object_ptr;
    Color ret;
    ret += scene->get_backgroud() * object->material->diffract;
    for (const auto& light : scene->get_lights()) {
        Vector3 L = light->get_light_vec(intersect.position).normalize();
        double dot = L.dot(intersect.normal);
        if (dot > 0) {
            ret += light->get_color() * dot * object->material->diffract;
        }
    }
    ret.confine();
    return ret;
}

}
