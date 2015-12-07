#include "options.hpp"

#include <iostream>
#include <getopt.h>
#include <vector>


auto make_option(char shortopt, const char* longopt, const char* helptxt,
  Argument has_arg, action_t action) -> option_t 
{
  return std::make_tuple(shortopt, longopt, helptxt, has_arg, action);
}

auto parse(const option_list& opts, const action_t& non_arg, int argc, 
    char* argv[]) -> int 
{
  using namespace std;
  option_list opt_list(opts.begin(), opts.end());
  list<option_t> l(opt_list.begin(), opt_list.end());
  static auto option_help = [&] (const string&) -> int {
    for(auto& i : opt_list) {
      string so(1, get<0>(i));
      string lo(get<1>(i));
      string ht(get<2>(i));
      cout << (so.size() ? "-" : "") << so << "\t"
           << (lo.size() ? "--": "") << lo << "\t"
           << ht << "\n";
    }
    return 0;
  };
  static auto builtin_help_opt = make_option('h', "help", 
      "Display this help information.", Argument::not_required, option_help);
  opt_list.push_back(builtin_help_opt);
  // string containing the short opts to pass to getopt_long
  string short_opt_string;
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
      has_arg == Argument::required ? required_argument : no_argument,
      0,
      shortopt
    };
    opt_array.push_back(o);
    // add an entry to the short option string
    short_opt_string += shortopt;
    if(has_arg == Argument::required) {
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
