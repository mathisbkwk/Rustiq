#include "YamlParser.hpp"
#include <fstream>
#include <regex>
#include <stdexcept>

namespace rustiq {

    std::vector<ChunkObject> YmlParser::parse(const std::string& filePath) {
        std::vector<ChunkObject> chunks;
        if (filePath.empty())
            return {};

        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        std::string line;
        std::size_t index = 0;
        std::regex kv_regex(R"(^\s*([^\s:#]+)\s*:\s*(.+)?$)");

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            std::smatch match;
            if (std::regex_match(line, match, kv_regex)) {
                std::string key = match[1];
                std::string value = match[2];
                if (value.empty()) value = "\"\"";
                else if (value.front() != '"' && value != "true" && value != "false" && !std::isdigit(value.front()))
                    value = "\"" + value + "\"";

                std::string chunk_value = "{\"" + key + "\": " + value + "}";
                chunks.emplace_back("yml_pair", chunk_value, chunk_value.length(), index++);
            }
        }

        return chunks;
    }

}
