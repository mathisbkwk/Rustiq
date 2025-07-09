/*
** EPITECH PROJECT, 2025
** Rustiq
** File description:
** 07
*/

#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <exception>
#include <string>
#include <vector>
#include "Factory/ParserFactory.hpp"

namespace rustiq 
{
    class DataLoader {
        public:
            class DataLoaderError : public std::exception {
                private:
                    std::string _message;
                public:
                    DataLoaderError(const std::string& msg): _message(msg) {};
                    const char *what() const noexcept override { return _message.c_str(); }
            };
            explicit DataLoader(std::string fileName);
            ~DataLoader();
            
            void printChunks();
            std::vector<ChunkObject> _chunks;
    };
}



#endif //DATALOADER_HPP
