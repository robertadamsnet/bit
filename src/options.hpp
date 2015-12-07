#ifndef OPTIONS_HPP_2015_1203_225632
#define OPTIONS_HPP_2015_1203_225632 

#include <functional>
#include <tuple>
#include <list>
#include <iostream>
#include <vector>
#include <getopt.h>

enum class Argument {
      required,
  not_required,
};

using string      = std::string;

using action_t    = std::function<int(const string&)>;
using option_t    = std::tuple<char, const char*, const char*, Argument, action_t>;
using option_list = std::list<option_t>;

auto parse(const option_list& opts, const action_t& non_opt_action, int argc, 
    char* argv[]) -> int;

auto make_option(char, const char*, const char*, Argument, action_t) 
  -> option_t;


#endif//OPTIONS_HPP_2015_1203_225632
