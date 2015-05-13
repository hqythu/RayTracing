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

const ObjectVec& Scene::get_objects() const
{
    return objects;
}

}