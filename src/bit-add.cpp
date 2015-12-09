#include "bit.hpp"
#include "option.hpp"
#include <iostream>


int main(int argc, char* argv[]) {
  using namespace opt;
  using namespace std;
  
  auto fn = [](const string_t s) { cout << s << endl; return 0; };

  option_list_t opts = {
    option_t('a', "shit", "shit", arg_required, fn )
  };


  return parse(opts, fn, argc, argv);
}

