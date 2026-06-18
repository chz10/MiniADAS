#include "parser/GTParser.hpp"

#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace mini_adas::parser {
namespace {

std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }

    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::vector<std::string> splitCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, ',')) {
        fields.push_back(trim(field));
    }

    return fields;
}

bool isHeaderLine(const std::string& line) {
    return line.find("frame_id") != std::string::npos;
}

}  // namespace

ParseResult GTParser::parseFile(const std::string& file_path) const {
    std::ifstream input(file_path);
    if (!input.is_open()) {
        ParseResult result;
        result.success = false;
        result.message = "Failed to open GT file: " + file_path;
        return result;
    }

    std::map<int, core::FrameData> frame_map;
    std::string line;
    std::size_t line_count = 0;
    std::size_t skipped_lines = 0;
    std::size_t parsed_objects = 0;

    while (std::getline(input, line)) {
        ++line_count;
        const std::string trimmed_line = trim(line);
        if (trimmed_line.empty() || isHeaderLine(trimmed_line)) {
            continue;
        }

        core::ObjectInfo object;
        if (!parseDataLine(trimmed_line, object)) {
            ++skipped_lines;
            continue;
        }

        auto& frame = frame_map[object.frame_id];
        frame.frame_id = object.frame_id;
        frame.objects.push_back(object);
        ++parsed_objects;
    }

    if (line_count == 0 || parsed_objects == 0) {
        ParseResult result;
        result.success = false;
        result.message = "No valid GT objects parsed from file: " + file_path;
        result.parsed_objects = parsed_objects;
        result.skipped_lines = skipped_lines;
        return result;
    }

    std::vector<core::FrameData> frames;
    frames.reserve(frame_map.size());
    std::transform(
        frame_map.begin(),
        frame_map.end(),
        std::back_inserter(frames),
        [](const auto& item) { return item.second; }
    );

    ParseResult result;
    result.success = true;
    result.message = "Parsed GT file successfully: " + file_path;
    result.parsed_objects = parsed_objects;
    result.skipped_lines = skipped_lines;
    result.frames = frames;
    return result;
}

bool GTParser::parseDataLine(const std::string& line, core::ObjectInfo& object) {
    const auto fields = splitCsvLine(line);
    if (fields.size() != 8) {
        return false;
    }

    try {
        object.frame_id = std::stoi(fields[0]);
        object.object_id = std::stoi(fields[1]);
        object.category = fields[2];
        object.bbox.x1 = std::stod(fields[3]);
        object.bbox.y1 = std::stod(fields[4]);
        object.bbox.x2 = std::stod(fields[5]);
        object.bbox.y2 = std::stod(fields[6]);
        object.distance = std::stod(fields[7]);
        object.confidence = 1.0;
    } catch (...) {
        return false;
    }

    return object.frame_id >= 0
        && object.object_id >= 0
        && !object.category.empty()
        && object.bbox.isValid();
}

}  // namespace mini_adas::parser
