#include <raytracer/utils/scene-loader.hh>

#include <raytracer/types/scene.hh>
#include <raytracer/utils/filesystem.hh>
#include <raytracer/utils/json-utils.hh>

using namespace raytracer;

Scene raytracer::load_scene(const char* filename)
{
    auto j = parse_json(filename);

    // Saving current working directory
    auto current_dir = filesystem::current_path();

    // Changing current working dir. to the scene containing directory
    {
        auto file = filesystem::path(filename);

        if (file.has_parent_path())
            filesystem::current_path(file.parent_path());
    }

    /*
     * Triggers recursive parsing using all Scene subtypes: Camera, Light, ...
     *
     * Scene and each of its subtypes implements its own parsing using template
     * specialization on method raytracer::from_json (thanks to nlohmann::json)
     */
    auto scene = j.get<Scene>();

    // Restoring old working dir.
    filesystem::current_path(current_dir);

    return scene;
}
