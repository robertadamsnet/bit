#ifndef CMD_SET_HPP_20151230095625
#define CMD_SET_HPP_20151230095625 

#include "db.hpp"
#include "config.hpp"
#include <options/options.hpp>

inline
auto cmd_set_opt_table() -> option::table_t* {
  using namespace option;

  static db::map_t assignments;

  auto do_set = [&] (const std::string& arg) {
    auto record = db::from_string(arg);
    assignments.erase(record.first);
    assignments.insert(record);
  };

  auto do_terminator = [&] (const std::string&) {
    config::fn::merge_into_db(assignments);
  };

  auto do_display_set = [&] (const std::string&) {
    for(const auto& key_value : config::fn::read_db() ) {
      std::cout << key_value.first << ":" << key_value.second << "\n";
    }
  };

  static auto opts = table(
    entry(tag_nomatch(), "", arg_required, do_set, nullptr),
    entry(tag_terminator(), "", arg_none,  do_terminator, nullptr),
    entry(do_display_set)
  );


  return &opts;
};
#endif//CMD_SET_HPP_20151230095625
