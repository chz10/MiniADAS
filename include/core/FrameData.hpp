#pragma once

#include <vector>

#include "core/ObjectInfo.hpp"

namespace mini_adas::core {

struct FrameData {
    int frame_id{0};
    std::vector<ObjectInfo> objects;

    [[nodiscard]] bool empty() const {
        return objects.empty();
    }

    [[nodiscard]] std::size_t size() const {
        return objects.size();
    }
};

}  // namespace mini_adas::core
