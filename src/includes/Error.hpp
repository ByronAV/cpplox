#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <string>

class Error {
 public:
  Error() = default;
  ~Error() = default;
  [[gnu::always_inline]] static void Report(unsigned int line, const std::string &where,
                            const std::string &message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message
              << std::endl;
    had_error = true;
  }
  [[gnu::always_inline]] static void SendError(unsigned int line, const std::string &message) {
    Report(line, "", message);
  }
  inline static bool had_error = false;
};

#endif