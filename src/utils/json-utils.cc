#include <raytracer/utils/json-utils.hh>

#include <cerrno>
#include <fstream>
#include <system_error>

using namespace raytracer;

json raytracer::parse_json(const char* filename)
{
    nlohmann::json j;

    // Loading JSON file
    {
        std::ifstream i(filename);

        if (!i.good())
            throw std::system_error(errno, std::system_category());

        i >> j;
    }

    return j;
}
