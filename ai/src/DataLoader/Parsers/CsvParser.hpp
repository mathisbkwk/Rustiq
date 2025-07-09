/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include "../Factory/ParserFactory.hpp"

namespace rustiq {
    class CSVParser : public IParser {
        public:
            struct CSVOptions {
                std::vector<char> separators = {',', ';'};
                bool has_header = true;
            };

                std::vector<ChunkObject> parse(const std::string& filepath) override;
        private:
            CSVOptions _options;
    };
}



#endif //CSVPARSER_HPP
