#include "cmd-init.hpp"
#include <options/options.hpp>
#include <iostream>

void get_opts(const std::string& opt) {
  std::cout << opt << "\n";
};


int main(int argc, char* argv[]) try
{ 
  {  
    using namespace option;

    auto opts =  
      table(
        entry(
          names("help", "-h", "--help", "&HELP"),
          "Display help.",
          arg_none, 
          do_nothing),
        entry(
          names("init"), "Initialize the build database.",
          arg_none, 
          [&](const std::string&){}, 
          init_opt_table())
      );

    parse(argc, argv, &opts);
  }
  return 0;
}
catch(const std::runtime_error& e) {
  using namespace std;
  cerr << e.what() << endl;
  return -1;
}


