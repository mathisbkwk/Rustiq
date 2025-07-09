/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#include "ParserFactory.hpp"
#include "DataLoader/Parsers/CsvParser.hpp"

rustiq::ParserFactory::ParserFactory()
{
    _parsers = {
        {rustiq::FileExtension::CSV, [](){ return std::make_shared<CSVParser>(); }},
    };
}

std::shared_ptr<rustiq::IParser> rustiq::ParserFactory::createParserFromExtension(rustiq::FileExtension ext)
{
    auto it = this->_parsers.find(ext);
    
    if (it == this->_parsers.end())
        return nullptr;
    return it->second();
}

std::shared_ptr<rustiq::IParser> rustiq::ParserFactory::createParserFromFile(const std::string &filePath)
{
    rustiq::FileExtension ext = ParserUtils::detectExtension(filePath);
    
    if (ext == FileExtension::UNKNOWN)
        return nullptr;
    return this->createParserFromExtension(ext);
}