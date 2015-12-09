#include "option.hpp"



#include <iostream>
#include <getopt.h>
#include <vector>

namespace opt {
//============================================================================
//
auto parse(const option_list_t& opts, const action_t& non_arg, int argc, 
    char* argv[]) -> int 
{
  using namespace std;
  option_list_t opt_list(opts.begin(), opts.end());
  list<option_t> l(opt_list.begin(), opt_list.end());
  static auto option_help = [&] (const string_t&) -> int {
    for(auto& i : opt_list) {
      string_t so(1, get<0>(i));
      string_t lo(get<1>(i));
      string_t ht(get<2>(i));
      cout << (so.size() ? "-" : "") << so << "\t"
           << (lo.size() ? "--": "") << lo << "\t"
           << ht << "\n";
    }
    return 0;
  };
  static auto builtin_help_opt = option_t('h', "help", 
      "Display this help information.", arg_none, option_help);
  opt_list.push_back(builtin_help_opt);
  // string containing the short opts to pass to getopt_long
  string_t short_opt_string;
  // create the array of options to pass to getopt_long
  std::vector<struct option> opt_array;
  for(const auto& i : opt_list) {
    auto& shortopt = get<0>(i);
    auto& longopt  = get<1>(i);
    auto& helptxt  = get<2>(i);
    auto& has_arg  = get<3>(i);
    auto& action   = get<4>(i);

    // insert the entry into the long option array
    struct option o = { 
      longopt, 
      has_arg == arg_required ? required_argument : no_argument,
      0,
      shortopt
    };
    opt_array.push_back(o);
    // add an entry to the short option string
    short_opt_string += shortopt;
    if(has_arg == arg_required) {
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
    opt_match = getopt_long(argc, const_cast<char**>(argv), short_opt_string.c_str(), 
      opt_array.data(), &opt_index);
    for(auto& i : opt_list) {
      auto sopt = get<0>(i);
      if(sopt == opt_match) {
        auto action = get<4>(i);
        auto result = action((optarg ? optarg : ""));
        if(result) {
          return result;
        }
      }
    }
  };

  while(optind < argc) {
    auto r = non_arg(argv[optind++]);
    if(r) {
      return r;
    }
  }    
  return 0;
};
//============================================================================
//
}; // namespace opt
