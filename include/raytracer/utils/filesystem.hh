#pragma once

#ifdef FILESYSTEM_EXPERIMENTAL
 # include <experimental/filesystem>
#else
 # include <filesystem>
#endif

namespace raytracer
{
#ifdef FILESYSTEM_EXPERIMENTAL
    namespace filesystem = std::experimental::filesystem;
#else
    namespace filesystem = std::filesystem;
#endif
}
