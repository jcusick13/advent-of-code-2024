#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "reader.h"
#include "readerConfig.h"

namespace reader {

std::vector<std::string> inputsAsString(int day, InputType itype) {

  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day" << std::setw(2) << std::setfill('0')
        << day << (itype == TEST ? "-test" : "") << ".txt";

  std::ifstream input_file(fname.str());
  if (!input_file) {
    throw std::runtime_error("Can't open " + fname.str());
  }

  std::vector<std::string> inputs;
  std::string str;
  while (input_file >> str) {
    inputs.push_back(str);
  }

  return inputs;
}
} // namespace reader
