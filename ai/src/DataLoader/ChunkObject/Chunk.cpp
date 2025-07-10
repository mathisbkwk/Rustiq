

#include "Chunk.hpp"
#include <utility>

rustiq::ChunkObject::ChunkObject(const std::string &type, const std::string &value, const std::size_t &lenght, const std::size_t &index):
    _type(std::move(type)), _value(std::move(value)), _lenght(lenght), _index(index) {}

std::string rustiq::ChunkObject::to_string() const {
    return "[Chunk #" + std::to_string(_index) + "]\n" + _value; 
}