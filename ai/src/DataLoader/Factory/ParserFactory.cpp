/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#include "ParserFactory.hpp"
#include "DataLoader/Parsers/CsvParser.hpp"
#include "DataLoader/Parsers/JsonLParser.hpp"
#include "DataLoader/Parsers/JsonParser.hpp"
#include "DataLoader/Parsers/TomlParser.hpp"
#include "DataLoader/Parsers/TxtParser.hpp"
#include "DataLoader/Parsers/XmlParser.hpp"
#include "DataLoader/Parsers/YamlParser.hpp"
#include "DataLoader/Utils/Utils.hpp"

rustiq::ParserFactory::ParserFactory()
{
    _parsers = {
        {rustiq::FileExtension::CSV, [](){ return std::make_shared<CSVParser>(); }},
        {rustiq::FileExtension::JSONL, []() { return std::make_shared<JsonLParser>(); }},
        {rustiq::FileExtension::JSON, []() { return std::make_shared<JsonParser>(); }},
        {rustiq::FileExtension::TOML, []() { return std::make_shared<TomlParser>(); }},
        {rustiq::FileExtension::TXT, []() { return std::make_shared<TxtParser>(); }},
        {rustiq::FileExtension::XML, []() { return std::make_shared<XmlParser>(); }},
        {rustiq::FileExtension::YAML, []() { return std::make_shared<YmlParser>(); }}
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