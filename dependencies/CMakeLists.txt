add_library(lodepng STATIC lodepng/lodepng.cpp)
target_include_directories(lodepng PUBLIC lodepng/)

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE nlohmann-json/)
add_library(nlohmann::json ALIAS nlohmann_json)
