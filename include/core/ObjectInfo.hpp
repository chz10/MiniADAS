#pragma once

#include <string>

#include "core/BBox.hpp"

namespace mini_adas::core {

struct ObjectInfo {
    int frame_id{0};
    int object_id{-1};
    std::string category;
    double confidence{1.0};
    double distance{0.0};
    BBox bbox;
};

}  // namespace mini_adas::core
