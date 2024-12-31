#ifndef _READER_H_
#define _READER_H_

#include <string>
#include <vector>

namespace reader {

using CharMatrix = std::vector<std::vector<char>>;

enum InputType : int { FULL, TEST };

std::vector<std::string> inputsAsString(int day, InputType itype);

CharMatrix inputsAsCharMatrix(int day, InputType itype);
} // namespace reader

#endif // _READER_H_