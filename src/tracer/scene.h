#ifndef SCENE_H
#define SCENE_H

#include "../objects/object.h"

#include <vector>

namespace tracer
{

typedef std::vector<objects::Object*> ObjectVec;

class Scene
{
public:
    Scene();
    ~Scene();

    void add_object(objects::Object* object_ptr);
    const ObjectVec& get_objects() const;

private:
    ObjectVec objects;
};

}

#endif //SCENE_H
