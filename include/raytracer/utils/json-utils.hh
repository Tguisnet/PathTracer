#pragma once

#include <algorithm>
#include <string>

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

namespace raytracer
{
    using json = nlohmann::json;

    json parse_json(const char* filename);
}

static inline auto json_lisp_case(const char* c_str)
{
    auto str = std::string(c_str);
    std::replace(str.begin(), str.end(), '_', '-');

    return str;
}

#define GET_TO_OTHER(Json, Value, JsonField, CField) (Json).at(JsonField).get_to((Value).CField)
#define GET_TO(Json, Value, Field) GET_TO_OTHER(Json, Value, json_lisp_case(#Field), Field)

namespace nlohmann
{
    using namespace Eigen;

    template<typename Scalar, int Rows, int Cols>
    struct adl_serializer<Matrix<Scalar, Rows, Cols>>
    {
        using matrix_type = Matrix<Scalar, Rows, Cols>;
        static constexpr auto size = static_cast<size_t>(Rows * Cols);

        static void from_json(const json& j, matrix_type& mat)
        {
            if (j.size() != 3)
                throw std::runtime_error(
                        "Invalid matrix size (had " + std::to_string(j.size())
                        + ", but " + std::to_string(size) + " expected)");

            std::array<Scalar, size> array;
            j.get_to(array);

            mat = matrix_type(array.data());
        }
    };
}