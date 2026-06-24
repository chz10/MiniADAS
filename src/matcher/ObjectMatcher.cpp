#include "matcher/ObjectMatcher.hpp"

#include <algorithm>
#include <cstddef>
#include <vector>

namespace mini_adas::matcher {
namespace {

struct MatchCandidate {
    std::size_t gt_index{0};
    std::size_t det_index{0};
    double iou{0.0};
};

bool isHigherPriority(const MatchCandidate& lhs, const MatchCandidate& rhs) {
    if (lhs.iou != rhs.iou) {
        return lhs.iou > rhs.iou;
    }

    if (lhs.gt_index != rhs.gt_index) {
        return lhs.gt_index < rhs.gt_index;
    }

    return lhs.det_index < rhs.det_index;
}

core::MatchResult makeMatchedResult(
    const core::ObjectInfo& gt,
    const core::ObjectInfo& detection,
    double iou,
    core::MatchStatus status
) {
    core::MatchResult result;
    result.frame_id = gt.frame_id;
    result.gt_id = gt.object_id;
    result.det_id = detection.object_id;
    result.gt_category = gt.category;
    result.det_category = detection.category;
    result.iou = iou;
    result.confidence = detection.confidence;
    result.distance = detection.distance;
    result.status = status;
    return result;
}

}  // namespace

std::vector<core::MatchResult> ObjectMatcher::matchFrame(
    const core::FrameData& gt_frame,
    const core::FrameData& detection_frame,
    double iou_threshold
) const {
    std::vector<core::MatchResult> results;
    if (gt_frame.frame_id != detection_frame.frame_id || iou_threshold < 0.0) {
        return results;
    }

    std::vector<MatchCandidate> same_category_candidates;
    std::vector<MatchCandidate> different_category_candidates;

    for (std::size_t gt_index = 0; gt_index < gt_frame.objects.size(); ++gt_index) {
        const auto& gt = gt_frame.objects[gt_index];
        for (std::size_t det_index = 0; det_index < detection_frame.objects.size(); ++det_index) {
            const auto& detection = detection_frame.objects[det_index];
            const double iou = gt.bbox.iou(detection.bbox);
            if (iou < iou_threshold) {
                continue;
            }

            MatchCandidate candidate{gt_index, det_index, iou};
            if (gt.category == detection.category) {
                same_category_candidates.push_back(candidate);
            } else {
                different_category_candidates.push_back(candidate);
            }
        }
    }

    std::sort(
        same_category_candidates.begin(),
        same_category_candidates.end(),
        isHigherPriority
    );
    std::sort(
        different_category_candidates.begin(),
        different_category_candidates.end(),
        isHigherPriority
    );

    std::vector<bool> matched_gt(gt_frame.objects.size(), false);
    std::vector<bool> matched_detection(detection_frame.objects.size(), false);

    const auto matchCandidates = [&](const std::vector<MatchCandidate>& candidates,
                                     core::MatchStatus status) {
        for (const auto& candidate : candidates) {
            if (matched_gt[candidate.gt_index] || matched_detection[candidate.det_index]) {
                continue;
            }

            const auto& gt = gt_frame.objects[candidate.gt_index];
            const auto& detection = detection_frame.objects[candidate.det_index];
            results.push_back(makeMatchedResult(gt, detection, candidate.iou, status));
            matched_gt[candidate.gt_index] = true;
            matched_detection[candidate.det_index] = true;
        }
    };

    matchCandidates(same_category_candidates, core::MatchStatus::TruePositive);
    matchCandidates(different_category_candidates, core::MatchStatus::ClassError);

    for (std::size_t gt_index = 0; gt_index < gt_frame.objects.size(); ++gt_index) {
        if (matched_gt[gt_index]) {
            continue;
        }

        const auto& gt = gt_frame.objects[gt_index];
        core::MatchResult result;
        result.frame_id = gt.frame_id;
        result.gt_id = gt.object_id;
        result.gt_category = gt.category;
        result.distance = gt.distance;
        result.status = core::MatchStatus::FalseNegative;
        results.push_back(result);
    }

    for (std::size_t det_index = 0; det_index < detection_frame.objects.size(); ++det_index) {
        if (matched_detection[det_index]) {
            continue;
        }

        const auto& detection = detection_frame.objects[det_index];
        core::MatchResult result;
        result.frame_id = detection.frame_id;
        result.det_id = detection.object_id;
        result.det_category = detection.category;
        result.confidence = detection.confidence;
        result.distance = detection.distance;
        result.status = core::MatchStatus::FalsePositive;
        results.push_back(result);
    }

    return results;
}

}  // namespace mini_adas::matcher
