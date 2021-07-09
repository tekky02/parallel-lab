#include <chrono>
#include <iostream>
#include <string>

namespace utils {

struct Timer {
    explicit Timer(const std::string& str) : info{str} { start = std::chrono::steady_clock::now(); }
    ~Timer() {
        auto end = std::chrono::steady_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "[Total time with " << info << "]: " << duration.count() << "us" << std::endl;
    }

private:
    std::string info;
    std::chrono::time_point<std::chrono::steady_clock> start;
};

}  // namespace utils