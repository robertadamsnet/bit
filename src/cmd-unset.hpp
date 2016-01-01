#ifndef CMD_UNSET_HPP_20151230150757
#define CMD_UNSET_HPP_20151230150757 

#include "db.hpp"
#include "config.hpp"
#include <options/options.hpp>

inline
auto cmd_unset_opt_table() -> option::table_t* {
  using namespace option;

  static std::list<std::string> removals;

  auto do_unset = [&] (std::string arg) {
    removals.push_back(arg);
  };

  auto do_terminator = [&] (const std::string&) {
    config::fn::remove_from_db(removals);
  };

  static auto opts = table(
    entry(tag_nomatch(), "", arg_required, do_unset, nullptr),
    entry(tag_terminator(), "", arg_none,  do_terminator, nullptr)
  );


  return &opts;
};

#endif//CMD_UNSET_HPP_20151230150757
