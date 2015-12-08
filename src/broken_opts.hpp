#ifndef OPTION_HPP_20151207174259
#define OPTION_HPP_20151207174259 

#include <string>
#include <functional>
#include <list>

namespace option {
//============================================================================
//

  using string_t        = std::string;

  using shortopt_t      = char;
  using longopt_t       = string_t;
  using help_t          = string_t;
  using action_t        = std::function<int(const string_t&)>;
  using option_t        = std::tuple<shortopt_t, longopt_t, help_t, action_t>;
  using optlist_t       = std::list<option_t>;

  enum { Short, Long, Help, Action };

  //auto merge(int argc, char* argv[]) -> string_t;

  auto parse(int argc, char* argv[]) -> int;
  auto parse(const string_t& cmd, const optlist_t&) -> int;



//============================================================================
}; // 

#endif//OPTION_HPP_20151207174259
