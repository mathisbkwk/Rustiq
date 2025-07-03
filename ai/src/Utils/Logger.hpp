/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <cstddef>
#include <string>
#include <iostream>

namespace rustiq {
    class Logger {
    public:
        explicit Logger(const bool &isDebugActivate);
        ~Logger() = delete;

        template <typename T>
        void sendDebugMessage(const T& dataToSend, std::size_t lenght, const std::string& label)
        {
            if (!this->_isDebuggingMode)
                return;
            std::cout << "[DEBUG] " << label << "(" << lenght << "bytes): " << dataToSend << std::endl;
        }
    private:
        bool _isDebuggingMode;
    };
}



#endif //LOGGER_HPP
