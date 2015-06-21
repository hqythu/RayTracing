#include "scene.h"


namespace tracer
{

Scene::Scene()
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

const Scene::ObjectList& Scene::get_objects() const
{
    return objects;
}

const Scene::LightList& Scene::get_lights() const
{
    return lights;
}

}
