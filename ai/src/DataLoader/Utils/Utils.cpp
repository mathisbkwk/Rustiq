/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#include "Utils.hpp"
#include <algorithm>
#include <filesystem>
#include <unordered_map>

rustiq::FileExtension rustiq::ParserUtils::detectExtension(const std::string& path)
{
    static std::unordered_map<std::string, FileExtension> extMap = {
        {".json",  JSON},
        {".jsonl", JSONL},
        {".yaml",  YAML},
        {".yml",   YAML},
        {".toml",  TOML},
        {".xml",   XML},
        {".csv",   CSV},
        {".txt",   TXT},
        {".xlsx",  XLSX},
    };

    std::string ext = std::filesystem::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (auto it = extMap.find(ext); it != extMap.end()) {
        return it->second;
    }

    return rustiq::FileExtension::UNKNOWN;
}
