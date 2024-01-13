#include "Buffer.hpp"

namespace ecs {
    Buffer::Buffer() {
        this->currentIndex_ = 0;
    }

    Buffer::~Buffer() {
        
    }

    void Buffer::writeMessageType(MessageType messageType) {
        char value = static_cast<char>(messageType);
        data_.push_back(value);
    }

    MessageType Buffer::readMessageType() {
        char value = this->data_[this->currentIndex_++];
        return static_cast<MessageType>(value);
    }

    void Buffer::writeString(const std::string& str) {
        size_t size = str.size();
        writeSize(size);
        data_.insert(data_.end(), str.begin(), str.end());
    }

    std::string Buffer::readString() {
        size_t size = readSize();
        std::string str(data_.begin() + currentIndex_, data_.begin() + currentIndex_ + size);
        currentIndex_ += size;
        return str;
    }

    void Buffer::writeInt(int value) {
        size_t size = sizeof(value);
        writeSize(size);
        data_.insert(data_.end(), reinterpret_cast<const char*>(&value), reinterpret_cast<const char*>(&value) + size);
    }

    int Buffer::readInt() {
        size_t size = readSize();
        int value;
        std::memcpy(&value, data_.data() + currentIndex_, size);
        currentIndex_ += size;
        return value;
    }

    void Buffer::writeSize(size_t size) {
        data_.insert(data_.end(), reinterpret_cast<const char*>(&size), reinterpret_cast<const char*>(&size) + sizeof(size_t));
    }

    size_t Buffer::readSize() {
        size_t size;
        std::memcpy(&size, data_.data() + currentIndex_, sizeof(size_t));
        currentIndex_ += sizeof(size_t);
        return size;
    }

}
