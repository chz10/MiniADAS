#pragma once

#include <algorithm>

namespace mini_adas::core {

struct BBox {
    double x1{0.0};
    double y1{0.0};
    double x2{0.0};
    double y2{0.0};

    [[nodiscard]] double width() const {
        return x2 - x1;
    }

    [[nodiscard]] double height() const {
        return y2 - y1;
    }

    [[nodiscard]] double area() const {
        return isValid() ? width() * height() : 0.0;
    }

    [[nodiscard]] bool isValid() const {
        return x2 > x1 && y2 > y1;
    }

    [[nodiscard]] double intersectionArea(const BBox& other) const {
        if (!isValid() || !other.isValid()) {
            return 0.0;
        }

        const double inter_x1 = std::max(x1, other.x1);
        const double inter_y1 = std::max(y1, other.y1);
        const double inter_x2 = std::min(x2, other.x2);
        const double inter_y2 = std::min(y2, other.y2);

        if (inter_x2 <= inter_x1 || inter_y2 <= inter_y1) {
            return 0.0;
        }

        return (inter_x2 - inter_x1) * (inter_y2 - inter_y1);
    }

    [[nodiscard]] double unionArea(const BBox& other) const {
        const double union_area = area() + other.area() - intersectionArea(other);
        return union_area > 0.0 ? union_area : 0.0;
    }

    [[nodiscard]] double iou(const BBox& other) const {
        const double union_area = unionArea(other);
        if (union_area <= 0.0) {
            return 0.0;
        }

        return intersectionArea(other) / union_area;
    }
};

}  // namespace mini_adas::core
