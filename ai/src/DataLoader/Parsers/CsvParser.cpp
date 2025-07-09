/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#include "CsvParser.hpp"
#include <filesystem>

std::vector<rustiq::ChunkObject> rustiq::CSVParser::parse(const std::string& filepath)
{
    std::filesystem::path path(filepath);
    std::istringstream stream(filepath);
    std::string line;
    std::vector<ChunkObject> chunks;

    while (std::getline(stream, line)) {
        chunks.push_back({line, line, 1, 1});
    }
    return chunks;
}
