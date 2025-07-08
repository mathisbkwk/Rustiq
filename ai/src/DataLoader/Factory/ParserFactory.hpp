/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef PARSERFACTORY_HPP
#define PARSERFACTORY_HPP
#include <memory>
#include "Parser.hpp"
#include "../DataLoader.hpp"

namespace rustiq {
    class ParserFactory {
        std::unique_ptr<IParser> createParserFromExtension(FileExtension ext);
        std::unique_ptr<IParser> createParserFromFile(const std::string& filePath);
    };
}



#endif //PARSERFACTORY_HPP
