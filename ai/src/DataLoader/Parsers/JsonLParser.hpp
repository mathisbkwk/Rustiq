/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef JSONLPARSER_HPP
#define JSONLPARSER_HPP
#include "../Factory/ParserFactory.hpp"

namespace rustiq {
    class JsonLParser : public IParser {
        public:
            std::vector<ChunkObject> parse(const std::string& filepath) override;
    };
}


#endif //JSONLPARSER_HPP
