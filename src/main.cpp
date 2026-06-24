#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include "core/BBox.hpp"
#include "core/FrameData.hpp"
#include "core/MatchResult.hpp"
#include "core/ObjectInfo.hpp"
#include "matcher/ObjectMatcher.hpp"
#include "parser/DetectionParser.hpp"
#include "parser/GTParser.hpp"

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

std::size_t countStatus(
    const std::vector<mini_adas::core::MatchResult>& results,
    mini_adas::core::MatchStatus status
) {
    return static_cast<std::size_t>(std::count_if(
        results.begin(),
        results.end(),
        [status](const mini_adas::core::MatchResult& result) {
            return result.status == status;
        }
    ));
}

void verifyObjectMatching() {
    using mini_adas::core::BBox;
    using mini_adas::core::FrameData;
    using mini_adas::core::MatchStatus;

    const FrameData gt_frame{
        10,
        {
            {10, 101, "car", 1.0, 20.0, BBox{0.0, 0.0, 100.0, 100.0}},
            {10, 102, "person", 1.0, 15.0, BBox{200.0, 200.0, 260.0, 280.0}},
            {10, 103, "bicycle", 1.0, 10.0, BBox{400.0, 400.0, 450.0, 450.0}}
        }
    };
    const FrameData detection_frame{
        10,
        {
            {10, 201, "car", 0.95, 20.5, BBox{10.0, 10.0, 100.0, 100.0}},
            {10, 202, "car", 0.88, 21.0, BBox{15.0, 15.0, 100.0, 100.0}},
            {10, 203, "truck", 0.90, 15.5, BBox{202.0, 202.0, 258.0, 278.0}},
            {10, 204, "car", 0.70, 50.0, BBox{600.0, 600.0, 650.0, 650.0}}
        }
    };

    const mini_adas::matcher::ObjectMatcher matcher;
    const auto results = matcher.matchFrame(gt_frame, detection_frame, 0.5);

    assert(results.size() == 5);
    assert(countStatus(results, MatchStatus::TruePositive) == 1);
    assert(countStatus(results, MatchStatus::ClassError) == 1);
    assert(countStatus(results, MatchStatus::FalseNegative) == 1);
    assert(countStatus(results, MatchStatus::FalsePositive) == 2);
}

}  // namespace

int main() {
    verifyBBoxGeometry();
    verifyObjectMatching();

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

    const mini_adas::parser::GTParser gt_parser;
    const auto parse_result = gt_parser.parseFile("data/gt/sample_gt.csv");
    assert(parse_result.success);
    assert(parse_result.parsed_objects == 3);
    assert(parse_result.skipped_lines == 2);
    assert(parse_result.frames.size() == 2);
    assert(parse_result.frames[0].frame_id == 1);
    assert(parse_result.frames[0].objects.size() == 2);
    assert(parse_result.frames[1].frame_id == 2);
    assert(parse_result.frames[1].objects.size() == 1);

    const mini_adas::parser::DetectionParser detection_parser;
    const auto det_result = detection_parser.parseFile("data/detection/sample_det.csv", 0.3);
    assert(det_result.success);
    assert(det_result.parsed_objects == 3);
    assert(det_result.skipped_lines == 3);
    assert(det_result.frames.size() == 2);
    assert(det_result.frames[0].frame_id == 1);
    assert(det_result.frames[0].objects.size() == 2);
    assert(det_result.frames[0].objects[0].confidence >= 0.3);
    assert(det_result.frames[1].frame_id == 2);
    assert(det_result.frames[1].objects.size() == 1);

    std::cout << "MiniADAS-CPP v0.6: Object matcher ready. "
              << "frame_id=" << frame.frame_id
              << ", objects=" << frame.size()
              << ", bbox_area=" << bbox.area()
              << ", sample_iou=" << bbox.iou(detection_bbox)
              << ", gt_frames=" << parse_result.frames.size()
              << ", gt_objects=" << parse_result.parsed_objects
              << ", skipped_lines=" << parse_result.skipped_lines
              << ", det_frames=" << det_result.frames.size()
              << ", det_objects=" << det_result.parsed_objects
              << ", det_skipped_lines=" << det_result.skipped_lines
              << std::endl;
    return 0;
}
