/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP


#include "../Factory/ParserFactory.hpp"

namespace rustiq {
    class JsonParser : public IParser {
        public:
            std::vector<ChunkObject> parse(const std::string& filepath) override;
    };
}



#endif //JSONPARSER_HPP
