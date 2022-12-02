#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

uint64_t max_group = 0;
uint64_t cur_group = 0;
std::string line_buffer;

void update(uint64_t value) {
  if (value > (std::numeric_limits<uint64_t>::max() - cur_group)) {
    cur_group = std::numeric_limits<uint64_t>::max();
    std::cerr << "Warning: Group hit limit." << std::endl;
  } else {
    cur_group += value;
  }
}

bool is_empty_line(const std::string& line) {
  for (char ch : line) {
    if (!std::isspace(ch)) {
      return false;
    }
  }
  return true;
}

void finish_group() {
  if (cur_group > max_group) {
    max_group = cur_group;
  }
  cur_group = 0;
}

void update(const std::string& line) {
  if (is_empty_line(line)) {
    finish_group();
  } else {
    update(std::stoll(line));
  }
}



int main(void) {

  while (true) {
    
    // Clear previous line.
    line_buffer.clear();

    // Read next line.
    std::getline(std::cin, line_buffer);

    if (std::cin.bad())
    {
      std::cerr << "Error: Bad input." << std::endl;
      return 1;
    } else {

      try {
        update(line_buffer);
      } catch (const std::out_of_range& e) {
        std::cerr << "Error: Out of range: " << e.what() << std::endl;
        return 1;
      } catch (const std::invalid_argument &e) {
        std::cerr << "Error: Invalid argument: " << e.what() << std::endl;
        return 1;
      }

      if (std::cin.eof()) {
        break;
      }

    }
  }

  std::cout << "Answer: " << max_group << " calories" << std::endl;

}