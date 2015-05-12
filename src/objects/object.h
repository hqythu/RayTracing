#ifndef OBJECT_H
#define OBJECT_H

namespace objects
{

class Object
{
public:
    Object();
    virtual ~Object();

    void intersects();
};

}

#endif // OBJECT_H
