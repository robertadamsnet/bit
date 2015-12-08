#include "option.hpp"

#include <iostream>
#include <functional>
#include <tuple>

namespace option {
//============================================================================
//
/*
  auto merge(int argc, char* argv[]) -> string_t {
    
    using namespace std;
    string_t argstr;
    auto append_space = [&] {
      argstr += " ";
    };
    std::function<void(void)> append_fn = [&] {
      append_fn = append_space;
    };
    for(int i = 0; i < argc; ++i) {
      append_fn();
      argstr += argv[i];
    }
    cout << argstr << "\n";
    return argstr;
  }
*/
//============================================================================
//
  auto parse(int argc, char* argv[], optlist_t& opts) -> int {
    std::function<int(int)> parse_all = [&] (int idx) -> int {
      if(idx < argc) {
        auto result = parse(argv[idx], opts);
        return result ? result : parse_all(idx + 1);
      }
      return 0;
    };
    return parse_all(0);
  };
//============================================================================
//
  auto parse(const string_t& cmd, const optlist_t& opts) -> int {
    using namespace std;
    using size_type       = string_t::size_type;
    const size_type len   = cmd.size();
    size_type idx         = 0;

    auto peek  = [&] {
      return idx < len ? cmd[idx] : 0;
    };

    auto getch = [&] {
      return idx < len ? cmd[idx++] : 0;
    };

    std::function<int(void)> parse_start;

    auto parse_long_option = [&] {
      string_t optstr;
      while(isalpha(peek())) {
        optstr += getch();
      }
    };

    auto parse_non_option = [&] {
      for(auto& i : opts) {
        if(get<Short>(i) == '!') {
          auto action = get<Action>(i);
          auto result = action(string_t(cmd,idx));
          return result ? result : parse_start();
        }
      }
      return 0;
    };

    auto parse_short_options = [&] {
      while(isalpha(peek())) {
        auto ch = getch();
        for(auto& i : opts) {
          if(ch == get<Short>(i)) {
            auto action = get<Action>(i);
            auto result = action("");
            return result ? result : parse_non_option();
          }
        }
        return 0;
      }
      return parse_non_option();
    };

    auto parse_option = [&] {
      if(peek() == '-') {
        getch();
        return parse_long_option();
      } 
      return parse_short_options();
    };

    parse_start = [&] {
      auto ch = getch();

      while(isspace(ch = getch()));

      if(ch == '-') {
        return parse_option();
      }
    };

  }

//============================================================================
}; // namespace option
