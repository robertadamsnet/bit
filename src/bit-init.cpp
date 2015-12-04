#include "bit.hpp"
#include "options.hpp"

#include <iostream>


//Implementation-type stuff
//===========================================================================
int main(int argc, char* argv[]) {

  option_list options = {
    make_option('h', "help", "Display help information.", false, option_help)
  };

  auto parse = option_parser(options);

  parse(argc, argv);
  
  return 0;
}
















