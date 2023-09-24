// std
#include <cstdlib>
#include <iostream>

// User defined
#include "src/includes/Run.hpp"
#include "src/includes/Error.hpp"

int main(int argc, const char* argv[]) {
    try {
        auto runner = std::make_unique<Run>();
        if (argc > 2) {
            throw std::invalid_argument("Usage: cpplox [script]");
        } else if (argc == 2) {
            runner->ExecuteFile(argv[0]);
        } else {
            runner->ExecutePrompt();
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}