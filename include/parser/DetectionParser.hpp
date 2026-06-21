#pragma once

#include <string>

#include "parser/GTParser.hpp"

namespace mini_adas::parser {

class DetectionParser {
public:
    [[nodiscard]] ParseResult parseFile(
        const std::string& file_path,
        double confidence_threshold = 0.3
    ) const;

private:
    [[nodiscard]] static bool parseDataLine(
        const std::string& line,
        double confidence_threshold,
        core::ObjectInfo& object
    );
};

}  // namespace mini_adas::parser
