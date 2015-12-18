#include "option.hpp"
#include <iostream>

//#include "bit-init.hpp"
#include "opt_table.hpp"
#include <boost/lexical_cast.hpp>

void get_opts(const std::string& opt) {
  std::cout << opt << "\n";
};

auto do_add = [] (const std::string& s) {
  std::cout << "Haha! " << s << "\n";
};

int main(int argc, char* argv[]) try
{
  auto opts = opt_table::create(
      opt_table::option(opt_table::names("-a", "--add", "-x"), "add", opt_table::arg_required, do_add
    ));

  opt_table::dispatch(argc, argv, opts);

  return 0;
}
catch(const std::runtime_error& e) {
  using namespace std;
  cerr << e.what() << endl;
  return -1;
}


