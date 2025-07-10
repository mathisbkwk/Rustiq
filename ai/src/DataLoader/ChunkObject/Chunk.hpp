
#include <string>

namespace rustiq {
    class ChunkObject {
        public:
            ChunkObject() = default;
            ChunkObject(const std::string &type, const std::string &value, const std::size_t &lenght, const std::size_t &index);
            ~ChunkObject() = default;
            
            std::string to_string() const;
        private:
            std::string _type;
            std::string _value;
            std::size_t _lenght;
            std::size_t _index;
    };
}