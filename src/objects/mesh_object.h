#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "object.h"

#include <string>
#include <vector>

#include "box.h"
#include "triangle.h"

namespace objects
{

using tracer::Ray;

class KDTreeNode : public Box
{
public:
    KDTreeNode(const std::vector<Triangle>& triangles);
    KDTreeNode(Vector3 p1, Vector3 p2, std::vector<Triangle> triangles, int depth);

    bool is_leaf() const { return pLeft == nullptr && pRight == nullptr; }
    void create_node(Vector3 p1, Vector3 p2, std::vector<Triangle> triangles, int depth);

    KDTreeNode *pLeft, *pRight;
    int depth;
    std::vector<Triangle> triangles;

    Intersect intersects(const tracer::Ray& ray);
    Color get_color(Intersect intersect) const { return Color(0, 0, 0); }
};


class MeshObject : public Object
{
public:
    MeshObject(std::string model, double rotation, double scale, Vector3 translation);
    ~MeshObject();

    Intersect intersects(const tracer::Ray& ray) const;
    Color get_color(Intersect intersect) const;

private:
    KDTreeNode* root;
};

}

#endif // MESHOBJECT_H
