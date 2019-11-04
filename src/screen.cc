#include <raytracer/screen.hh>

#include <algorithm>
#include <cmath>
#ifdef PROGRESS_BAR
# include <iostream>
# include <mutex>
# include <thread>
#endif
#include <vector>

#include <raytracer/constants.hh>
#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/trace.hh>
#include <raytracer/types/image.hh>
#include <raytracer/types/scene.hh>
#include <raytracer/types/vector.hh>
#include <raytracer/types/triangle.hh>
#include <iostream>

using namespace raytracer;

static auto create_kdtree(const Scene& scene)
{
    std::vector<Triangle> triangles;

    for (const auto& object: scene.objects)
        for (auto triangle: object.faces())
            triangles.push_back(std::move(triangle));

    return KDTree(std::move(triangles));
}

static auto compute_rays(const Scene& scene, Vector& down, Vector& right)
{
    Vector forward = scene.camera.forward;
    forward.normalize();

    down = - scene.camera.up;
    down.normalize();

    right = scene.camera.forward.cross(scene.camera.up);
    right.normalize();

    float s_down = std::tan(static_cast<float>(scene.camera.fov * M_PI / 180.f) * 0.5f);
    float s_right = s_down;

    /* here we handle the aspect ratio */
    if (scene.width > scene.height)
        s_down *= static_cast<float>(scene.height) / static_cast<float>(scene.width);
    else
        s_right *= static_cast<float>(scene.width) / static_cast<float>(scene.height);

    Vector ray = forward - s_down * down - s_right * right;

    float step_x = (2.f * s_right) / static_cast<float>(scene.width);
    float step_y = (2.f * s_down) / static_cast<float>(scene.height);

    down *= step_y;
    right *= step_x;

    return ray;
}

Vector gamma(const Vector& color)
{
    return color.unaryExpr([] (auto x) { return std::exp((1.f / 2.2f) * std::log(x)); });
}

Image raytracer::compute_screen(const Scene& scene)
{
#ifdef PROGRESS_BAR
    static std::mutex io_mutex;
#endif

    static constexpr unsigned spp = 4;
    static constexpr unsigned spp_aux = 2;
    static constexpr unsigned depth = 4;

    Image res = Image(scene.width, scene.height);
    KDTree kd_tree = create_kdtree(scene);

    Vector down, right;
    Vector top_left_corner = compute_rays(scene, down, right);

    auto nb_pixels = scene.height * scene.width;

#if defined(_OPENMP)
# pragma omp parallel for schedule(dynamic)
#endif
    for (unsigned i = 0; i < nb_pixels; i++)
    {
#ifdef PROGRESS_BAR
        if (!(i % 32))
        {
            std::lock_guard<std::mutex> lock(io_mutex);
            std::cout << "> " << static_cast<unsigned>(static_cast<float>(i) / static_cast<float>(nb_pixels) * 100.f)
                << "% (pixel " << i << ") <" << '\r' << std::flush;
        }
#endif

        auto y = i / scene.width;
        auto x = i % scene.width;

        Vector ray_dir = top_left_corner + y * down + x * right;
        Vector color = Vector::Zero();
        for (auto step = 0u; step < spp; ++step)
            color += trace(kd_tree, scene.camera.pos, ray_dir, spp_aux, depth);
        color /= spp;
        res.set_pixel(x, y, gamma(color).unaryExpr([] (auto x) { return std::clamp(x, 0.f, 1.f); }));
    }

#ifdef PROGRESS_BAR
    std::cout << "> 100% (all pixels processed) <" << std::endl;
#endif

    return res;
}
