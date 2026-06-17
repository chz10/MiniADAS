#include <iostream>

#include "core/BBox.hpp"
#include "core/FrameData.hpp"
#include "core/MatchResult.hpp"
#include "core/ObjectInfo.hpp"

int main() {
    mini_adas::core::BBox bbox{100.0, 120.0, 180.0, 240.0};
    mini_adas::core::ObjectInfo object{
        1, 101, "car", 1.0, 35.6, bbox
    };
    mini_adas::core::FrameData frame{1, {object}};
    mini_adas::core::MatchResult result;
    result.frame_id = frame.frame_id;
    result.gt_id = object.object_id;
    result.gt_category = object.category;

    std::cout << "MiniADAS-CPP v0.2: core data structures ready. "
              << "frame_id=" << frame.frame_id
              << ", objects=" << frame.size()
              << ", bbox_area=" << bbox.area()
              << std::endl;
    return 0;
}
