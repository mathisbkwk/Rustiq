/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP
#include "Parser.hpp"


namespace rustiq {
    class CSVParser : public IParser {
        public:
            struct CSVOptions {
                std::vector<char> separators = {',', ';'};
                bool has_header = false;
            };
            bool hasHeader(const std::vector<std::string>& chunks) const;
            std::vector<std::string> parse(const std::string& filepath) override;
    };
}



#endif //CSVPARSER_HPP
