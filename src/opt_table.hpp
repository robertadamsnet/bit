#ifndef OPT_TABLE_HPP_20151217082815
#define OPT_TABLE_HPP_20151217082815 

#include <cstring>

#include "option.hpp"

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

    auto get_opt = [&] (const std::string& optname) {
      auto error_expected_argument = [&] {
        std::string msg = "Expected argument for option: " + optname;
        throw std::runtime_error(msg);
      };
      auto error_unrecognized = [&] {
        std::string msg = "Unrecognized option: " + optname;
        throw std::runtime_error(msg);
      };

      auto match = find_match(optname);
      
    };

    option::parse(argc, argv, get_opt);
  }

}; // namespace opt_table

#endif//OPT_TABLE_HPP_20151217082815
