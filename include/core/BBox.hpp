#pragma once

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
};

}  // namespace mini_adas::core
