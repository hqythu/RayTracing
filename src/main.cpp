#include <iostream>

#include "util/vector3.h"
#include "util/image.h"
#include "tracer/camera.h"
#include "tracer/tracer.h"
#include "tracer/scene.h"
#include "objects/sphere.h"


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
    Camera* camera = new Camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0),
        width, height, 0.25);
    camera->set_image(img);
    Scene* scene = new Scene;
    Tracer* tracer = new Tracer;
    tracer->set_camera(camera);
    tracer->set_scene(scene);
    tracer->run();
    img->show();
    return 0;
}
