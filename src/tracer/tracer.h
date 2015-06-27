#ifndef TRACER_H
#define TRACER_H

#include <string>

#include "../objects/object.h"
#include "../objects/light.h"
#include "../util/color.h"
#include "../util/vector3.h"
#include "../util/json/json.h"
#include "camera.h"
#include "ray.h"
#include "scene.h"

namespace tracer
{

class Tracer
{
public:
    Tracer();
    ~Tracer();

    void set_camera(Camera* camera);
    void set_scene(Scene* scene);
    void read_config_from_file(std::string filename);

    void run();
    void show();

private:
    util::Color raytrace(const Ray& ray, int depth, bool refreacted);

    Ray get_reflection_light(const Ray& ray, const objects::Intersect& inter);
    Ray get_refraction_light(const Ray& ray, const objects::Intersect& inter, double n);

    Scene* create_scene(Json::Value);
    objects::Object* create_object(Json::Value);
    objects::Light* create_light(Json::Value);
    Camera* create_camera(Json::Value);

    Camera* camera;
    Scene* scene;
};

}

#endif // TRACER_H
