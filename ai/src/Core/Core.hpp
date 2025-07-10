
#include <exception>
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
                    throw rustiq::Core::CoreError(std::string("Error: ") + e.what());
                } catch (...) {
                    throw rustiq::Core::CoreError("Error: Unknown exception type caught");
                }
            }
            bool isRunning = false;
    };
}