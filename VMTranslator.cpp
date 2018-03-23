#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char *argv[])
{
  std::ifstream inFile(argv[1]);
  if (inFile) {
    std::string line;
    char x;
    while (std::getline(inFile, line)) {
      std::cout << line << std::endl;
    }
  } else {
    std::cerr << "No file name passed in" << std::endl;
  }

  return 0;
}
