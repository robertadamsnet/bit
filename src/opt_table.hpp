#ifndef OPT_TABLE_HPP_20151217082815
#define OPT_TABLE_HPP_20151217082815 

#include "option.hpp"
#include <cstring>
#include <list>
#include <tuple>

namespace opt_table {

  enum arg_spec_t       { no_arg, arg_optional, arg_required };

  using arg_t           = std::string;
  using action_t        = std::function<void(const arg_t&)>;
  using help_text_t     = std::string;
  using name_t          = std::string;
  using name_list_t     = std::list<name_t>;
  using option_t        = std::tuple<name_list_t, help_text_t, arg_spec_t, 
                            action_t>;

  enum option_fields    { opt_names, opt_help, opt_arg, opt_action };

  using option_table_t  = std::vector<option_t>;

  template<class...Names>
  auto names(Names&&...names) {
    return name_list_t({ names... });
  };

  auto option(const name_list_t& names, const help_text_t& help, const
      arg_spec_t& argspec, const action_t& action) 
  {
    return make_tuple(names, help, argspec, action);
  }

  template<class...Options>
  auto create(Options&&...options) {
    return option_table_t({ options... });
  }

  auto dispatch(int argc, char* argv[], const option_table_t& table) {
    
    auto match_name = [] (const auto& namelist, const auto& optname) {
      for(const auto& n : namelist) {
        if(n == optname) {
          return true;
        }
      }
      return false;
    };

    // find match in option table or return null
    auto find_match = [&] (const auto& optname) -> const option_t* {
      for(auto& i : table) {
        if(match_name(std::get<opt_names>(i), optname)) {
          return &i;
        }
      }
      return nullptr;
    };

    auto is_option = [] (const std::string& optname) {
      return optname[0] == '-';
    };

    enum class Mode {
      option,
      argument
    };

    auto err_unexpected = [] (const auto& optname) {
      std::string msg = "Unexpected: " + optname;
      throw std::runtime_error(msg);
    };

    auto not_found = [&] (const std::string& optname) {
      if(is_option(optname)) {
        std::string msg = "Unknown option: " + optname;
        throw std::runtime_error(msg);
      }
      auto found = find_match("");
      if(found) {
        auto non_opt_handler = std::get<opt_action>(*found);
        non_opt_handler(optname);
      } else {
        err_unexpected(optname);
      }
    };

    auto err_arg_unexpected = [] (const std::string& optname) {
      std::string msg = "Option \"" + optname + "\" takes no arguments.";
      throw std::runtime_error(msg);
    };

    auto err_arg_required = [] (const std::string& optname) {
      std::string msg = "Argument required for option: " + optname;
      throw std::runtime_error(msg);
    };

    auto found = [] (const auto& match, auto optc, const auto& array) {
    };

    auto get_opts = [&] (const option::array_t& array) {
      for(int i = 0; i < array.size(); ++i) {
        auto opt = array[i];
        auto match = find_match(opt);
        if(match) {
          auto action = std::get<opt_action>(*match);
          auto arg_option = std::get<opt_arg>(*match);
          auto next_opt = i + 1;
          std::string optarg = next_opt < array.size() ? array[next_opt] : "";
          if(is_option(optarg)) {
            if(arg_option == arg_required) {
              err_arg_required(opt);
            } 
          } 
          else {
            if(arg_option == no_arg) {
              err_arg_unexpected(opt);
            }
          }
          action(optarg);
        } else {
          not_found(opt);
        }

      }
    };

    option::parse(argc, argv, get_opts);
  }

}; // namespace opt_table

#endif//OPT_TABLE_HPP_20151217082815
