#pragma once

#include <optional>
#include <string>

namespace mini_adas::core {

enum class MatchStatus {
    TruePositive,
    FalsePositive,
    FalseNegative,
    ClassError
};

struct MatchResult {
    int frame_id{0};
    std::optional<int> gt_id;
    std::optional<int> det_id;
    std::string gt_category;
    std::string det_category;
    double iou{0.0};
    double confidence{0.0};
    double distance{0.0};
    MatchStatus status{MatchStatus::FalseNegative};
};

}  // namespace mini_adas::core
