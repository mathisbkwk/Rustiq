
#include <exception>
#include <iostream>
#include <string>

namespace rustiq {
    class Core {
        public:
            class CoreError : public std::exception {
                public:
                    CoreError(const std::string &msg): _message(msg) {}
                    
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };
            int run(int ac, char **av);
            template<typename Func>
            void safeLookup(Func functionToLookUp) {
                try {
                    functionToLookUp();
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Unexpected error caught." << std::endl;
                }
            }
            bool isRunning = false;
    };
}