#include <cassert>
#include <cmath>
#include <iostream>

#include "core/BBox.hpp"
#include "core/FrameData.hpp"
#include "core/MatchResult.hpp"
#include "core/ObjectInfo.hpp"

namespace {

bool nearlyEqual(double lhs, double rhs, double eps = 1e-9) {
    return std::fabs(lhs - rhs) <= eps;
}

void verifyBBoxGeometry() {
    const mini_adas::core::BBox box{0.0, 0.0, 100.0, 100.0};
    const mini_adas::core::BBox same_box{0.0, 0.0, 100.0, 100.0};
    const mini_adas::core::BBox overlap_box{50.0, 50.0, 150.0, 150.0};
    const mini_adas::core::BBox disjoint_box{120.0, 120.0, 160.0, 160.0};
    const mini_adas::core::BBox invalid_box{10.0, 10.0, 5.0, 20.0};

    assert(nearlyEqual(box.width(), 100.0));
    assert(nearlyEqual(box.height(), 100.0));
    assert(nearlyEqual(box.area(), 10000.0));
    assert(box.isValid());
    assert(!invalid_box.isValid());
    assert(nearlyEqual(invalid_box.area(), 0.0));
    assert(nearlyEqual(box.iou(same_box), 1.0));
    assert(nearlyEqual(box.iou(disjoint_box), 0.0));
    assert(nearlyEqual(box.iou(invalid_box), 0.0));
    assert(nearlyEqual(box.intersectionArea(overlap_box), 2500.0));
    assert(nearlyEqual(box.unionArea(overlap_box), 17500.0));
    assert(nearlyEqual(box.iou(overlap_box), 2500.0 / 17500.0));
}

}  // namespace

int main() {
    verifyBBoxGeometry();

    mini_adas::core::BBox bbox{100.0, 120.0, 180.0, 240.0};
    mini_adas::core::BBox detection_bbox{102.0, 118.0, 179.0, 242.0};
    mini_adas::core::ObjectInfo object{
        1, 101, "car", 1.0, 35.6, bbox
    };
    mini_adas::core::FrameData frame{1, {object}};
    mini_adas::core::MatchResult result;
    result.frame_id = frame.frame_id;
    result.gt_id = object.object_id;
    result.gt_category = object.category;

    std::cout << "MiniADAS-CPP v0.3: BBox geometry and IoU ready. "
              << "frame_id=" << frame.frame_id
              << ", objects=" << frame.size()
              << ", bbox_area=" << bbox.area()
              << ", sample_iou=" << bbox.iou(detection_bbox)
              << std::endl;
    return 0;
}
