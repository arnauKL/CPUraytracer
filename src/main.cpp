#include "camera.h"
#include "config.hpp"
#include "hittable/Sphere.h"
#include "hittable/hittable.h"
#include "hittable/hittable_list.h"

#include <chrono>
using namespace std::chrono; // To time execution

int main() {

    /// World settings
    Hittable_list world; // Stores a list of objects present that can be hit

    world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5));    // Lil sphere
    world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100)); // Massive sphere to emulate a ground

    // Define camera
    Camera cam;
    cam.aspect_ratio = conf::ASPECT_RATIO;
    cam.image_width = conf::W_WIDTH;

    // Render (and time)
    auto start = high_resolution_clock::now();
    cam.render(world);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::clog << "\rDone in " << duration.count() / 1000.0 << " ms                        \n";

    // '\r' replaces characters

    return 0;
}
