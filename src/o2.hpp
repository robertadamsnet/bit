#ifndef O2_HPP_20151229195813
#define O2_HPP_20151229195813 

#include <options/option_table.hpp> 

namespace o2 {
using namespace option;

using arg_array = std::vector<const char*>;
using arg_iter  = arg_array::const_iterator;

int parse(const arg_iter& begin, const arg_iter& end, const table_t* table); 
int parse(const arg_array& args, const table_t* table);
int parse(int argc, char* argv[], const table_t* table);
int parse(int argc, char* argv[], int start, const table_t* table);

}; // namespace o2

int o2::parse(const arg_iter& begin, const arg_iter& end, 
    const table_t* table) 
{
  std::function<int(void)> recurse;

  arg_iter next = begin;

  auto symbol = [&] (const auto& iter) {
    return iter == end 
      ? ""
      : *iter;
  };

  auto option_not_found = [&] () {
    auto opt = symbol(next);
    std::string msg = "Invalid option: ";
    msg += opt;
    throw std::runtime_error(msg);
    return 0;
  };

  using delegate_t  = std::pair<action_t, std::string>;
  using queue_t     = std::list<delegate_t>;

  queue_t queue;

  auto is_option = [&] (const auto& symbol) {
    return symbol == nullptr 
      ? false
      : symbol[0] == '-';
  };

  auto is_long_option = [&] (const auto& symbol) {
    return is_option(symbol) && symbol[1] == '-';
  };


  auto enqueue = [&] (const auto& delegate) {
    queue.push_back(delegate);
  };

  auto option_no_arg = [&] (const auto& entry) {
    enqueue(make_pair(entry.action, ""));
    return recurse();
  };

  auto is_non_option = [&] (const auto& symbol) {
    return is_option(symbol) 
      ? false
      : symbol == ""
        ? false
        : true;
  };

  auto option_arg = [&] (const auto& entry) {
    return is_non_option(symbol(next + 1));
  };

  auto found = [&] (const auto& entry) {
    return entry.arg_spec == arg_none 
      ? option_no_arg(entry) 
      : option_arg(entry);
  };

  auto find = [&] (const auto& symbol) -> const entry_t* {
    for(const auto& entry : *table) {
      for(const auto& name : entry.names) {
        if(symbol != nullptr && symbol == name) {
          return &entry;
        }
      }
    }
    return nullptr;
  };

  auto parse_long_option = [&] (const auto& symbol) {
    auto entry = find(symbol);
    return entry == nullptr
      ? option_not_found()
      : found(*entry);
  };

  auto parse_short_options = [&] {
    std::string opts = *next;
    char opt[] = { '-', 0, 0 };
    for(const auto& c : opts) {
      opt[1] = c;
      parse_long_option(opt);
    }
    return 0;
  };

  auto check_long_option = [&] {
    return is_long_option(*next)
      ? parse_long_option(*next) 
      : parse_short_options();
  };

  auto parse_argument = [&] (const auto& symbol) {
    return parse_long_option(symbol);
  };

  auto check_option = [&] {
    return is_option(*next)
      ? check_long_option() 
      : parse_argument(*next);
  };


  recurse = [&] {
    if(next == end) {
      return 0;
    } else {
      return check_option();
    }
    ++next;
    return recurse();
  };

  return recurse();
};

int o2::parse(const arg_array& args, const table_t* table) {
  return parse(args.begin(), args.end(), table);
};

int o2::parse(int argc, char* argv[], const table_t* table) {
  return parse(argc, argv, 1, table);
}

int o2::parse(int argc, char* argv[], int start, const table_t* table) {
  arg_array args(argc);
  for(int i = start; i < argc; ++i) {
    args[i] = argv[i];
  }

  return parse(args, table);
};

#endif//O2_HPP_20151229195813
