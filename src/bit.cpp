#include "option.hpp"
#include <iostream>

#include "bit-init.hpp"
#include "opt_table.hpp"

void get_opts(const std::string& opt) {
  std::cout << opt << "\n";
};

auto do_add = [](const std::string&) {
};

int main(int argc, char* argv[]) try
{
    
  return 0;
}
catch(const std::runtime_error& e) {
  using namespace std;
  cerr << e.what() << endl;
  return -1;
}


