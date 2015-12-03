#ifndef PARSE_HPP_2015_1202_2138
#define PARSE_HPP_2015_1202_2138 

#include <string>
#include <list>

namespace bit {
  using option_list = std::list<std::string>;

  auto parse(const int argc, char* argv[]) -> option_list;

  auto parse_arg(const char*) -> option_list;

// inline definitions
//============================================================================

  inline
  auto parse(const int argc, char* argv[]) -> option_list {

    return parse_arg(argv[argc]);
  };

  inline
  auto parse_arg(const char* arg) -> option_list {
    unsigned index  = 0;
    option_list options;

    auto advance = [&] {
      ++index;
    };

    auto parse_short_options = [&] {
      advance();
      if(isalpha(arg[index])) {
        options += string
      }    
    };

    auto start = [&] {
      switch(arg[index]) {
      case '-':
        advance();
        if(arg[index] == '-')
          return parse_short_options();
        else
          return parse_long_option();
        }
        break;
      case ' ':
        return start();
        break;
      default:
        return parse_word();
      };
    };
  }

};// namespace bit

#endif//PARSE_HPP_2015_1202_2138
