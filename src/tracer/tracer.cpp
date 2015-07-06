#include "tracer.h"

#include <cmath>
#include <iostream>
#include <fstream>

#include "../objects/object.h"
#include "../objects/sphere.h"
#include "../objects/plane.h"
#include "../objects/box.h"
#include "../objects/triangle.h"
#include "../objects/mesh_object.h"
#include "../objects/light.h"
#include "../objects/pointlight.h"
#include "../objects/arealight.h"
#include "../util/json/json.h"

using namespace std;

namespace tracer
{

using util::Color;
using util::Vector3;
using util::Image;
using objects::Intersect;
using objects::Object;
using objects::Sphere;
using objects::Plane;
using objects::Box;
using objects::Triangle;
using objects::MeshObject;
using objects::Light;
using objects::PointLight;
using objects::AreaLight;


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

    grid = root["anti_aliasing_grid"].asInt();
}


Ray Tracer::get_reflection_light(const Ray& ray, const Intersect& inter)
{
    const Vector3& norm = inter.normal;
    Vector3 L = - ray.direction;
    Vector3 R = norm * (L.dot(norm * 2)) - L;
    return Ray(inter.position, R.normalize());
}


Ray Tracer::get_refraction_light(const Ray& ray, const Intersect& inter, double n)
{
    double cos_i = -ray.direction.dot(inter.normal);
    double sin_i = sqrt(1 - cos_i * cos_i);
    double sin_r = sin_i / n;
    double cos_r = sqrt(1 - sin_i * sin_i);
    Vector3 R = inter.normal * (cos_i / n - cos_r) + ray.direction / n;
    return Ray(inter.position, R.normalize());
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
        Json::Value dx = value["dx"];
        object = new Plane(Vector3(normal[0].asDouble(), normal[1].asDouble(), normal[2].asDouble()),
            Vector3(point[0].asDouble(), point[1].asDouble(), point[2].asDouble()),
            Vector3(dx[0].asDouble(), dx[1].asDouble(), dx[2].asDouble()));
    }
    else if (value["type"].asString() == "Box") {
        double x1 = value["x1"].asDouble();
        double x2 = value["x2"].asDouble();
        double y1 = value["y1"].asDouble();
        double y2 = value["y2"].asDouble();
        double z1 = value["z1"].asDouble();
        double z2 = value["z2"].asDouble();
        object = new Box(x1, x2, y1, y2, z1, z2);
    }
    else if (value["type"].asString() == "Triangle") {
        Json::Value p0 = value["p0"];
        Json::Value p1 = value["p1"];
        Json::Value p2 = value["p2"];
        object = new Triangle(Vector3(p0[0].asDouble(), p0[1].asDouble(), p0[2].asDouble()),
            Vector3(p1[0].asDouble(), p1[1].asDouble(), p1[2].asDouble()),
            Vector3(p2[0].asDouble(), p2[1].asDouble(), p2[2].asDouble()));
    }
    else if (value["type"].asString() == "Mesh") {
        Json::Value trans = value["translation"];
        object = new MeshObject(value["model"].asString(), value["rotation"].asDouble(), value["scale"].asDouble(),
            Vector3(trans[0].asDouble(), trans[1].asDouble(), trans[2].asDouble()));
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
    material->drefl = value["drefl"].asDouble();
    Json::Value color = value["color"];
    material->color = Color(color[0].asDouble(), color[1].asDouble(), color[2].asDouble());
    Json::Value absorb = value["absorb"];
    material->absorb = Color(absorb[0].asDouble(), absorb[1].asDouble(), absorb[2].asDouble());

    if (value["texture"].isNull()) {
        material->texture = nullptr;
    }
    else {
        Image *img = new Image;
        img->read(value["texture"].asString());
        material->texture = img;
    }

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
    else if (value["type"].asString() == "area") {
        Json::Value position = value["position"];
        Json::Value color = value["color"];
        Json::Value Dx = value["Dx"];
        Json::Value normal = value["normal"];
        light = new AreaLight(Vector3(position[0].asDouble(), position[1].asDouble(), position[2].asDouble()),
            Vector3(normal[0].asDouble(), normal[1].asDouble(), normal[2].asDouble()),
            value["dx"].asDouble(), value["dy"].asDouble(),
            Vector3(Dx[0].asDouble(), Dx[1].asDouble(), Dx[2].asDouble()),
            Color(color[0].asDouble(), color[1].asDouble(), color[2].asDouble()), value["soft_shadow_grid"].asInt());
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
        value["width"].asInt(), value["height"].asInt(),
        value["ratio"].asInt(), value["focus"].asInt(),
        value["depth_grid"].asInt(), value["depth_range"].asInt());
    util::Image* image = new util::Image(value["width"].asInt(), value["height"].asInt());
    camera->set_image(image);
    return camera;
}


