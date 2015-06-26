#include "tracer.h"

#include <cmath>
#include <iostream>
#include <fstream>

#include "../objects/object.h"
#include "../objects/sphere.h"
#include "../objects/plane.h"
#include "../objects/light.h"
#include "../objects/pointlight.h"
#include "../util/json/json.h"

using namespace std;

namespace tracer
{

using util::Color;
using util::Vector3;
using objects::Intersect;
using objects::Object;
using objects::Sphere;
using objects::Plane;
using objects::Light;
using objects::PointLight;


Tracer::Tracer()
{

}


Tracer::~Tracer()
{

}


void Tracer::set_camera(Camera* camera)
{
    this->camera = camera;
}


void Tracer::set_scene(Scene* scene)
{
    this->scene = scene;
}


void Tracer::read_config_from_file(std::string filename)
{
    ifstream file(filename);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file, root);

    camera = create_camera(root["camera"]);
    scene = create_scene(root);
}


Ray Tracer::get_reflection_light(Ray ray, Intersect inter)
{
    const Vector3& norm = inter.normal;
    Vector3 L = - ray.direction;
    Vector3 R = norm * (L.dot(norm * 2)) - L;
    return Ray(inter.position, R);
}


tracer::Ray Tracer::get_refraction_light(Ray ray, objects::Intersect inter, double n)
{
    double cos_i = -ray.direction.dot(inter.normal);
    double sin_i = sqrt(1 - cos_i * cos_i);
    double sin_r = sin_i / n;
    double cos_r = sqrt(1 - sin_i * sin_i);
    Vector3 R = inter.normal * (cos_i / n - cos_r) + ray.direction / n;
    return Ray(inter.position, R);
    //return Ray(Vector3(0, 0, 0), Vector3(0, 0, 0));
}


Scene* Tracer::create_scene(Json::Value value)
{
    Json::Value backgroundcolor = value["backgroundcolor"];
    Scene* scene = new Scene(Color(backgroundcolor[0].asDouble(), backgroundcolor[1].asDouble(),
        backgroundcolor[2].asDouble()));
    int object_size = value["objects"].size();
    for (int i = 0; i < object_size; i++) {
        scene->add_object(create_object(value["objects"][i]));
    }
    int light_size = value["lights"].size();
    for (int i = 0; i < light_size; i++) {
        scene->add_light(create_light(value["lights"][i]));
    }
    return scene;
}


objects::Object* Tracer::create_object(Json::Value value)
{
    Object* object = nullptr;
    if (value["type"].asString() == "Sphere") {
        Json::Value center = value["center"];
        object = new Sphere(Vector3(center[0].asDouble(),
            center[1].asDouble(), center[2].asDouble()), value["radius"].asDouble());
    }
    else if (value["type"].asString() == "Plane") {
        Json::Value normal = value["normal"];
        Json::Value point = value["point"];
        object = new Plane(Vector3(normal[0].asDouble(), normal[1].asDouble(), normal[2].asDouble()),
            Vector3(point[0].asDouble(), point[1].asDouble(), point[2].asDouble()));
    }
    else {

    }
    objects::Material* material = new objects::Material;
    material->diffract = value["diffract"].asDouble();
    material->reflect = value["reflect"].asDouble();
    material->refract = value["refract"].asDouble();
    material->rindex = value["rindex"].asDouble();
    material->spec = value["spec"].asDouble();
    material->specn = value["specn"].asDouble();
    Json::Value color = value["color"];
    material->color = Color(color[0].asDouble(), color[1].asDouble(), color[2].asDouble());
    if (object) {
        object->material = material;
    }
    return object;
}


objects::Light* Tracer::create_light(Json::Value value)
{
    Light* light = nullptr;
    if (value["type"].asString() == "point") {
        Json::Value position = value["position"];
        Json::Value color = value["color"];
        light = new PointLight(Vector3(position[0].asDouble(), position[1].asDouble(), position[2].asDouble()),
            Color(color[0].asDouble(), color[1].asDouble(), color[2].asDouble()));
    }
    else {

    }
    return light;
}


Camera* Tracer::create_camera(Json::Value value)
{
    Vector3 position(value["position"][0].asDouble(),
        value["position"][1].asDouble(),
        value["position"][2].asDouble());
    Vector3 up(value["up"][0].asDouble(),
        value["up"][1].asDouble(),
        value["up"][2].asDouble());
    Vector3 front(value["front"][0].asDouble(),
        value["front"][1].asDouble(),
        value["front"][2].asDouble());
    Camera* camera = new Camera(position, front, up,
        value["width"].asInt(), value["height"].asInt(), value["focus"].asInt());
    util::Image* image = new util::Image(value["width"].asInt(), value["height"].asInt());
    camera->set_image(image);
    return camera;
}


void Tracer::run()
{
    int width = camera->get_width();
    int height = camera->get_height();

    for (int i = 0; i < width; i++) {
        //cout << i + 1 << endl;
        for (int j = 0; j < height; j++) {
            Color color = raytrace(camera->emit(i, j), 0, false);
            int x = int(255 * color.get_r());
            camera->set_color(i, j, color);
        }
    }
}


void Tracer::show()
{
    camera->show();
}


Color Tracer::raytrace(Ray ray, int depth, bool refreacted)
{
    if (depth > 10) {
        return Color(0, 0, 0);
    }
    using util::Vector3;
    objects::Intersect intersect = scene->find_nearest_object(ray);
    if (!intersect.intersects) {
        return Color(0, 0, 0);
    }
    objects::Object* object = intersect.object_ptr;
    Color ret;
    ret += scene->get_backgroud() * object->material->diffract;
    for (const auto& light : scene->get_lights()) {
        Vector3 L = light->get_light_vec(intersect.position);
        double dist = L.module();
        L = L.normalize();
        if ((scene->find_nearest_object(Ray(intersect.position, L))).distance < dist) {
            continue;
        }
        double dot = L.dot(intersect.normal);
        if (dot > 0) {
            if (object->material->diffract > 0) {
                ret += light->get_color() * object->material->color * dot * object->material->diffract;
            }
            if (object->material->spec > 0) {
                ret += light->get_color() * pow(dot, object->material->specn) * object->material->spec;
            }
        }
    }
    if (object->material->reflect > 0) {
        Ray reflection = get_reflection_light(ray, intersect);
        ret += raytrace(reflection, depth + 1, refreacted) * object->material->reflect;
    }
    if (object->material->refract > 0) {
        double n = object->material->rindex;
        if (refreacted) {
            n = 1 / n;
        }
        Ray refraction = get_refraction_light(ray, intersect, object->material->rindex);
        Color rcol = raytrace(refraction, depth + 1, !refreacted) * object->material->reflect;
        if (refreacted) {
            Color absorb = object->material->absorb * intersect.distance;
            rcol = Color(exp(-absorb.get_r()), exp(-absorb.get_g()), exp(-absorb.get_b()))
                * object->material->refract;
        }
        else {
            rcol = rcol * object->material->refract;
        }
        ret += rcol;
    }
    ret.confine();
    return ret;
}

}
