/*
** EPITECH PROJECT, 2025
** Rustiq
** File description:
** 07
*/

#include "DataLoader.hpp"
#include <iostream>

rustiq::DataLoader::DataLoader(std::string fileName)
{
    ParserFactory factory;
    auto parser = factory.createParserFromFile(fileName);
    
    if (!parser)
        throw DataLoaderError("Error: Parser not initialized properly.");
    _chunks = parser->parse(fileName);
}

rustiq::DataLoader::~DataLoader()
{
    if (_chunks.empty())
        return;
    _chunks.clear();
}

void rustiq::DataLoader::printChunks()
{
    if (_chunks.empty())
        throw DataLoaderError("Chunks Empty");
    for (auto it : _chunks) {
        std::cout << it.to_string() << std::endl;
    }
}