void Tracer::run()
{
    int width = camera->get_width();
    int height = camera->get_height();

    Image *img = new Image(width * grid + 1, height * grid + 1);

    for (int i = 0; i < width * grid + 1; i++) {
        cout << (i + 1) / grid << "/" << width << endl;
        for (int j = 0; j < height * grid + 1; j++) {
            vector<Ray>& rays = camera->emit(static_cast<double>(i) / grid, static_cast<double>(j) / grid);
            Color color;
            for (const auto& ray : rays) {
                color += raytrace(ray, 0, false);
            }
            color = color / rays.size();
            img->set_color(i, j, color);
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Color color;
            for (int ii = 0; ii <= grid; ii++) {
                for (int jj = 0; jj <= grid; jj++) {
                    color += img->get_color(i * grid + ii, j * grid + jj);
                }
            }
            color = color / ((grid + 1) * (grid + 1));
            camera->set_color(i, j, color);
        }
    }
}


void Tracer::show()
{
    camera->show();
}


void Tracer::save(std::string filename)
{
    camera->save(filename);
}


Color Tracer::raytrace(const Ray& ray, int depth, bool refreacted)
{
    if (depth > 10) {
        return Color(0, 0, 0);
    }
    using util::Vector3;
    objects::Intersect intersect = scene->find_nearest_object(ray);
    objects::Intersect intersect_l = scene->find_nearest_light(ray);
    if (intersect_l.intersects && (intersect_l.distance < intersect.distance || !intersect.intersects)) {
        return intersect_l.object_ptr->get_color();
    }
    if (!intersect.intersects && !intersect_l.intersects) {
        return Color(0, 0, 0);
    }
    const objects::Object* object = intersect.object_ptr;
    Color ret;
    ret += scene->get_backgroud() * object->get_color(intersect) * object->material->diffract;
    Color tmp;
    for (const auto& light : scene->get_lights()) {
        vector<Vector3>& light_vecs= light->get_light_vec(intersect.position);
        for (const auto& vec : light_vecs) {
            Vector3 L = vec;
            double dist = L.module();
            L = L.normalize();
            if ((scene->find_nearest_object(Ray(intersect.position, L))).distance < dist) {
                continue;
            }
            double dot = L.dot(intersect.normal);
            if (dot > 0) {
                if (object->material->diffract > 0) {
                    tmp += light->get_color() * object->get_color(intersect) * dot * object->material->diffract;
                }
                if (object->material->spec > 0) {
                    tmp += light->get_color() * pow(dot, object->material->specn) * object->material->spec;
                }
            }
        }
        tmp = tmp / light_vecs.size();
    }
    ret += tmp;
    if (object->material->reflect > 0) {
        Ray reflection = get_reflection_light(ray, intersect);
        if (object->material->drefl > 0) {
            const int SAMPLE = 16;
            Vector3 Dx = (reflection.direction * Vector3(1, 0, 0)).normalize();
            Vector3 Dy = (Dx * reflection.direction).normalize();
            Dx = Dx * object->material->drefl;
            Dy = Dy * object->material->drefl;

            Color color;
            for (int i = 0; i < SAMPLE; i++) {
                double x, y;
                do {
                    x = rand() / 32768.0;
                    y = rand() / 32768.0;
                } while (x * x + y * y < 1);
                color += raytrace(Ray(reflection.start, reflection.direction + Dx * x + Dy * y), 10, refreacted);
            }
            ret += color / SAMPLE * object->get_color(intersect) * object->material->reflect;
        }
        else {
            ret += raytrace(reflection, depth + 1, refreacted) * object->get_color(intersect) *
                object->material->reflect;
        }
    }
    if (object->material->refract > 0) {
        double n = object->material->rindex;
        if (refreacted) {
            n = 1 / n;
        }
        Ray refraction = get_refraction_light(ray, intersect, n);
        Color rcol = raytrace(refraction, depth + 1, !refreacted) * object->get_color(intersect) 
            * object->material->refract;
        if (refreacted) {
            Color absorb = object->material->absorb * intersect.distance;
            rcol = rcol * Color(exp(-absorb.get_r()), exp(-absorb.get_g()), exp(-absorb.get_b()));
        }
        ret += rcol;
    }
    ret.confine();
    return ret;
}

}
