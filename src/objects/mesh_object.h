#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "object.h"
#include "box.h"

namespace objects
{


class KDTreeNode : public Box
{
};


class MeshObject : public Object
{
public:
    MeshObject();
    ~MeshObject();
};

}

#endif // MESHOBJECT_H
