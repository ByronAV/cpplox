#include "includes/Run.hpp"
#include "includes/Error.hpp"
#include "includes/Token.hpp"
#include "includes/Scanner.hpp"

void Run::Execute(const std::string& source) {
    auto scanner = std::make_unique<Scanner>(source);
    auto& tokens = scanner->ScanTokens();

    for (auto &token: tokens) {
        std::cout << token << std::endl;
    }
}

void Run::ExecutePrompt() {
    std::string line;
    
    std::cout << "> ";
    while(std::getline(std::cin, line)) {
        std::cout << "> ";
        if (line == "")
            { break; }
        Execute(line);
        Error::had_error = false;
    }
}

void Run::ExecuteFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening file");
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    Execute(content);
    if (Error::had_error) { throw std::runtime_error("Error while parsing file"); }
}