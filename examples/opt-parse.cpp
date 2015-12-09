#include <option.hpp>
#include <iostream>
/*****************************************************************************
 * Simple example for processing command line arguments.
 *
 * After compiling, try this:
 *
 *    opt-parse -a --banana --fruit=kiwi orange tomato
 *    opt-parse --help
 *
 ****************************************************************************/

int main(int argc, char* argv[]) {
  using namespace opt;
  using namespace std;

  // actions are handler functions which are executed when a command line
  // option is recognized by the parser
  action_t do_apple = [] (const string_t&) { 
    cout << "Apple\n"; 
    return 0; 
  };

  action_t do_banana = [] (const string_t&) { 
    cout << "Banana\n"; 
    return 0; 
  };

  // this option will receive its argument in 's'
  action_t do_fruit = [] (const string_t& s) { 
    cout << "You specified \"" << s << "\" as a fruit.\n";
    return 0;
  };

  // this action catches all command line arguments which were not assigned
  // to an option (e.g., a list of files at the end of the command line).
  action_t non_opt_args = [](const string_t& s) {
    cout << "[non_opt_args]: " << s << "\n";
    return 0;
  };

  // a list of options to pass to the 'parse' function.
  option_list_t opts = {
    option_t('a', "apple", "Display the word 'apple'.", arg_none, do_apple),
    option_t('b', "banana", "Display the word 'banana'.", arg_none, do_banana),
    option_t('f', "fruit", "Specify a fruit.", arg_required, do_fruit)
  };


  // parse the options given on the command line and execute their handlers
  return parse(opts, non_opt_args, argc, argv);
}
