/*
** EPITECH PROJECT, 2025
** Rustiq
** File description:
** 07
*/

#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <string>

namespace rustiq 
{

    enum FileExtension {
        JSON,
        JSONL,
        YAML,
        TOML,
        XML,
        CSV,
        TSV,
        TXT,
        XLSX,
        UNKNOWN,
    };

    class DataLoader {
        public:
            explicit DataLoader(std::string fileName);
            ~DataLoader() = delete;
    };
}



#endif //DATALOADER_HPP
