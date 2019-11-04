#include <exception>
#include <iostream>
#include <thread>

#include <raytracer/utils/save-png.hh>
#include <raytracer/utils/scene-loader.hh>
#include <raytracer/screen.hh>

using namespace raytracer;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <scene.json> <output.png>" << std::endl;
        return 1;
    }

    const auto scene_filename = argv[1];
    const auto output_filename = argv[2];

#ifdef NDEBUG
    try
    {
#endif
        Scene scene = load_scene(scene_filename);

        std::cout << "# Threads   : " << std::thread::hardware_concurrency() << std::endl;

        std::cout << "Scene height: " << scene.height << std::endl;
        std::cout << "Scene width : " << scene.width << std::endl;
        std::cout << "Scene pixels: " << scene.height * scene.width << std::endl;
        std::cout << "# Meshes    : " << scene.meshes.size() << std::endl;
        std::cout << "# Materials : " << scene.materials.size() << std::endl;
        std::cout << "# Objects   : " << scene.objects.size() << std::endl;
        std::cout << "# Vertices  : " << scene.n_vertices() << std::endl;
        std::cout << "# Faces     : " << scene.n_faces() << std::endl;

        Image res = compute_screen(scene);

        save_png(res, output_filename);
#ifdef NDEBUG
    }
    catch (const std::exception& ex)
    {
        std::cerr << "An error occurred: " << ex.what() << std::endl;
        return 1;
    }
#endif

    return 0;
}
