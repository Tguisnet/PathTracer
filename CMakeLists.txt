cmake_minimum_required(VERSION 3.12)
project(my_raytracer)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
    message("Clang or G++ detected, enabling optimizations")
    add_compile_options(-Ofast -march=native -fno-trapping-math -fno-signed-zeros)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules/")

find_package(Eigen3 REQUIRED)
find_package(Filesystem REQUIRED COMPONENTS Experimental Final)
find_package(OpenMP)

if (${CXX_FILESYSTEM_HEADER} STREQUAL "experimental/filesystem")
    add_definitions(-DFILESYSTEM_EXPERIMENTAL)
endif ()

if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_subdirectory(dependencies/)

# Adds progress bar for processing
add_definitions(-DPROGRESS_BAR)

add_executable(my_raytracer
        src/main.cc
        src/types/image.cc
        src/types/triangle.cc
        src/utils/mesh-loader.cc
        src/utils/save-png.cc
        src/utils/scene-loader.cc
        src/utils/faces-range.cc
        src/screen.cc
        src/kd-tree/aabb.cc
        src/kd-tree/kd-tree.cc
        src/kd-tree/construction.cc
        src/kd-tree/traversal.cc
        src/utils/json-utils.cc
        src/trace.cc
        src/intersect.cc
        src/types/bsdf.cc
        src/types/bsdfs/mirror-bsdf.cc
        src/types/bsdfs/metal-bsdf.cc
        src/types/bsdfs/glass-bsdf.cc
        src/types/bsdfs/lambert-bsdf.cc src/utils/math-utils.cc)

target_include_directories(my_raytracer PRIVATE include/)

target_link_libraries(my_raytracer std::filesystem OpenMeshCore lodepng nlohmann::json Eigen3::Eigen)

add_executable(test_save_png
        src/types/image.cc
        src/utils/save-png.cc
        tests/test-save-png.cc)

target_include_directories(test_save_png PRIVATE include/)

target_link_libraries(test_save_png lodepng Eigen3::Eigen nlohmann::json)
