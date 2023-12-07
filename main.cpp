// std
#include <cstdlib>
#include <iostream>
#include <memory>

// User defined
#include "src/includes/Error.hpp"
#include "src/includes/Run.hpp"

int main(int argc, const char *argv[]) {
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