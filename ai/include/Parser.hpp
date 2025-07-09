#include "DataLoader/ChunkObject/Chunk.hpp"
#include <string>
#include <vector>

namespace rustiq {
    class IParser {
        public:
            virtual ~IParser() = default;
            virtual std::vector<rustiq::ChunkObject> parse(const std::string& filepath) = 0;
    };
}