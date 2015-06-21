#ifndef SCENE_H
#define SCENE_H

#include "../objects/object.h"
#include "../objects/light.h"

#include <vector>
#include <list>

namespace tracer
{

class Scene
{
public:
    Scene();
    ~Scene();

    typedef std::list<objects::Object*> ObjectList;
    typedef std::list<objects::Light*> LightList;

    void add_object(objects::Object* object_ptr);
    void add_light(objects::Light* light_ptr);
    const ObjectList& get_objects() const;
    const LightList& get_lights() const;

private:
    ObjectList objects;
    LightList lights;
};

}

#endif //SCENE_H
