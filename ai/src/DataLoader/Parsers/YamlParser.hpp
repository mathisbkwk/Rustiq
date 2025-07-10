#ifndef YMLPARSER_HPP
#define YMLPARSER_HPP

#include "../Factory/ParserFactory.hpp"

namespace rustiq {
    class YmlParser : public IParser {
    public:
        std::vector<ChunkObject> parse(const std::string& filePath) override;
    };
}

#endif // YMLPARSER_HPP
