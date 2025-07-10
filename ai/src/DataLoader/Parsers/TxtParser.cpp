#include "TxtParser.hpp"
#include <fstream>
#include <stdexcept>

namespace rustiq {

    std::vector<ChunkObject> TxtParser::parse(const std::string& filePath) {
        std::vector<ChunkObject> chunks;
        if (filePath.empty())
            return {};

        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        std::string line;
        std::size_t index = 0;

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            chunks.emplace_back("txt_line", line, line.length(), index++);
        }

        return chunks;
    }

}
