#pragma once

#include <fstream>
#include <iostream>
#include <string>

class Run {
public:
  Run() = default;
  ~Run() = default;

  // No copy
  Run(const Run &) = delete;
  Run &operator=(const Run &) = delete;

  // No move
  Run(Run &&) = delete;
  Run &operator=(Run &&) = delete;

  static void Execute(const std::string &source);
  static void ExecutePrompt();
  static void ExecuteFile(const std::string &path);
};