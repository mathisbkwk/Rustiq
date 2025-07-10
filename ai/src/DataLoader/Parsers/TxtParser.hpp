#ifndef TXTPARSER_HPP
#define TXTPARSER_HPP

#include "../Factory/ParserFactory.hpp"

namespace rustiq {
    class TxtParser : public IParser {
    public:
        std::vector<ChunkObject> parse(const std::string& filePath) override;
    };
}

#endif // TXTPARSER_HPP
