#include "bit.hpp"
#include "option.hpp"
#include "db.hpp"

#include <iostream>
#include <string>

using string_t = std::string;

auto add_file(const string_t& filename) {
  
};

int main(int argc, char* argv[]) {
  using namespace opt;
  using namespace std;
 
  auto opts = make_list(); 

  auto do_non_opt = [](const opt::string_t&) { return 0; };
  auto do_default = []() { return 0; };

  return parse(opts, do_non_opt, do_default)(argc, argv);
}

