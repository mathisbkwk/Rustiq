#include "CsvParser.hpp"
#include <fstream>
#include <stdexcept>

namespace rustiq {

    CSVParser::CSVOptions default_options;

    std::vector<ChunkObject> CSVParser::parse(const std::string& filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filepath);
        }

        std::vector<ChunkObject> chunks;
        std::string line;
        std::size_t index = 0;
        bool skip_header = _options.has_header;

        while (std::getline(file, line)) {
            if (skip_header) {
                skip_header = false;
                continue;
            }

            chunks.emplace_back("csv_row", line, line.length(), index++);
        }

        return chunks;
    }
}
