#include <string>
#include <vector>

namespace rustiq {
    class IParser {
        public:
            virtual ~IParser() = default;
            virtual std::vector<std::string> parse(const std::string& filepath) = 0;
    };
}