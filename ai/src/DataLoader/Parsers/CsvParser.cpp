#include "CsvParser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace rustiq {

    std::vector<ChunkObject> CSVParser::parse(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filepath);
        }

        std::vector<ChunkObject> chunks;
        std::string line;
        std::vector<std::string> headers;
        std::size_t index = 0;
        bool first = true;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            std::vector<std::string> values;
            char sep = _options.separators[0];

            for (char candidate : _options.separators) {
                if (line.find(candidate) != std::string::npos) {
                    sep = candidate;
                    break;
                }
            }

            while (std::getline(ss, cell, sep)) {
                values.push_back(cell);
            }

            if (first && _options.has_header) {
                headers = values;
                first = false;
                continue;
            }

            std::ostringstream formatted;
            formatted << "{";
            for (size_t i = 0; i < values.size(); ++i) {
                const std::string& key = (i < headers.size()) ? headers[i] : ("col" + std::to_string(i));
                formatted << "\"" << key << "\": \"" << values[i] << "\"";
                if (i != values.size() - 1)
                    formatted << ", ";
            }
            formatted << "}";

            std::string chunk_value = formatted.str();
            chunks.emplace_back("csv_row", chunk_value, chunk_value.length(), index++);
        }

        return chunks;
    }

}
