#include "JsonParser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <regex>

namespace rustiq {

    std::vector<ChunkObject> JsonParser::parse(const std::string& filePath) {
        std::vector<ChunkObject> chunks;
        if (filePath.empty())
            return {};

        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        std::ostringstream ss;
        ss << file.rdbuf();
        std::string content = ss.str();

        std::size_t i = 0;
        while (i < content.size() && content[i] != '[') ++i;
        if (i == content.size())
            return {};

        ++i;

        std::size_t index = 0;
        std::regex pair_regex("\"([^\"]+)\"\\s*:\\s*(\"[^\"]*\"|\\d+|true|false|null)");

        while (i < content.size()) {
            while (i < content.size() && std::isspace(content[i])) ++i;
            if (i >= content.size() || content[i] == ']') break;

            if (content[i] != '{') {
                ++i;
                continue;
            }
            int brace_count = 0;
            size_t start = i;
            while (i < content.size()) {
                if (content[i] == '{') brace_count++;
                else if (content[i] == '}') brace_count--;
                ++i;
                if (brace_count == 0)
                    break;
            }

            std::string object_str = content.substr(start, i - start);

            std::ostringstream formatted;
            formatted << "{";

            std::smatch match;
            std::string::const_iterator searchStart(object_str.cbegin());
            bool first = true;

            while (std::regex_search(searchStart, object_str.cend(), match, pair_regex)) {
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
            chunks.emplace_back("json_row", chunk_value, chunk_value.length(), index++);

            while (i < content.size() && (content[i] == ',' || std::isspace(content[i]))) ++i;
        }

        return chunks;
    }

}
