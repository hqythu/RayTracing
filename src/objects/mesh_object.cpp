#include "mesh_object.h"

#include "../util/SimpleObject.h"
#include "triangle.h"

#include <vector>
#include <limits>
#include <algorithm>


namespace objects
{

using std::string;
using std::vector;


KDTreeNode::KDTreeNode(const std::vector<Triangle>& triangles)
{
    pLeft = nullptr;
    pRight = nullptr;

    double min_x = std::numeric_limits<double>::max();
    double max_x = -std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();
    double max_y = -std::numeric_limits<double>::max();
    double min_z = std::numeric_limits<double>::max();
    double max_z = -std::numeric_limits<double>::max();

    for (const auto& tri : triangles) {
        if (tri.min_x() < min_x) min_x = tri.min_x();
        if (tri.max_x() > max_x) max_x = tri.max_x();
        if (tri.min_y() < min_y) min_y = tri.min_y();
        if (tri.max_y() > max_y) max_y = tri.max_y();
        if (tri.min_z() < min_z) min_z = tri.min_z();
        if (tri.max_z() > max_z) max_z = tri.max_z();
    }

    Vector3 p1(min_x, min_y, min_z);
    Vector3 p2(max_x, max_y, max_z);

    create_node(p1, p2, triangles, 0);
}


KDTreeNode::KDTreeNode(Vector3 p1, Vector3 p2, std::vector<Triangle> triangles, int depth)
{
    create_node(p1, p2, triangles, depth);
}


void KDTreeNode::create_node(Vector3 p1, Vector3 p2, std::vector<Triangle> triangles, int depth)
{
    this->depth = depth;

    x1 = p1.get_x();
    x2 = p2.get_x();
    y1 = p1.get_y();
    y2 = p2.get_y();
    z1 = p1.get_z();
    z2 = p2.get_z();

    if (triangles.size() < 3 || depth > 100) {
        this->triangles = std::move(triangles);
        pLeft = pRight = nullptr;
        return;
    }

    Vector3 ptemp1 = p1;
    Vector3 ptemp2 = p2;

    if (depth % 3 == 0) {
        sort(triangles.begin(), triangles.end(), [](const Triangle& a, const Triangle& b) {
            return a.max_x() < b.max_x();
        });
        ptemp2.x = (triangles.begin() + triangles.size() / 2 - 1)->max_x();
    }
    else if (depth % 3 == 1) {
        sort(triangles.begin(), triangles.end(), [](const Triangle& a, const Triangle& b) {
            return a.max_y() < b.max_y();
        });
        ptemp2.y = (triangles.begin() + triangles.size() / 2 - 1)->max_y();
    }
    else {
        sort(triangles.begin(), triangles.end(), [](const Triangle& a, const Triangle& b) {
            return a.max_z() < b.max_z();
        });
        ptemp2.z = (triangles.begin() + triangles.size() / 2 - 1)->max_z();
    }

    vector<Triangle> t1(triangles.begin(), triangles.begin() + triangles.size() / 2);
    vector<Triangle> t2(triangles.begin() + triangles.size() / 2, triangles.end());

    double tempmin = std::numeric_limits<double>::max();
    if (depth % 3 == 0) {
        for (const auto& t : t2) {
            double temp = t.min_x();
            if (temp < tempmin) tempmin = temp;
        }
        ptemp1.x = tempmin;
    }
    else if (depth % 3 == 1) {
        for (const auto& t : t2) {
            double temp = t.min_y();
            if (temp < tempmin) tempmin = temp;
        }
        ptemp1.y = tempmin;
    }
    else {
        for (const auto& t : t2) {
            double temp = t.min_z();
            if (temp < tempmin) tempmin = temp;
        }
        ptemp1.z = tempmin;
    }

    pLeft = new KDTreeNode(p1, ptemp2, t1, depth + 1);
    pRight = new KDTreeNode(ptemp1, p2, t2, depth + 1);
}


Intersect KDTreeNode::intersects(const Ray& ray)
{
    if (!Box::intersects(ray).intersects) {
        return Intersect::noHit;
    }
    if (is_leaf()) {
        double min = std::numeric_limits<double>::max();
        Intersect inter = Intersect::noHit;
        for (const auto& t : triangles) {
            Intersect tmp = t.intersects(ray);
            if (tmp.intersects && tmp.distance < min) {
                min = tmp.distance;
                inter = tmp;
            }
        }
        return inter;
    }

    Intersect l_tmp = Intersect::noHit;
    if (pLeft->Box::intersects(ray).intersects) {
        l_tmp = pLeft->intersects(ray);
    }
    Intersect r_tmp = Intersect::noHit;
    if (pRight->Box::intersects(ray).intersects) {
        r_tmp = pRight->intersects(ray);
    }

    if (l_tmp.intersects && r_tmp.intersects) {
        if (l_tmp.distance < r_tmp.distance) {
            return l_tmp;
        }
        else {
            return r_tmp;
        }
    }
    else if (l_tmp.intersects) {
        return l_tmp;
    }
    else if (r_tmp.intersects) {
        return r_tmp;
    }
    else {
        return Intersect::noHit;
    }
}


MeshObject::MeshObject(string model, double rotation, double scale, Vector3 translation)
{
    root = nullptr;

    SimpleOBJ::CSimpleObject obj;
    obj.LoadFromObj(model.c_str());

    vector<Triangle> triangles;

    for (int i = 0; i < obj.m_nTriangles; i++) {
        SimpleOBJ::Vec3f v;
        int p_0, p_1, p_2;
        p_0 = obj.m_pTriangleList[i][0];
        p_1 = obj.m_pTriangleList[i][1];
        p_2 = obj.m_pTriangleList[i][2];

        v = obj.m_pVertexList[p_0];
        Vector3 p0 = Vector3(v.x * scale, v.y * scale, v.z * scale) + translation;
        v = obj.m_pVertexList[p_1];
        Vector3 p1 = Vector3(v.x * scale, v.y * scale, v.z * scale) + translation;
        v = obj.m_pVertexList[p_2];
        Vector3 p2 = Vector3(v.x * scale, v.y * scale, v.z * scale) + translation;

        triangles.push_back(Triangle(p0, p1, p2));
    }

    root = new KDTreeNode(triangles);
}


MeshObject::~MeshObject()
{
}


objects::Intersect MeshObject::intersects(const tracer::Ray& ray) const
{
    if (root) {
        Intersect inter =  root->intersects(ray);
        inter.object_ptr = this;
        return inter;
    }
    else {
        return Intersect::noHit;
    }
}


Color MeshObject::get_color(Intersect intersect) const
{
    if (material) {
        return material->color;
    }
    else {
        return Color(0, 0, 0);
    }
}

}
