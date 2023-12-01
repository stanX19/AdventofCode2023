#include <fstream>
#include <string>
#include <iostream>

int main() {
  std::ifstream file("input.txt");
  std::string line;

  while (std::getline(file, line)) {
    std::cout << "|" << line << "| " << file.eof() << '\n';
  }

  return 0;
}