#ifndef DB_HPP_20151207132454
#define DB_HPP_20151207132454 

#include <string>
#include <map>

namespace db {
//============================================================================
//
  using string_t        = std::string;
  using map_t           = std::multimap<string_t, string_t>;

  auto from_file(const string_t&) -> map_t;
  auto to_file(const string_t&, const map_t&) -> void;


//============================================================================
}; // namespace db
#endif//DB_HPP_20151207132454
