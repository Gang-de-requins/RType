#ifndef CUSTOM_EXCEPTIONS_HPP
#define CUSTOM_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace ecs {
    class DuplicateComponentTypeException : public std::exception {
        std::string _message;

        public:
            DuplicateComponentTypeException(const std::string &message) :
                _message(message)
            {
            }

            const char *what() const noexcept override
            {
                return this->_message.c_str();
            }
    };
}

#endif /* CUSTOM_EXCEPTIONS_HPP */
