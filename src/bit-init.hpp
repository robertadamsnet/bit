#ifndef BIT_INIT_HPP_20151214142637
#define BIT_INIT_HPP_20151214142637 

#include "option.hpp"
#include <list>
#include <iostream>
#include <algorithm>

namespace option {

  using short_opt_t       = std::string;
  using long_opt_t        = std::string;
  using help_text_t       = std::string;
  using action_t          = std::function<void(const string*)>;

  enum option_has_arg {
    arg_optional,
    arg_required,
    no_argument
  };


  using item_t            = std::tuple<short_opt_t, long_opt_t, help_text_t,
                                        option_has_arg, action_t>;

  enum { item_short_opt, item_long_opt, item_help_text, item_has_arg,
    item_action };

  using table_t           = std::list<item_t>;

  template<class NextFn>
  auto dispatch(const table_t&, const NextFn);

}; // namespace option

template<class T>
void do_init(T&& next_fn);

auto do_init_trample = [] (const std::string* arg) { 
  using namespace std;
  cout << "HULK SMASH!!!!" << endl; 
};

template<class NextFn>
auto option::dispatch(const table_t& table, const NextFn next) {
  using namespace std;

  auto non_opt_action = [&] () -> action_t {
    for(const auto& i : table) {
      if(get<item_short_opt>(i) == "&") {
        return get<item_action>(i);
      }
    }
    return [](const string*) {};
  }();

  auto is_opt = [&] (const string& s) {
    return s[0] == '-';
  };
  auto opt_found = false;

  std::function<void(const string&)> dispatch_opt = [&](const string& opt) {
    for(const auto& i : table) {
      auto short_opt_match  = get<item_short_opt>(i) == opt;
      auto long_opt_match   = get<item_long_opt>(i) == opt;
      if(short_opt_match || long_opt_match) {
        opt_found = true;
        auto action = get<item_action>(i);
        auto has_arg = get<item_has_arg>(i);
        auto next_opt = next();
        switch(has_arg) {
        case arg_required:
          if(is_opt(next_opt)) {
            string errmsg = "Expected argument for option: " + opt;
            throw runtime_error(errmsg);
          } else {
            action(&next_opt);
            dispatch_opt(next());
          }
          break;
        case arg_optional:
          if(is_opt(next_opt)) {
            action(nullptr);
            dispatch_opt(next_opt);
          } 
          else {
            action(&next_opt);
            dispatch_opt(next());
          }
          break;
        case no_argument:
          if(is_opt(next_opt)) {
            action(nullptr);
            dispatch_opt(next_opt);
          }
          else {
            string errmsg = "Unexpected argument specified for option: " + opt;
            throw runtime_error(errmsg);
          }
        };
      }
    }
    if(!opt_found) {
      string errmsg = "Unrecognized option: " + opt;
      throw runtime_error(errmsg);
    }
  };

  auto dispatch_value = [&] (const string& s) {
    non_opt_action(&s);
  };

  std::function<void(void)> inner_ = [&] {
    auto opt = next();
    if(is_opt(opt)) {
      dispatch_opt(opt);
    } 
    else {
      dispatch_value(opt);
    }   
  };
};

template<class T>
void do_init(T&& next) {

  option::table_t opts = {
    option::item_t("-T", "--trample", 
      "Destroy an existing database and init a new one.", option::no_argument, 
      do_init_trample
    )
  };

  option::dispatch(opts, next);
  
}

#endif//BIT_INIT_HPP_20151214142637
