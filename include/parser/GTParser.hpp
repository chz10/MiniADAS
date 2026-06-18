#pragma once

#include <string>
#include <vector>

#include "core/FrameData.hpp"

namespace mini_adas::parser {

struct ParseResult {
    bool success{false};
    std::string message;
    std::size_t parsed_objects{0};
    std::size_t skipped_lines{0};
    std::vector<core::FrameData> frames;
};

class GTParser {
public:
    [[nodiscard]] ParseResult parseFile(const std::string& file_path) const;

private:
    [[nodiscard]] static bool parseDataLine(
        const std::string& line,
        core::ObjectInfo& object
    );
};

}  // namespace mini_adas::parser
