#include "cmd-init.hpp"
#include "cmd-set.hpp"
#include "cmd-unset.hpp"
#include "cmd-build.hpp"

#include <options/options.hpp>
#include <iostream>

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
          do_nothing, 
          cmd_init_opt_table()),
        entry(
          names("build"), "Build the project.",
          arg_none, 
          do_nothing, 
          cmd_build_opt_table()),
        entry(
          names("set"), "Set a build variable.",
          arg_none, 
          do_nothing, 
          cmd_set_opt_table()),
        entry(
          names("unset"), "Remove (erase) a build variable.",
          arg_none, 
          do_nothing, 
          cmd_unset_opt_table())
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


