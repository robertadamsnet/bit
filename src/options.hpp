#ifndef OPTIONS_HPP_2015_1203_225632
#define OPTIONS_HPP_2015_1203_225632 

#include <functional>
#include <tuple>
#include <list>
#include <iostream>

auto option_help = [] () -> int {
  using namespace std;
  cout << "Displaying help and shit.\n\n";
  return 0;
};

using action_t    = std::function<int(void)>;
using option_t    = std::tuple<char, const char*, const char*, bool, action_t>;
using parser_t    = std::function<int(int, char*[])>;
using option_list = std::list<option_t>;

auto option_parser(const option_list&) -> parser_t;

auto make_option(char, const char*, const char*, bool, action_t) -> option_t;


#endif//OPTIONS_HPP_2015_1203_225632
