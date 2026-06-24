#pragma once

#include <vector>

#include "core/FrameData.hpp"
#include "core/MatchResult.hpp"

namespace mini_adas::matcher {

class ObjectMatcher {
public:
    [[nodiscard]] std::vector<core::MatchResult> matchFrame(
        const core::FrameData& gt_frame,
        const core::FrameData& detection_frame,
        double iou_threshold = 0.5
    ) const;
};

}  // namespace mini_adas::matcher
