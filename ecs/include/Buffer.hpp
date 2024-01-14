#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <fstream>
#include <string_view>
#include <vector>
#include <array>
#include <cctype>
#include <algorithm>
#if defined(_WIN32)
#define NOGDI
#define NOUSER
#endif

// #include <boost/asio.hpp>
#include <asio.hpp>

#if defined(_WIN32)
#undef near
#undef far
#endif
#include "rapidjson/document.h"
#include "Macros.hpp"
#include "Network.hpp"
#include "Scene.hpp"
#include "components/Components.hpp"

namespace ecs {
    class Buffer {
        public:
            Buffer();
            ~Buffer();
            void writeMessageType(MessageType messageType);
            MessageType readMessageType();
            void writeString(const std::string& str);
            std::string readString();
            void writeInt(int value);
            int readInt();
            void writeSize(size_t size);
            size_t readSize();
            void setEndpoint(asio::ip::udp::endpoint endpoint) {
                _fromEndpoint = endpoint;
            }
            asio::ip::udp::endpoint getEndpoint()
            {
                return _fromEndpoint;
            }
            std::vector<char>& getData() {
                return data_;
            }
            void setData(const std::vector<char>& newData) {
                data_ = newData;
            }

        private:
            std::vector<char> data_;
            size_t currentIndex_;
            asio::ip::udp::endpoint _fromEndpoint;
    };
};

#endif /* BUFFER_HPP */
