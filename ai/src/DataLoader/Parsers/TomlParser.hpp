#ifndef TOMLPARSER_HPP
#define TOMLPARSER_HPP

#include "../Factory/ParserFactory.hpp"

namespace rustiq {
    class TomlParser : public IParser {
    public:
        std::vector<ChunkObject> parse(const std::string& filePath) override;
    };
}

#endif // TOMLPARSER_HPP
