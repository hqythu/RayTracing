#include <iostream>

#include "util/vector3.h"
#include "util/image.h"
#include "tracer/camera.h"
#include "tracer/tracer.h"
#include "tracer/scene.h"
#include "objects/sphere.h"
#include "objects/pointlight.h"


using util::Vector3;
using util::Image;
using tracer::Camera;
using tracer::Tracer;
using tracer::Scene;
using namespace objects;

int main()
{
    const int width = 800;
    const int height = 600;
    Image* img = new Image(width, height);
    Camera* camera = new Camera(Vector3(0, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1),
        width, height, 1000);
    camera->set_image(img);
    Scene* scene = new Scene(Color(0.2, 0.2, 0.2));
    objects::Sphere s(Vector3(0, 1000, 0), 200);
    s.material = new Material;
    s.material->diffract = 0.8;
    scene->add_object(&s);
    PointLight l(Vector3(0, 0, 0), Color(1, 1, 0));
    scene->add_light(&l);
    Tracer* tracer = new Tracer;
    tracer->set_camera(camera);
    tracer->set_scene(scene);
    tracer->run();
    img->show();
    return 0;
}
