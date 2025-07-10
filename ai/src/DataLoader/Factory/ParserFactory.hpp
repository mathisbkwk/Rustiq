/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef PARSERFACTORY_HPP
#define PARSERFACTORY_HPP
#include <memory>
#include <map>
#include "Parser.hpp"
#include "../Utils/Utils.hpp"
#include <functional>

namespace rustiq {
    class ParserFactory {
        public:
            ParserFactory();
            std::shared_ptr<IParser> createParserFromExtension(FileExtension ext);
            std::shared_ptr<IParser> createParserFromFile(const std::string& filePath);
        private:
            std::map<FileExtension, std::function<std::shared_ptr<IParser>()>> _parsers;
    };
}



#endif //PARSERFACTORY_HPP
