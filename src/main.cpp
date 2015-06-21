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

    objects::Sphere s1(Vector3(-200, 800, 0), 100);
    s1.material = new Material;
    s1.material->diffract = 0.4;
    s1.material->reflect = 0.8;
    s1.material->spec = 0.8;
    s1.material->specn = 50;
    s1.material->color = Color(0, 0, 1);

    objects::Sphere s2(Vector3(200, 1200, 0), 100);
    s2.material = new Material;
    s2.material->diffract = 0.4;
    s2.material->reflect = 0.8;
    s2.material->spec = 0.8;
    s2.material->specn = 50;
    s2.material->color = Color(1, 0, 0);

    scene->add_object(&s1);
    scene->add_object(&s2);

    PointLight l1(Vector3(0, 0, 1000), Color(1, 1, 1));
    PointLight l2(Vector3(0, 500, 500), Color(0, 0, 0));

    scene->add_light(&l1);
    scene->add_light(&l2);

    Tracer* tracer = new Tracer;
    tracer->set_camera(camera);
    tracer->set_scene(scene);
    tracer->run();
    img->show();

    return 0;
}
