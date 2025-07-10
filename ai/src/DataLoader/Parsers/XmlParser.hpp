#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "../Factory/ParserFactory.hpp"

namespace rustiq {
    class XmlParser : public IParser {
    public:
        std::vector<ChunkObject> parse(const std::string& filePath) override;
    };
}

#endif // XMLPARSER_HPP
