#ifndef SCENE_H
#define SCENE_H

#include "../objects/object.h"
#include "../objects/light.h"
#include "../util/color.h"

#include <vector>
#include <list>

namespace tracer
{

class Scene
{
public:
    Scene(util::Color color);
    ~Scene();

    typedef std::list<objects::Object*> ObjectList;
    typedef std::list<objects::Light*> LightList;

    void add_object(objects::Object* object_ptr);
    void add_light(objects::Light* light_ptr);

    const ObjectList& get_objects() const;
    const LightList& get_lights() const;

    objects::Intersect find_nearest_object(Ray ray);
    objects::Intersect find_nearest_light(Ray ray);

    util::Color get_backgroud() { return backgroud_color; }

private:
    ObjectList objects;
    LightList lights;
    util::Color backgroud_color;
};

}

#endif //SCENE_H
