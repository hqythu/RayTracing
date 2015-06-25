#include "scene.h"

#include <limits>

using util::Color;


namespace tracer
{

Scene::Scene(Color color)
    : backgroud_color(color)
{

}

Scene::~Scene()
{

}

void Scene::add_object(objects::Object* object_ptr)
{
    this->objects.push_back(object_ptr);
}

void Scene::add_light(objects::Light* light_ptr)
{
    this->lights.push_back(light_ptr);
}

objects::Intersect Scene::find_nearest_object(Ray ray)
{
    double min = std::numeric_limits<double>::max();
    using objects::Intersect;
    Intersect inter = Intersect::noHit;
    for (const auto& object : objects) {
        Intersect tmp = object->intersects(ray);
        if (tmp.intersects && tmp.distance < min) {
            inter = tmp;
            min = tmp.distance;
        }
    }
    return inter;
}

const Scene::ObjectList& Scene::get_objects() const
{
    return objects;
}

const Scene::LightList& Scene::get_lights() const
{
    return lights;
}

}
