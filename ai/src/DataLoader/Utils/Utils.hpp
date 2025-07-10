/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "rustiq.hpp"

namespace rustiq {
    class ParserUtils {
        public:
            static FileExtension detectExtension(const std::string& path);
    };
}



#endif //UTILS_HPP
