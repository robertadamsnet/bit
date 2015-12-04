#include "options.hpp"

#include <iostream>
#include <getopt.h>
#include <vector>

auto option_parser(const option_list& opts) -> parser_t {
  return [&] (int argc, char* argv[]) -> int {
    using namespace std;
    // string containing the short opts to pass to getopt_long
    string short_opt_string;
    // create the array of options to pass to getopt_long
    std::vector<struct option> opt_array;
    for(auto& i : opts) {
      auto& shortopt = get<0>(i);
      auto& longopt  = get<1>(i);
      auto& helptxt  = get<2>(i);
      auto& has_arg  = get<3>(i);
      auto& action   = get<4>(i);

      // insert the entry into the long option array
      struct option o = { 
        longopt, 
        has_arg ? required_argument : no_argument,
        0,
        shortopt
      };
      opt_array.push_back(o);
      // add an entry to the short option string
      short_opt_string += shortopt;
      if(has_arg) {
        short_opt_string += ":";
      }
    } 
    // terminal entry
    struct option o = { 0, 0, 0, 0 };
    opt_array.push_back(o);
    // process each argument passed to the command line
    int opt_match = 0;
    int opt_index = 0;
    while(opt_match != -1) {
      opt_match = getopt_long(argc, argv, short_opt_string.c_str(), 
        opt_array.data(), &opt_index);
      for(auto& i : opts) {
        auto sopt = get<0>(i);
        if(sopt == opt_match) {
          auto action = get<4>(i);
          auto result = action();
          if(result) {
            return result;
          }
        }
      }
    };
    return 0;
  };
};

auto make_option(char shortopt, const char* longopt, const char* helptxt,
  bool has_arg, action_t action) -> option_t 
{
  return std::make_tuple(shortopt, longopt, helptxt, has_arg, action);
}


