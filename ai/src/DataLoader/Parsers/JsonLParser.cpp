#include "JsonLParser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <regex>

namespace rustiq {

    std::vector<ChunkObject> JsonLParser::parse(const std::string& filePath) {
        std::vector<ChunkObject> chunks;
        if (filePath.empty())
            return {};

        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        std::string line;
        std::size_t index = 0;

        std::regex pair_regex("\"([^\"]+)\"\\s*:\\s*(\"[^\"]*\"|\\d+|true|false|null)");

        while (std::getline(file, line)) {
            if (line.empty())
                continue;

            std::ostringstream formatted;
            formatted << "{";

            std::smatch match;
            std::string::const_iterator searchStart(line.cbegin());
            bool first = true;

            while (std::regex_search(searchStart, line.cend(), match, pair_regex)) {
                if (!first)
                    formatted << ", ";
                first = false;

                std::string key = match[1];
                std::string value = match[2];
                if (value.front() != '"')
                    value = "\"" + value + "\"";

                formatted << "\"" << key << "\": " << value;
                searchStart = match.suffix().first;
            }

            formatted << "}";

            std::string chunk_value = formatted.str();
            chunks.emplace_back("jsonl_row", chunk_value, chunk_value.length(), index++);
        }

        return chunks;
    }

}
