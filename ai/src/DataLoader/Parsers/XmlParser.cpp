#include "XmlParser.hpp"
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

namespace rustiq {

    std::vector<ChunkObject> XmlParser::parse(const std::string& filePath) {
        std::vector<ChunkObject> chunks;
        if (filePath.empty())
            return {};

        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        std::ostringstream ss;
        ss << file.rdbuf();
        std::string content = ss.str();

        std::regex tag_regex(R"(<([^!?][^>/\s]*)([^>]*)>(.*?)<\/\1>)");
        std::smatch match;
        std::string::const_iterator searchStart(content.cbegin());
        std::size_t index = 0;

        while (std::regex_search(searchStart, content.cend(), match, tag_regex)) {
            std::string tag = match[1];
            std::string inner = match[3];
            std::string chunk_value = "<" + tag + ">" + inner + "</" + tag + ">";
            chunks.emplace_back("xml_node", chunk_value, chunk_value.length(), index++);
            searchStart = match.suffix().first;
        }

        return chunks;
    }

}
