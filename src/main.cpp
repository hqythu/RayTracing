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
    Tracer* tracer = new Tracer;
    tracer->read_config_from_file("test/config.json");
    tracer->run();
    tracer->show();
    tracer->save("output.jpg");

    return 0;
}
